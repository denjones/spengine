#pragma once

using namespace SPEngine;

namespace SV8PictureBox
{
	Handle<ObjectTemplate> GetTemplate();

	void BasePicture(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SpeedSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void NextLineImageGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void NextLineImageSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void NextPageImageGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void NextPageImageSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void SetPicture( const FunctionCallbackInfo<Value>& args );
	void SetVideo( const FunctionCallbackInfo<Value>& args );
	void SetParticleSystem( const FunctionCallbackInfo<Value>& args );
}
