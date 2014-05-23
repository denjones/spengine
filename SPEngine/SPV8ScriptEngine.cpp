#include "StdAfx.h"
#include "SPV8ScriptEngine.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"
#include "SPRandomHelper.h"
#include "SPConfigManager.h"



namespace SPEngine
{
	SPV8ScriptEngine::SPV8ScriptEngine(void)
	{
		isolate = NULL;
		isThreadRunning = false;
		isStopping = false;
		pAsync = new uv_async_t();
		((uv_async_t*)pAsync)->data = (void*)&scriptToRun;
	}

	SPV8ScriptEngine::~SPV8ScriptEngine(void)
	{
		StopThread();

		if (persistentContext)
		{
			persistentContext->ClearAndLeak();
			persistentContext = NULL;
		}		

		//if (isolate)
		//{
		//	isolate->Dispose();
		//	isolate = NULL;
		//}

		if(pAsync)
		{
			delete pAsync;
			pAsync = NULL;
		}
	}

	Isolate* SPV8ScriptEngine::GetIsolate()
	{
		return isolate;
	}

	Handle<Context> SPV8ScriptEngine::GetContext()
	{
		//return Handle<Context>::New(isolate, *persistentContext);

		Handle<Context> context = isolate->GetCurrentContext();
		if (context.IsEmpty())
		{
			context = Context::New(isolate);
			context->Enter();
		}
		return context;
	}

	void SPV8ScriptEngine::Initialize()
	{
		isolate = Isolate::New();

		Locker locker(isolate); 
		Isolate::Scope isolateScope(isolate);
		HandleScope handleScope(isolate);

		// Create a new context.
		// Make context persistent.
		//persistentContext = new Persistent<Context>(isolate, Context::New(isolate));

		// Global Function
		//AddFunction(L"using", Import);
		//AddFunction(L"include", Include);
		//AddFunction(L"sleep", SleepFunc);
		//AddFunction(L"setTimeout", SetTimeOut);
		//AddFunction(L"clearTimeout", ClearTimeOut);

		StartThread();
	}

	void SPV8ScriptEngine::Load()
	{
	}

	void SPV8ScriptEngine::Unload()
	{
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

		SPFilePtr file = SPFileManager::GetSingleton()->OpenFile(path);

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

		SPFileManager::GetSingleton()->CloseFile(path);

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
		if (!msg.IsEmpty())
		{
			SPLogHelper::WriteLog(L"[SPScript] Error: " + StringToSPString(msg->Get()));
			SPLogHelper::WriteLog(L"[SPScript] in \"" + StringToSPString(msg->GetScriptResourceName()->ToString()) +
				L"\", line " + SPStringHelper::ToWString(msg->GetLineNumber()) + 
				L", col " + SPStringHelper::ToWString(msg->GetEndColumn()));
		}
	}

	void SPV8ScriptEngine::Update( float timeElapsed )
	{
	}

	void SPV8ScriptEngine::Draw( float timeElapsed )
	{
	}

	void EvalCallback( uv_async_t *handle, int status)
	{
		list<ScriptToRunPtr>* scriptList = (list<ScriptToRunPtr>*)handle->data;

		HandleScope handleScope(SPV8ScriptEngine::GetSingleton()->GetIsolate());
		Handle<Context> realContext = SPV8ScriptEngine::GetSingleton()->GetIsolate()->GetCurrentContext();
		Context::Scope contextScope(realContext);

		if (scriptList->size() != 0)
		{
			ScriptToRunPtr script = scriptList->front();

			if (script->type == ScriptFile)
			{
				Handle<Value> result = SPV8ScriptEngine::GetSingleton()->EvalFile(script->value, true);
			}
			else
			{
				Handle<Value> result = SPV8ScriptEngine::GetSingleton()->Eval(script->value, true);
			}

			scriptList->pop_front();
		}
	}

