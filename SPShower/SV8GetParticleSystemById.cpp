#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIScreen.h"
#include "SUIManager.h"
#include "SPGameShow.h"
#include "SUITrackManager.h"
#include "SUIVideoManager.h"
#include "SUIParticleSystemManager.h"

void SV8Function::GetParticleSystemById( const FunctionCallbackInfo<Value>& args )
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
	SPParticleSystem3DPtr ps = SPParticleSystemManager::GetSingleton()->GetParticleSystem(id);
	if(ps)
	{
		args.GetReturnValue().Set(SUIParticleSystemManager::GetSingleton()->GetParticleSystem(ps.GetHandle()));
	}
}