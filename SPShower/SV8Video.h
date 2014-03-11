#pragma once

using namespace SPEngine;

namespace SV8Video
{
	Handle<ObjectTemplate> GetTemplate();

	void MuteGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void MuteSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void VolumeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void VolumeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void SrcGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SrcSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LoopGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LoopSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ControlGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ControlSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void Play( const FunctionCallbackInfo<Value>& args );
	void Stop( const FunctionCallbackInfo<Value>& args );
	void Pause( const FunctionCallbackInfo<Value>& args );
}
