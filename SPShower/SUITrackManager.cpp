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
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	return Handle<Object>::New(isolate, *trackHandleManager[handle]);
}

Handle<Object> SUITrackManager::CreateTrack( Handle<Object> argObj )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

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

	trackHandleManager[handle] = new Persistent<Object>(isolate, obj);

	obj->Set(SPV8ScriptEngine::SPStringToString(L"control"), argObj->Get(SPV8ScriptEngine::SPStringToString(L"control")));

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

Handle<Object> SUITrackManager::SaveAsObj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<Object> trackManagerObj = Object::New();
	map<SUISoundTrackHandle, SPPointer<Persistent<Object>>>::iterator iter = trackHandleManager.begin();
	while(iter != trackHandleManager.end())
	{
		Handle<Object> trackObj = Handle<Object>::New(isolate, *iter->second);
		trackManagerObj->Set(trackObj->Get(SPV8ScriptEngine::SPStringToString(L"id")), trackObj);
		iter++;
	}
	return trackManagerObj;
}

void SUITrackManager::LoadFromObj( Handle<Object> obj )
{
	const Local<Array> props = obj->GetPropertyNames();
	const uint32_t length = props->Length();
	for (uint32_t i = 0; i < length; i++)
	{
		const Local<Value> key = props->Get(i);
		const Local<Value> value = obj->Get(key);

		CreateTrack(Handle<Object>::Cast(value));
	}
}


