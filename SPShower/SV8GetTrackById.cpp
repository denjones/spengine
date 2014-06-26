#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SPGameShow.h"
#include "SUITrackManager.h"

void SV8Function::GetTrackById( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	if (args.Length() == 0)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	SPString id = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
	SPSoundTrackPtr track = SPSoundManager::GetSingleton()->GetTrack(id);
	if(track)
	{
		args.GetReturnValue().Set(SUITrackManager::GetSingleton()->GetTrack(track.GetHandle()));
	}
}