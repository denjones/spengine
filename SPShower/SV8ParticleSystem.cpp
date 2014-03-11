#include "StdAfx.h"
#include "SV8ParticleSystem.h"
#include "SUIParticleSystemManager.h"
#include "SV8Function.h"


Handle<ObjectTemplate> SV8ParticleSystem::GetTemplate()
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
	templParticleSystem->SetAccessor(SPV8ScriptEngine::SPStringToString(L"countMin"), CountMinGetter, CountMinSetter);
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

void SV8ParticleSystem::HeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPParticleSystemTexturePtr tex = SUIParticleSystemManager::GetSingleton().GetParticleSystemTexture(handle);

	info.GetReturnValue().Set(tex->GetHeight());
}

void SV8ParticleSystem::HeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString name = SUIParticleSystemManager::GetSingleton().GetParticleSystemName(handle);
	int width = 0;
	int height = value->Int32Value();

	SPParticleSystemTexturePtr tex = SPTextureManager::GetSingleton().GetParticleSystem(name);
	if (tex)
	{
		width = tex->GetWidth();
	}

	SPTextureManager::GetSingleton().CreateParticleSystemTexture(name, width, height);

}

void SV8ParticleSystem::WidthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPParticleSystemTexturePtr tex = SUIParticleSystemManager::GetSingleton().GetParticleSystemTexture(handle);

	info.GetReturnValue().Set(tex->GetWidth());
}

void SV8ParticleSystem::WidthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString name = SUIParticleSystemManager::GetSingleton().GetParticleSystemName(handle);
	int width = value->Int32Value();
	int height = 0;

	SPParticleSystemTexturePtr tex = SPTextureManager::GetSingleton().GetParticleSystem(name);
	if (tex)
	{
		height = tex->GetHeight();
	}

	SPTextureManager::GetSingleton().CreateParticleSystemTexture(name, width, height);
}

void SV8ParticleSystem::TexGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8ParticleSystem::TexSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->SetTexture(SV8Function::GetTextureFromObj(value->ToObject()));
}

void SV8ParticleSystem::BornXMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornXMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornYMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornYMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornXMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornXMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornYMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BornYMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveXMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveXMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveYMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveYMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveXMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveXMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveYMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveYMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveTimeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::LiveTimeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootVelocityMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootVelocityMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootVelocityMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootVelocityMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootRateGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootRateSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootAngleMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootAngleMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootAngleMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ShootAngleMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::CountMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	
}

void SV8ParticleSystem::CountMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8ParticleSystem::CountMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::CountMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::AccelerationXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::AccelerationXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::AccelerationYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::AccelerationYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotationMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotationMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotationMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotationMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotateRateMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotateRatenMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotateRateMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::RotateRateMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleRateMinGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleRateMinSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleRateMaxGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ScaleRateMaxSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::FadeTimeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::FadeTimeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::SpecialRotationGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::SpecialRotationSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BackgroundColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::BackgroundColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ControlGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::ControlSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::Play( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::Stop( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8ParticleSystem::Pause( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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
