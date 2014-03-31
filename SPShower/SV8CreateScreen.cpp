#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"

void SV8Function::CreateScreen( const FunctionCallbackInfo<Value>& args )
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
	
	if (HasProperty(L"id", argObj))
	{
		SUIScreenPtr screen;
		SPString name = SPV8ScriptEngine::StringToSPString(GetProperty(L"id", argObj)->ToString());

		if (SUIManager::GetSingleton()->IsScreenValid(name))
		{
			screen = SUIManager::GetSingleton()->GetScreen(name);
		}
		else
		{
			screen = new SUIScreen();
			screen->SetName(name);
			SUIManager::GetSingleton()->AddScreen(screen);
		}

		if (HasProperty(L"popUp", argObj))
		{
			screen->SetPopUp(GetProperty(L"popUp", argObj)->BooleanValue());
		}

		if (HasProperty(L"backgroundColor", argObj))
		{
			screen->SetBackgroundColor(GetProperty(L"backgroundColor", argObj)->Int32Value());
		}

		args.GetReturnValue().Set(screen->GetV8Obj());

		//SUIManager::GetSingleton()->FocusScreen(name);
	}
}