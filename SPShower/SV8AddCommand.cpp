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
	SV8ScriptManager::GetSingleton()->AddCommand(new SV8ScriptCommand(function));
	
}