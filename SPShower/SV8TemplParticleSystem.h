#pragma once

using namespace SPEngine;

namespace SV8TemplParticleSystem
{
	Handle<ObjectTemplate> GetTemplate();

	void HeightGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void HeightSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void WidthGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void WidthSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void TexGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void TexSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BornXMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BornXMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BornYMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BornYMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BornXMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BornXMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BornYMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BornYMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LiveXMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LiveXMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LiveYMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LiveYMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LiveXMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LiveXMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LiveYMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LiveYMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LiveTimeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LiveTimeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ColorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ColorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ShootVelocityMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ShootVelocityMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ShootVelocityMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ShootVelocityMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ShootRateGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ShootRateSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ShootAngleMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ShootAngleMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ShootAngleMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ShootAngleMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CountMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CountMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CountMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CountMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AccelerationXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AccelerationXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AccelerationYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AccelerationYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotationMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotationMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotationMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotationMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotateRateMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotateRatenMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotateRateMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotateRateMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ScaleMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScaleMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ScaleMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScaleMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ScaleRateMinGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScaleRateMinSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ScaleRateMaxGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScaleRateMaxSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void FadeTimeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void FadeTimeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void SpecialRotationGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SpecialRotationSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BackgroundColorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BackgroundColorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ControlGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ControlSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void Play( const FunctionCallbackInfo<Value>& args );
	void Stop( const FunctionCallbackInfo<Value>& args );
	void Pause( const FunctionCallbackInfo<Value>& args );
}
