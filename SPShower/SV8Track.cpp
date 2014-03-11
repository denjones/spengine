#include "StdAfx.h"
#include "SV8Track.h"
#include "SUITrackManager.h"


Handle<ObjectTemplate> SV8Track::GetTemplate()
{
	Handle<ObjectTemplate> templTrack = ObjectTemplate::New();
	templTrack->SetInternalFieldCount(1);

	templTrack->SetAccessor(SPV8ScriptEngine::SPStringToString(L"mute"), MuteGetter, MuteSetter);
	templTrack->SetAccessor(SPV8ScriptEngine::SPStringToString(L"volume"), VolumeGetter, VolumeSetter);
	templTrack->SetAccessor(SPV8ScriptEngine::SPStringToString(L"src"), SrcGetter, SrcSetter);
	templTrack->SetAccessor(SPV8ScriptEngine::SPStringToString(L"loop"), LoopGetter, LoopSetter);
	templTrack->SetAccessor(SPV8ScriptEngine::SPStringToString(L"control"), ControlGetter, ControlSetter);

	templTrack->Set(SPV8ScriptEngine::SPStringToString(L"play"), 
		FunctionTemplate::New(Play)->GetFunction());
	templTrack->Set(SPV8ScriptEngine::SPStringToString(L"stop"), 
		FunctionTemplate::New(Stop)->GetFunction());
	templTrack->Set(SPV8ScriptEngine::SPStringToString(L"pause"), 
		FunctionTemplate::New(Pause)->GetFunction());

	return templTrack;
}

void SV8Track::MuteGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->IsMute());
}

void SV8Track::MuteSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetMute(value->BooleanValue());
}

void SV8Track::VolumeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetVolume());
}

void SV8Track::VolumeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetVolume(value->NumberValue());
}

void SV8Track::SrcGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(handle->GetSoundName()));
}

void SV8Track::SrcSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetSound(SPV8ScriptEngine::StringToSPString(value->ToString()));
}

void SV8Track::LoopGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLoopTimes());
}

void SV8Track::LoopSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLoopTimes(value->Int32Value());
}

void SV8Track::ControlGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString state = L"stop";

	if (handle->GetSound())
	{
		if (handle->GetSound()->IsPlaying())
		{
			state = L"play";
		}
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(state));
}

void SV8Track::ControlSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString state = SPV8ScriptEngine::StringToSPString(value->ToString());

	if (SPStringHelper::EqualsIgnoreCase(state, L"Play"))
	{
		handle->Play();
	}
	else if (SPStringHelper::EqualsIgnoreCase(state, L"Stop"))
	{
		handle->Stop();
	}
	else if (SPStringHelper::EqualsIgnoreCase(state, L"Pause"))
	{
		handle->Pause();
	}
}

void SV8Track::Play( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Play();
}

void SV8Track::Stop( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Stop();
}

void SV8Track::Pause( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUISoundTrackHandle handle = (SUISoundTrackHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Pause();
}