	DWORD WINAPI SPV8ScriptEngine::ScriptRunningThread( void* context )
	{
		SPV8ScriptEngine* engine = (SPV8ScriptEngine*)context;

		if (SPConfigManager::GetSingleton()->GetCurrentConfig().debug)
		{
			//AllocConsole();
			HWND hWnd = GetConsoleWindow();
			ShowWindow( hWnd, SW_SHOW );
			//freopen("CONIN$", "r+t", stdin); // Redirect STDIN
			//freopen("CONOUT$", "w+t", stdout); // Redirect STDOUT
			SetConsoleTitle(L"Console"); 
		}

		// Initialize uv async obj

		uv_async_init(uv_default_loop(), (uv_async_t*)engine->GetAsync(), EvalCallback);

		wchar_t BufferFileName[MAX_PATH];
		GetModuleFileName(NULL, BufferFileName, MAX_PATH);

		string name = SPStringHelper::WStringToUTF8String(SPString(BufferFileName));

		engine->GetIsolate()->Enter();

		char** args = new char*[1];
		args[0] = new char[name.length()];

		for (int i = 0; i < name.length(); i++)
		{
			args[0][i] = name[i];
		}

		node::Start(1, args);

		engine->GetIsolate()->Exit();

		//while(!engine->IsStopping())
		//{
		//	if (!engine->RunTimeOutFunc() && !engine->RunNextScript())
		//	{
		//		Sleep(1);
		//	}
		//}

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

			int totalSleep = 0;
			bool isTerminating = false;
			V8::TerminateExecution(isolate);
			//while(isThreadRunning)
			//{
			//	Sleep(16);
			//	totalSleep += 16;
			//	if (totalSleep > 100 && !isTerminating)
			//	{
					//V8::TerminateExecution(isolate);
					//uv_stop(uv_default_loop());					
			//		isTerminating = true;
			//	}
			//}
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

		uv_async_send((uv_async_t*)pAsync);

		return;
	}

