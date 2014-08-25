#include "StdAfx.h"
#include "SV8TemplParticleSystem.h"
#include "SUIParticleSystemManager.h"
#include "SV8Function.h"


Handle<ObjectTemplate> SV8TemplParticleSystem::GetTemplate()
{
	Handle<ObjectTemplate> templParticleSystem = ObjectTemplate::New();
	templParticleSystem->SetInternalFieldCount(1);

	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"height"), HeightGetter, HeightSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"width"), WidthGetter, WidthSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"tex"), TexGetter, TexSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"bornXMin"), BornXMinGetter, BornXMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"bornYMin"), BornYMinGetter, BornYMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"bornXMax"), BornXMaxGetter, BornXMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"bornYMax"), BornYMaxGetter, BornYMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"liveXMin"), LiveXMinGetter, LiveXMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"liveYMin"), LiveYMinGetter, LiveYMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"liveXMax"), LiveXMaxGetter, LiveXMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"liveYMax"), LiveYMaxGetter, LiveYMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"liveTime"), LiveTimeGetter, LiveTimeSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"color"), ColorGetter, ColorSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"shootVelocityMin"), ShootVelocityMinGetter, ShootVelocityMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"shootVelocityMax"), ShootVelocityMaxGetter, ShootVelocityMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"shootRate"), ShootRateGetter, ShootRateSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"shootAngleMin"), ShootAngleMinGetter, ShootAngleMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"shootAngleMax"), ShootAngleMaxGetter, ShootAngleMaxSetter);
	
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"countMax"), CountMaxGetter, CountMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"accelerationX"), AccelerationXGetter, AccelerationXSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"accelerationY"), AccelerationYGetter, AccelerationYSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotationMin"), RotationMinGetter, RotationMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotationMax"), RotationMaxGetter, RotationMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotateRateMin"), RotateRateMinGetter, RotateRatenMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotateRateMax"), RotateRateMaxGetter, RotateRateMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"scaleMin"), ScaleMinGetter, ScaleMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"scaleMax"), ScaleMaxGetter, ScaleMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"scaleRateMin"), ScaleRateMinGetter, ScaleRateMinSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"scaleRateMax"), ScaleRateMaxGetter, ScaleRateMaxSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"fadeTime"), FadeTimeGetter, FadeTimeSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"specialRotation"), SpecialRotationGetter, SpecialRotationSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundColor"), BackgroundColorGetter, BackgroundColorSetter);
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"control"), ControlGetter, ControlSetter);

	templParticleSystem->Set(SPV8ScriptEngine::SPStringToString(L"play"), 
		FunctionTemplate::New(Play)->GetFunction());
	templParticleSystem->Set(SPV8ScriptEngine::SPStringToString(L"stop"), 
		FunctionTemplate::New(Stop)->GetFunction());
	templParticleSystem->Set(SPV8ScriptEngine::SPStringToString(L"pause"), 
		FunctionTemplate::New(Pause)->GetFunction());

	return templParticleSystem;
}

void SV8TemplParticleSystem::HeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPParticleSystemTexturePtr tex = SUIParticleSystemManager::GetSingleton()->GetParticleSystemTexture(handle);

	info.GetReturnValue().Set(tex->GetHeight());
}

void SV8TemplParticleSystem::HeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString name = SUIParticleSystemManager::GetSingleton()->GetParticleSystemName(handle);
	int width = 0;
	int height = value->Int32Value();

	SPParticleSystemTexturePtr tex = SPTextureManager::GetSingleton()->GetParticleSystem(name);
	if (tex)
	{
		width = tex->GetWidth();
	}

	SPTextureManager::GetSingleton()->CreateParticleSystemTexture(name, width, height);

}

void SV8TemplParticleSystem::WidthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPParticleSystemTexturePtr tex = SUIParticleSystemManager::GetSingleton()->GetParticleSystemTexture(handle);

	info.GetReturnValue().Set(tex->GetWidth());
}

void SV8TemplParticleSystem::WidthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString name = SUIParticleSystemManager::GetSingleton()->GetParticleSystemName(handle);
	int width = value->Int32Value();
	int height = 0;

	SPParticleSystemTexturePtr tex = SPTextureManager::GetSingleton()->GetParticleSystem(name);
	if (tex)
	{
		height = tex->GetHeight();
	}

	SPTextureManager::GetSingleton()->CreateParticleSystemTexture(name, width, height);
}

void SV8TemplParticleSystem::TexGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8TemplParticleSystem::TexSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (value->IsString())
	{
		handle->SetTexture(SPTextureManager::GetSingleton()->GetTexture(SPV8ScriptEngine::StringToSPString(value->ToString())));
	}
	else if(value->IsObject())
	{
		handle->SetTexture(SV8Function::GetTextureFromObj(value->ToObject()));
	}
}

void SV8TemplParticleSystem::BornXMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBornBoxMinX());
}

void SV8TemplParticleSystem::BornXMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBornBoxMinX(value->Int32Value());
}

void SV8TemplParticleSystem::BornYMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBornBoxMinY());
}

void SV8TemplParticleSystem::BornYMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBornBoxMinY(value->Int32Value());
}

void SV8TemplParticleSystem::BornXMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBornBoxMaxX());
}

void SV8TemplParticleSystem::BornXMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBornBoxMaxX(value->Int32Value());
}

void SV8TemplParticleSystem::BornYMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBornBoxMaxY());
}

