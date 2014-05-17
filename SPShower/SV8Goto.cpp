#include "StdAfx.h"
#include "SV8Function.h"
#include "SV8ScriptManager.h"

void SV8Function::Goto( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(args[0]);

	SPString fileName = L"";
	SPString tag = L"";

	if (HasProperty(L"file", argObj))
	{
		fileName = SPV8ScriptEngine::StringToSPString(GetProperty(L"file", argObj)->ToString());
	}
	else
	{
		Handle<StackFrame> stackFrame = v8::StackTrace::CurrentStackTrace(1)->GetFrame(0);
		fileName = SPV8ScriptEngine::StringToSPString(stackFrame->GetScriptName());
	}

	if (HasProperty(L"tag", argObj))
	{
		tag = SPV8ScriptEngine::StringToSPString(GetProperty(L"tag", argObj)->ToString());
	}

	SV8ScriptManager::GetSingleton()->Goto(fileName, tag);
}