	void SPV8ScriptEngine::RunScriptFromFile( SPString path )
	{
		scriptToRunLock.Lock();
		scriptToRun.push_back(new ScriptToRun(ScriptFile, path));
		scriptToRunLock.Unlock();

		uv_async_send((uv_async_t*)pAsync);

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

	void SPV8ScriptEngine::RunNextScript()
	{
		ScriptToRunPtr scriptToRunObj = NextScriptToRun();

		if (!scriptToRunObj)
		{
			return;
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

	Handle<Number> SPV8ScriptEngine::SetTimeOutFunction( Handle<Function> func, int timeoutMS )
	{
		timingScriptToRunLock.Lock();
		int runTime = timeGetTime() + timeoutMS;
		if (timeOutFunctionToRun.find(runTime) == timeOutFunctionToRun.end())
		{
			timeOutFunctionToRun[runTime] = FunctionList();
		}

		SPPointer<Persistent<Function>> persistentFunction = new Persistent<Function>(isolate, func);
		int timeOutId = SPRandomHelper::NextInt(1000000);
		while(timeOutMap.find(timeOutId) != timeOutMap.end())
		{
			timeOutId = SPRandomHelper::NextInt(1000000);
		}
		timeOutMap[timeOutId] = persistentFunction;
		timeOutFunctionToRun[runTime].push_back(timeOutId);
		timingScriptToRunLock.Unlock();

		return Number::New(timeOutId);
	}

	void SPV8ScriptEngine::ClearTimeOutFunction( Handle<Number> id )
	{
		timingScriptToRunLock.Lock();

		int timeOutId = id->Int32Value();
		TimeOutMap::iterator theIter = timeOutMap.find(timeOutId);

		if (theIter != timeOutMap.end())
		{
			timeOutMap.erase(theIter);
		}

		timingScriptToRunLock.Unlock();
	}

	void SPV8ScriptEngine::AddFunction( SPString funcName, FunctionCallback function )
	{
		Locker lock(isolate);
		Isolate::Scope isolateScope(isolate);		
		HandleScope handleScope(isolate);
		Handle<Context> context = GetContext();
		Context::Scope contextScope(context);
		Handle<FunctionTemplate> funcTmpl = FunctionTemplate::New(function);

		context->Global()->Set(SPV8ScriptEngine::SPStringToString(funcName), funcTmpl->GetFunction());
	}

	Handle<String> SPV8ScriptEngine::SPStringToString( SPString str )
	{
		return String::NewFromTwoByte(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (uint16_t*)str.c_str());
	}

	void SPV8ScriptEngine::Import( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
		HandleScope handleScope(isolate);
		Handle<Context> context = isolate->GetCurrentContext();

		if (args.Length() == 0) 
		{
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		// Ensure one module can only be imported once!

		Handle<String> moduleName = Handle<String>::Cast(args[0]);
		Handle<Object> loadedModules = Handle<Object>::Cast(context->Global()->GetHiddenValue(
			SPV8ScriptEngine::SPStringToString(L"_loadedModules")));

		if (loadedModules.IsEmpty())
		{
			loadedModules = Object::New();
			context->Global()->SetHiddenValue(SPV8ScriptEngine::SPStringToString(L"_loadedModules"), loadedModules);
		}

		if (loadedModules->HasOwnProperty(moduleName)) 
		{
			args.GetReturnValue().Set(loadedModules->Get(moduleName));
			return;
		}

		Handle<Value> result = SPV8ScriptEngine::GetSingleton()->EvalFile(SPV8ScriptEngine::StringToSPString(args[0]->ToString()), true);

		loadedModules->Set(moduleName, result);
		args.GetReturnValue().Set(result);
	}

	void SPV8ScriptEngine::Include( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
		HandleScope handleScope(isolate);

		if (args.Length() == 0) 
		{
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		Handle<Value> result = SPV8ScriptEngine::GetSingleton()->EvalFile(SPV8ScriptEngine::StringToSPString(args[0]->ToString()), true);
	}

	void SPV8ScriptEngine::SleepFunc( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
		HandleScope handleScope(isolate);

		int timeSpan = 0;

		if (args.Length() > 0) 
		{
			Handle<Integer> timeSpanObj = Handle<Integer>::Cast(args[0]);
			if (timeSpanObj.IsEmpty())
			{
				return;
			}

			timeSpan = timeSpanObj->Int32Value();
		}

		if (timeSpan >= 0 && !SPV8ScriptEngine::GetSingleton()->IsStopping())
		{
			Unlocker unlocker(isolate);
			Sleep(timeSpan);
			Locker locker(isolate);
		}

		return;
	}

	void SPV8ScriptEngine::SetTimeOut( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
		HandleScope handleScope(isolate);

		if (args.Length() < 2) 
		{
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		Handle<Function> func = Handle<Function>::Cast(args[0]);
		int timeMs = args[1]->Int32Value();

		args.GetReturnValue().Set(SPV8ScriptEngine::GetSingleton()->SetTimeOutFunction(func, timeMs));
	}

	void SPV8ScriptEngine::ClearTimeOut( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
		HandleScope handleScope(isolate);

		if (args.Length() < 1) 
		{
			isolate->ThrowException(Exception::TypeError(SPV8ScriptEngine::SPStringToString(L"Null Argument")));
			return;
		}

		SPV8ScriptEngine::GetSingleton()->ClearTimeOutFunction(args[0]->ToNumber());
	}

	void SPV8ScriptEngine::RunTimeOutFunc()
	{
		int currentTimeMs = timeGetTime();

		TimeOutFunctionMap::iterator iter = timeOutFunctionToRun.begin();
		list<SPPointer<Persistent<Function>>> functionToRun;

		while(iter != timeOutFunctionToRun.end())
		{
			if (iter->first <= currentTimeMs)
			{
				for (FunctionList::iterator innerIter = iter->second.begin(); innerIter != iter->second.end(); innerIter++)
				{
					TimeOutMap::iterator theIter = timeOutMap.find(*innerIter);

					if (theIter != timeOutMap.end())
					{
						functionToRun.push_back(theIter->second);
						timeOutMap.erase(timeOutMap.find(*innerIter));
					}
				}

				iter = timeOutFunctionToRun.erase(iter);
			}
			else
			{
				break;
			}
		}

		if (functionToRun.size() == 0)
		{
			return;
		}

		Locker lock(isolate);
		Isolate::Scope isolateScope(isolate);		
		HandleScope handleScope(isolate);
		Handle<Context> realContext = GetContext();
		Context::Scope contextScope(realContext);

		list<SPPointer<Persistent<Function>>>::iterator functionIter = functionToRun.begin();

		while(functionIter != functionToRun.end())
		{
			Handle<Function> func = Handle<Function>::New(isolate, **functionIter);
			func->Call(func, 0, NULL);
			functionIter++;
		}
	}

	void SPV8ScriptEngine::EvalFunc( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

		if(args.Length() < 1)
		{
			isolate->ThrowException(Exception::TypeError(
				SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
			return;
		}

		SPString scriptStr = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
		args.GetReturnValue().Set(SPV8ScriptEngine::GetSingleton()->Eval(scriptStr, true));
	}

	void SPV8ScriptEngine::EvalFileFunc( const FunctionCallbackInfo<Value>& args )
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

		if(args.Length() < 1)
		{
			isolate->ThrowException(Exception::TypeError(
				SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
			return;
		}

		SPString path = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
		args.GetReturnValue().Set(SPV8ScriptEngine::GetSingleton()->EvalFile(path, true));
	}

	void* SPV8ScriptEngine::GetAsync()
	{
		return pAsync;
	}

	Handle<String> SPV8ScriptEngine::ToJson( Handle<Value> object )
	{
		EscapableHandleScope scope(SPV8ScriptEngine::GetSingleton()->GetIsolate());
		Handle<Context> context = Context::GetCurrent();
		Handle<Object> global = context->Global();

		Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
		Handle<Function> JSON_stringify = Handle<Function>::Cast(JSON->Get(String::New("stringify")));
		Handle<Value> args[1];
		args[0] = object;

		return scope.Escape(JSON_stringify->Call(JSON, 1, args))->ToString();
	}

	Handle<Object> SPV8ScriptEngine::CopyObject( Handle<Object> object )
	{
		Handle<Object> obj = Object::New();

		const Local<Array> props = object->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = object->Get(key);

			obj->Set(key, value);
		}

		return obj;
	}

	Handle<Object> SPV8ScriptEngine::JsonParse( Handle<String> str )
	{
		EscapableHandleScope scope(SPV8ScriptEngine::GetSingleton()->GetIsolate());
		Handle<Context> context = Context::GetCurrent();
		Handle<Object> global = context->Global();

		Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
		Handle<Function> JSON_parse = Handle<Function>::Cast(JSON->Get(String::New("parse")));
		Handle<Value> args[1];
		args[0] = str;

		return Handle<Object>::Cast(scope.Escape(JSON_parse->Call(JSON, 1, args)));
	}

	Handle<v8::Function> SPV8ScriptEngine::ParseFunction( Handle<String> str )
	{
		SPString spStr = SPV8ScriptEngine::StringToSPString(str);
		spStr = L"(" + spStr + L")";
		Handle<Script> script = Script::Compile(SPV8ScriptEngine::SPStringToString(spStr));
		return Handle<v8::Function>::Cast(script->Run());
	}

	void SPV8ScriptEngine::CoverObject( Handle<Value> destObj, Handle<Value> srcObj )
	{
		const Local<Array> props = Handle<Object>::Cast(srcObj)->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = Handle<Object>::Cast(srcObj)->Get(key);
			Handle<Object>::Cast(destObj)->Set(key, value);
		}
	}
}
