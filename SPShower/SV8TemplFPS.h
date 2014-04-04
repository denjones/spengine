#pragma once

using namespace SPEngine;

namespace SV8TemplFPS
{
	Handle<ObjectTemplate> GetTemplate();

	void DisplayGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void DisplaySetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PositionGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PositionSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LockGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LockSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
}
