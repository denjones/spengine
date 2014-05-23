#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SPGameShow.h"

void SV8Function::SaveState( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	SPString fileName = L"state.dat";
	SPString screen = L"*";

	if(args.Length() >= 0)
	{
		if(args[0]->IsObject())
		{
			Handle<Object> argObj = Handle<Object>::Cast(args[0]);

			if (HasProperty(L"file", argObj))
			{
				fileName = SPV8ScriptEngine::StringToSPString(GetProperty(L"file", argObj)->ToString());
			}

			if (HasProperty(L"screen", argObj))
			{
				screen = SPV8ScriptEngine::StringToSPString(GetProperty(L"screen", argObj)->ToString());
			}

		}
		else if (args[0]->IsString())
		{
			fileName = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
		}
	}

	((SPPointer<SPGameShow>)SPGameManager::GetSingleton()->GetGame())->SaveAsFile(fileName, screen);
}