void SV8TemplParticleSystem::BornYMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBornBoxMaxY(value->Int32Value());
}

void SV8TemplParticleSystem::LiveXMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLiveBoxMinX());
}

void SV8TemplParticleSystem::LiveXMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLiveBoxMinX(value->Int32Value());
}

void SV8TemplParticleSystem::LiveYMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLiveBoxMinY());
}

void SV8TemplParticleSystem::LiveYMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLiveBoxMinY(value->Int32Value());
}

void SV8TemplParticleSystem::LiveXMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLiveBoxMaxX());
}

void SV8TemplParticleSystem::LiveXMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLiveBoxMaxX(value->Int32Value());
}

void SV8TemplParticleSystem::LiveYMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetLiveBoxMaxY());
}

void SV8TemplParticleSystem::LiveYMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetLiveBoxMaxY(value->Int32Value());
}

void SV8TemplParticleSystem::LiveTimeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetParticleAge());
}

void SV8TemplParticleSystem::LiveTimeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetParticleAge(value->NumberValue());
}

void SV8TemplParticleSystem::ColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(handle->GetColor()));
}

void SV8TemplParticleSystem::ColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetColor(value->Int32Value());
}

void SV8TemplParticleSystem::ShootVelocityMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetVelocityMin());
}

void SV8TemplParticleSystem::ShootVelocityMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetVelocityMin(value->NumberValue());
}

void SV8TemplParticleSystem::ShootVelocityMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetVelocityMax());
}

void SV8TemplParticleSystem::ShootVelocityMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetVelocityMax(value->NumberValue());
}

void SV8TemplParticleSystem::ShootRateGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBornRate());
}

void SV8TemplParticleSystem::ShootRateSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBornRate(value->NumberValue());
}

void SV8TemplParticleSystem::ShootAngleMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetShootAngleMin());
}

void SV8TemplParticleSystem::ShootAngleMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetShootAngleMin(value->NumberValue());
}

void SV8TemplParticleSystem::ShootAngleMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetShootAngleMax());
}

void SV8TemplParticleSystem::ShootAngleMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetShootAngleMax(value->NumberValue());
}


void SV8TemplParticleSystem::CountMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetMaxNumOfParticle());
}

void SV8TemplParticleSystem::CountMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetMaxNumOfParticle(value->Int32Value());
}

void SV8TemplParticleSystem::AccelerationXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetAcceleration().x);
}

void SV8TemplParticleSystem::AccelerationXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetAcceleration(D3DXVECTOR3(value->Int32Value(), 0, handle->GetAcceleration().z));
}

void SV8TemplParticleSystem::AccelerationYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetAcceleration().z);
}

void SV8TemplParticleSystem::AccelerationYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetAcceleration(D3DXVECTOR3(handle->GetAcceleration().x, 0, value->Int32Value()));
}

void SV8TemplParticleSystem::RotationMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBeginRotateMinAngle());
}

void SV8TemplParticleSystem::RotationMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBeginRotateMinAngle(value->NumberValue());
}

void SV8TemplParticleSystem::RotationMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetBeginRotateMaxAngle());
}

void SV8TemplParticleSystem::RotationMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBeginRotateMaxAngle(value->NumberValue());
}

void SV8TemplParticleSystem::RotateRateMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetRotateSpeedMin());
}

void SV8TemplParticleSystem::RotateRatenMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetRotateSpeedMin(value->NumberValue());
}

void SV8TemplParticleSystem::RotateRateMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetRotateSpeedMax());
}

void SV8TemplParticleSystem::RotateRateMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetRotateSpeedMax(value->NumberValue());
}

void SV8TemplParticleSystem::ScaleMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetParticleMinScale());
}

void SV8TemplParticleSystem::ScaleMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetParticleMinScale(value->NumberValue());
}

void SV8TemplParticleSystem::ScaleMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetParticleMaxScale());
}

void SV8TemplParticleSystem::ScaleMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetParticleMaxScale(value->NumberValue());
}

void SV8TemplParticleSystem::ScaleRateMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetParticleScaleDeltaMin());
}

void SV8TemplParticleSystem::ScaleRateMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetParticleScaleDelta(value->NumberValue(), handle->GetParticleScaleDeltaMax());
}

void SV8TemplParticleSystem::ScaleRateMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetParticleScaleDeltaMax());
}

void SV8TemplParticleSystem::ScaleRateMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetParticleScaleDelta(handle->GetParticleScaleDeltaMin(), value->NumberValue());
}

void SV8TemplParticleSystem::FadeTimeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetFadeOutTime());
}

void SV8TemplParticleSystem::FadeTimeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetFadeOutTime(value->NumberValue());
}

void SV8TemplParticleSystem::SpecialRotationGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->GetSpecialRotation());
}

void SV8TemplParticleSystem::SpecialRotationSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetSpecialRotation(value->BooleanValue());
}

void SV8TemplParticleSystem::BackgroundColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set((int)handle->GetBackgroundColor());
}

void SV8TemplParticleSystem::BackgroundColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetBackgroundColor(value->Int32Value());
}

void SV8TemplParticleSystem::ControlGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
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

void SV8TemplParticleSystem::ControlSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
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

void SV8TemplParticleSystem::Play( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Play();
}

void SV8TemplParticleSystem::Stop( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Stop();
}

void SV8TemplParticleSystem::Pause( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->Pause();
}
