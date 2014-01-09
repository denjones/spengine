#include "StdAfx.h"
#include "SPV8ScriptEngine.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPV8ScriptEngine::SPV8ScriptEngine(void)
	{
		isolate = NULL;
		isThreadRunning = false;
		isStopping = false;
	}

	SPV8ScriptEngine::~SPV8ScriptEngine(void)
	{
		StopThread();

		persistentContext->ClearAndLeak();
		persistentContext = NULL;

		if (isolate)
		{
			isolate->Dispose();
			isolate = NULL;
		}
	}

	Isolate* SPV8ScriptEngine::GetIsolate()
	{
		return isolate;
	}

	Handle<Context> SPV8ScriptEngine::GetContext()
	{
		return Handle<Context>::New(isolate, *persistentContext);
	}

	bool SPV8ScriptEngine::Initialize()
	{
		isolate = Isolate::New();

		Locker locker(isolate); 
		Isolate::Scope isolateScope(isolate);
		HandleScope handleScope(isolate);

		// Create a new context.
		// Make context persistent.
		persistentContext = new Persistent<Context>(isolate, Context::New(isolate));

		// Global Function
		AddFunction(L"using", Import);
		AddFunction(L"include", Include);

		StartThread();

		return true;
	}

	bool SPV8ScriptEngine::Load()
	{
		return true;
	}

	bool SPV8ScriptEngine::Unload()
	{
		return true;
	}

	Handle<Value> SPV8ScriptEngine::Eval( SPString scriptStr, bool isInScope )
	{
		SPPointer<Locker> innerLocker;
		SPPointer<Isolate::Scope> isolateScope;
		SPPointer<Context::Scope> contextScope;

		if (!isInScope)
		{
			innerLocker = new Locker(isolate); 
			isolateScope = new Isolate::Scope(isolate);
		}

		// Create a stack-allocated handle scope.

		EscapableHandleScope escapableHandleScope(isolate);

		if (!isInScope)
		{
			Handle<Context> context = GetContext();
			contextScope = new Context::Scope(context);
		}

		// Try.

		TryCatch trycatch;

		// Create a string containing the JavaScript source code.

		Handle<String> source = String::NewFromTwoByte(isolate, (uint16_t*)scriptStr.c_str());

		if (source.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		// Compile the source code.

		Handle<Script> script = Script::Compile(source);

		if (script.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		// Run the script to get the result.

		Handle<Value> result = script->Run();

		if (result.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		return escapableHandleScope.Escape<Value>(result);
	}

	Handle<Value> SPV8ScriptEngine::EvalFile( SPString path, bool isInScope )
	{
		SPPointer<Locker> innerLocker;
		SPPointer<Isolate::Scope> isolateScope;
		SPPointer<Context::Scope> contextScope;

		if (!isInScope)
		{
			innerLocker = new Locker(isolate); 
			isolateScope = new Isolate::Scope(isolate);
		}

		// Create a stack-allocated handle scope.

		EscapableHandleScope escapableHandleScope(isolate);

		if (!isInScope)
		{
			Handle<Context> context = GetContext();
			contextScope = new Context::Scope(context);
		}

		// Try.

		TryCatch trycatch;

		// Load script file.

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to open script file: " + path);
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		LONGLONG length = file->GetFileLength();
		void* pData = new char[(UINT)length];

		if (!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to read script file: " + path);
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		SPFileManager::GetSingleton().CloseFile(path);

		// Create a string containing the JavaScript source code.

		Handle<String> source = String::NewFromUtf8(isolate, (char*)pData, String::kNormalString, length);

		delete [] pData;
		pData = NULL;

		if (source.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		// Compile the source code.

		Handle<Script> script = Script::Compile(source, String::NewFromTwoByte(isolate, (uint16_t*)path.c_str()));

		if (script.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		// Run the script to get the result.

		Handle<Value> result = script->Run();

		if (result.IsEmpty())
		{
			// Error

			LogMessage(trycatch.Message());
			return escapableHandleScope.Escape<Value>(Undefined(isolate));
		}

		return escapableHandleScope.Escape<Value>(result);
	}

	SPString SPV8ScriptEngine::StringToSPString( Handle<String> str )
	{
		uint16_t* realResult = new uint16_t[str->Length() + 1];
		str->Write(realResult);

		SPString result = (wchar_t*)realResult;
		delete [] realResult;

		return result;
	}

	void SPV8ScriptEngine::Enter()
	{
		if (!locker)
		{
			locker = new Locker(isolate);
			isolate->Enter();
		}		
	}

	void SPV8ScriptEngine::Exit()
	{
		if (locker)
		{
			isolate->Exit();
			locker = NULL;
		}		
	}

	void SPV8ScriptEngine::LogMessage( Handle<Message> &msg )
	{
		SPLogHelper::WriteLog(L"[SPScript] Error: " + StringToSPString(msg->Get()));
		SPLogHelper::WriteLog(L"[SPScript] in \"" + StringToSPString(msg->GetScriptResourceName()->ToString()) +
			L"\", line " + SPStringHelper::ToWString(msg->GetLineNumber()) + 
			L", col " + SPStringHelper::ToWString(msg->GetEndColumn()));
			//L"\nCall Stack: \n" + StringToSPString(msg->GetStackTrace()));
	}

	bool SPV8ScriptEngine::Update( float timeElapsed )
	{
		timingScriptToRunLock.Lock();

		int currentTimeMs = timeGetTime();

		for(TimeingScriptMap::iterator iter = timingScriptToRun.begin(); iter != timingScriptToRun.end(); iter++)
		{
			Locker lock(isolate);
			Isolate::Scope isolateScope(isolate);		
			HandleScope handleScope(isolate);
			Handle<Context> realContext = GetContext();
			Context::Scope contextScope(realContext);

			if (iter->first >= currentTimeMs)
			{
				for(ScriptList::iterator innerIter = iter->second.begin(); innerIter != iter->second.end(); innerIter++)
				{
					if ((*innerIter)->type == ScriptFile)
					{
						Handle<Value> result = EvalFile((*innerIter)->value, true);
					}
					else
					{
						Handle<Value> result = Eval((*innerIter)->value, true);
					}
				}

				iter = timingScriptToRun.erase(iter);
			}
			else
			{
				break;
			}
		}

		timingScriptToRunLock.Unlock();

		return true;
	}

	bool SPV8ScriptEngine::Draw( float timeElapsed )
	{
		return true;
	}

	DWORD WINAPI SPV8ScriptEngine::ScriptRunningThread( void* context )
	{
		SPV8ScriptEngine* engine = (SPV8ScriptEngine*)context;

		while(!engine->IsStopping())
		{
			if (!engine->RunNextScript())
			{
				Sleep(16);
			}
		}

		engine->ThreadExited();

		return 0;
	}

	void SPV8ScriptEngine::StartThread()
	{
		isThreadRunning = CloseHandle(CreateThread(NULL, 0, ScriptRunningThread, (void*)this, 0, NULL)) == TRUE;
	}

	void SPV8ScriptEngine::StopThread()
	{
		if (isThreadRunning)
		{
			stoppingLock.Lock();
			isStopping = true;
			stoppingLock.Unlock();

			while(isThreadRunning)
			{
				Sleep(16);
			}
		}
	}

	bool SPV8ScriptEngine::IsStopping()
	{
		bool result = false;
		stoppingLock.Lock();
		result = isStopping;
		stoppingLock.Unlock();
		return result;
	}

	void SPV8ScriptEngine::ThreadExited()
	{
		threadRunningLock.Lock();
		isThreadRunning = false;
		threadRunningLock.Unlock();
	}

	void SPV8ScriptEngine::RunScript( SPString scriptStr )
	{
		scriptToRunLock.Lock();
		scriptToRun.push_back(new ScriptToRun(ScriptString, scriptStr));
		scriptToRunLock.Unlock();

		return;
	}

	void SPV8ScriptEngine::RunScriptFromFile( SPString path )
	{
		scriptToRunLock.Lock();
		scriptToRun.push_back(new ScriptToRun(ScriptFile, path));
		scriptToRunLock.Unlock();

		return;
	}

	ScriptToRunPtr SPV8ScriptEngine::NextScriptToRun()
	{
		ScriptToRunPtr result = NULL;

		scriptToRunLock.Lock();
		if (scriptToRun.size() > 0)
		{
			result = new ScriptToRun(*scriptToRun.front());
			scriptToRun.pop_front();
		}	
		scriptToRunLock.Unlock();

		return result;
	}

	bool SPV8ScriptEngine::RunNextScript()
	{
		ScriptToRunPtr scriptToRunObj = NextScriptToRun();

		if (!scriptToRunObj)
		{
			return false;
		}

		Locker lock(isolate);
		Isolate::Scope isolateScope(isolate);		
		HandleScope handleScope(isolate);
		Handle<Context> realContext = GetContext();
		Context::Scope contextScope(realContext);

		if (scriptToRunObj->type == ScriptFile)
		{
			Handle<Value> result = EvalFile(scriptToRunObj->value, true);
		}
		else
		{
			Handle<Value> result = Eval(scriptToRunObj->value, true);
		}

		return true;
	}

	void SPV8ScriptEngine::ThreadEnter()
	{
		if (!threadLocker)
		{
			threadLocker = new Locker(isolate);
			isolate->Enter();
		}	
	}

	void SPV8ScriptEngine::ThreadExit()
	{
		if (threadLocker)
		{
			isolate->Exit();
			threadLocker = NULL;
		}	
	}

	void SPV8ScriptEngine::AddTimingScript( ScriptToRunPtr script, int timeoutMS )
	{
		timingScriptToRunLock.Lock();
		int runTime = timeGetTime() + timeoutMS;
		if (timingScriptToRun.find(runTime) == timingScriptToRun.end())
		{
			timingScriptToRun[runTime] = ScriptList();
		}
		timingScriptToRun[runTime].push_back(script);
		timingScriptToRunLock.Unlock();
	}

	void SPV8ScriptEngine::AddFunction( SPString funcName, FunctionCallback function )
	{
		Locker lock(isolate);
		Isolate::Scope isolateScope(isolate);		
		HandleScope handleScope(isolate);
		Handle<Context> context = GetContext();
		Context::Scope contextScope(context);
		Handle<FunctionTemplate> funcTmpl = FunctionTemplate::New(isolate, function);

		context->Global()->Set(SPV8ScriptEngine::SPStringToString(funcName), funcTmpl->GetFunction());
	}

	Handle<String> SPV8ScriptEngine::SPStringToString( SPString str )
	{
		return String::NewFromTwoByte(SPV8ScriptEngine::GetSingleton().GetIsolate(), (uint16_t*)str.c_str());
	}

	void SPV8ScriptEngine::Import( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
		HandleScope handleScope(isolate);
		Handle<Context> context = isolate->GetCurrentContext();

		if (args.Length() == 0) {
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		// Ensure one module can only be imported once!

		Handle<String> moduleName = Handle<String>::Cast(args[0]);
		Handle<Object> loadedModules = Handle<Object>::Cast(context->Global()->GetHiddenValue(
			SPV8ScriptEngine::SPStringToString(L"_loadedModules")));

		if (loadedModules.IsEmpty()) {
			loadedModules = Object::New();
			context->Global()->SetHiddenValue(SPV8ScriptEngine::SPStringToString(L"_loadedModules"), loadedModules);
		}

		if (loadedModules->HasOwnProperty(moduleName)) {
			args.GetReturnValue().Set(loadedModules->Get(moduleName));
			return;
		}

		Handle<Value> result = SPV8ScriptEngine::GetSingleton().EvalFile(SPV8ScriptEngine::StringToSPString(args[0]->ToString()), true);

		loadedModules->Set(moduleName, result);
		args.GetReturnValue().Set(result);
	}

	void SPV8ScriptEngine::Include( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
		HandleScope handleScope(isolate);

		if (args.Length() == 0) {
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		Handle<Value> result = SPV8ScriptEngine::GetSingleton().EvalFile(SPV8ScriptEngine::StringToSPString(args[0]->ToString()), true);

		return;
	}


}
