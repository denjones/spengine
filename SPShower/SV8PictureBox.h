#pragma once

using namespace SPEngine;

namespace SV8PictureBox
{
	Handle<ObjectTemplate> GetTemplate();

	void FillModeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void FillModeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PositionModeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PositionModeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PositionXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PositionXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PositionYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PositionYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void SetBaseImage( const FunctionCallbackInfo<Value>& args );
	//void MixImage( const FunctionCallbackInfo<Value>& args );
}
