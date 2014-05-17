#include "StdAfx.h"
#include "SUITrackManager.h"
#include "SV8Function.h"
#include "SV8TemplTrack.h"


SUITrackManager::SUITrackManager(void)
{
}


SUITrackManager::~SUITrackManager(void)
{
	if (trackTempl)
	{
		trackTempl->ClearAndLeak();
		trackTempl = NULL;
	}
}

Handle<Object> SUITrackManager::GetTrack( SUISoundTrackHandle handle )
{
	return trackHandleManager[handle];
}

Handle<Object> SUITrackManager::CreateTrack( Handle<Object> argObj )
{
	SPSoundTrackPtr track;

	bool isNameSet = false;
	SPString id = L"";

	if (SV8Function::HasProperty(L"id", argObj))
	{
		id = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"id", argObj)->ToString());
		track = SPSoundManager::GetSingleton()->GetTrack(id);

		if (!track)
		{
			track = SPSoundManager::GetSingleton()->CreateSoundTrack(id);
		}
	}
	else
	{
		track = new SPSoundTrack();
	}

	SUISoundTrackHandle handle = track.GetHandle();
	
	Local<Object> obj = Handle<Object>();

	Handle<ObjectTemplate> handleTempl = GetTrackTemplate();
	obj = handleTempl->NewInstance();

	if(!obj.IsEmpty())
	{
		obj->SetInternalField(0, External::New(track.GetHandle()));

		const Local<Array> props = argObj->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = argObj->Get(key);

			obj->Set(key, value);
		}
	}

	trackHandleManager[handle] = obj;

	return obj;
}

void SUITrackManager::Initialize()
{
	//
	// Enter
	//

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton()->GetContext();
	Context::Scope contextScope(context);

	trackTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplTrack::GetTemplate());
}

Handle<ObjectTemplate> SUITrackManager::GetTrackTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*trackTempl));
}


