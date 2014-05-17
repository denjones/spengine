#include "StdAfx.h"
#include "SV8Function.h"
#include "SV8ScriptManager.h"

void SV8Function::AddCommand( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Value> value = args[0];
	if (!value->IsFunction())
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Function> function = Handle<Function>::Cast(args[0]);

	int stackLimit = 10;
	Handle<StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(stackLimit);
	
	SPString functionName = L"";
	SPString file = L"";
	int col = 0;
	int line = 0;

	for (int i = 0; i < stackTrace->GetFrameCount(); i++)
	{
		Handle<StackFrame> stackFrame = stackTrace->GetFrame(i);
		line = stackFrame->GetLineNumber();
		col = stackFrame->GetColumn();
		functionName = SPV8ScriptEngine::StringToSPString(stackFrame->GetFunctionName());
		file = SPV8ScriptEngine::StringToSPString(stackFrame->GetScriptName());
		if (functionName == L"")
		{
			break;
		}
	}
	SV8ScriptManager::GetSingleton()->AddCommand(new SV8ScriptCommand(function, line, col, file));
	
}