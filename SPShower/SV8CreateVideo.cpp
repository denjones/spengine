#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SUIVideoManager.h"

void SV8Function::CreateVideo( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (args.Length() == 0)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	args.GetReturnValue().Set(SUIVideoManager::GetSingleton()->CreateVideo(args[0]->ToObject()));
}