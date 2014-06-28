#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SPGameShow.h"
#include "SUITrackManager.h"
#include "SUIVideoManager.h"

void SV8Function::GetVideoById( const FunctionCallbackInfo<Value>& args )
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
	SPVideoPtr video = SPVideoManager::GetSingleton()->GetVideo(id);
	if(video)
	{
		args.GetReturnValue().Set(SUIVideoManager::GetSingleton()->GetVideo(video.GetHandle()));
	}
}