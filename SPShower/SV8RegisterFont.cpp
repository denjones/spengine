#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"

void SV8Function::RegisterFont( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(args[0]);

	if (HasProperty(L"file", argObj))
	{
		SPString fileName = SPV8ScriptEngine::StringToSPString(GetProperty(L"file", argObj)->ToString());
		SPFontManager::GetSingleton().AddExtendedFont(fileName);
	}
}