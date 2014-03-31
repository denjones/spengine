#pragma once

using namespace SPEngine;

namespace SV8TemplEvent
{
	Handle<ObjectTemplate> GetTemplate();

	void KeyGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void KeySetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AbsoluteXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AbsoluteXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AbsoluteYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AbsoluteYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void XGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void XSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void YGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void YSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void MovementXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void MovementXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void MovementYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void MovementYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ReturnValueGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ReturnValueSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
}
