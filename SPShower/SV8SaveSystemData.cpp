#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SPGameShow.h"

void SV8Function::SaveSystemData( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	SPString fileName = L"system.dat";

	if(args.Length() >= 0)
	{
		if(args[0]->IsObject())
		{
			Handle<Object> argObj = Handle<Object>::Cast(args[0]);

			if (HasProperty(L"file", argObj))
			{
				fileName = SPV8ScriptEngine::StringToSPString(GetProperty(L"file", argObj)->ToString());
			}
		}
		else if (args[0]->IsString())
		{
			fileName = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
		}
	}

	((SPPointer<SPGameShow>)SPGameManager::GetSingleton()->GetGame())->SaveSystemData(fileName);
}