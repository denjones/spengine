#pragma once

using namespace SPEngine;

namespace SV8Screen
{
	Handle<ObjectTemplate> GetTemplate();

	void ScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScreenSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void GetScreenProperty(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SetScreenProperty(Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info);

	void RootGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RootSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PopUpGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PopUpSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void IdGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void IdSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGColorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGColorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void Focus( const FunctionCallbackInfo<Value>& args );
	void CreateComponent( const FunctionCallbackInfo<Value>& args );
	void GetComponentById( const FunctionCallbackInfo<Value>& args );
}