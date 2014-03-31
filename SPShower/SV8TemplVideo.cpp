#include "StdAfx.h"
#include "SV8TemplVideo.h"
#include "SUIVideoManager.h"


Handle<ObjectTemplate> SV8TemplVideo::GetTemplate()
{
	Handle<ObjectTemplate> templVideo = ObjectTemplate::New();
	templVideo->SetInternalFieldCount(1);

	templVideo->SetAccessor(SPV8ScriptEngine::SPStringToString(L"mute"), MuteGetter, MuteSetter);
	templVideo->SetAccessor(SPV8ScriptEngine::SPStringToString(L"volume"), VolumeGetter, VolumeSetter);
	templVideo->SetAccessor(SPV8ScriptEngine::SPStringToString(L"src"), SrcGetter, SrcSetter);
	templVideo->SetAccessor(SPV8ScriptEngine::SPStringToString(L"loop"), LoopGetter, LoopSetter);
	templVideo->SetAccessor(SPV8ScriptEngine::SPStringToString(L"control"), ControlGetter, ControlSetter);

	templVideo->Set(SPV8ScriptEngine::SPStringToString(L"play"), 
		FunctionTemplate::New(Play)->GetFunction());
	templVideo->Set(SPV8ScriptEngine::SPStringToString(L"stop"), 
		FunctionTemplate::New(Stop)->GetFunction());
	templVideo->Set(SPV8ScriptEngine::SPStringToString(L"pause"), 
		FunctionTemplate::New(Pause)->GetFunction());

	return templVideo;
}

void SV8TemplVideo::MuteGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->IsMuted() == TRUE);
}

void SV8TemplVideo::MuteSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Mute(value->BooleanValue());
}

void SV8TemplVideo::VolumeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetVolume());
}

void SV8TemplVideo::VolumeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetVolume(value->NumberValue());
}

void SV8TemplVideo::SrcGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(handle->GetPath()));
}

void SV8TemplVideo::SrcSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->OpenFile(SPV8ScriptEngine::StringToSPString(value->ToString()));
}

void SV8TemplVideo::LoopGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLeftTime());
}

void SV8TemplVideo::LoopSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLoopTimes(value->Int32Value());
}

void SV8TemplVideo::ControlGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString state = L"stop";

	if (handle->IsPlaying())
	{
		state = L"play";
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(state));
}

void SV8TemplVideo::ControlSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
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

void SV8TemplVideo::Play( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Play();
}

void SV8TemplVideo::Stop( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Stop();
}

void SV8TemplVideo::Pause( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIVideoHandle handle = (SUIVideoHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Pause();
}
