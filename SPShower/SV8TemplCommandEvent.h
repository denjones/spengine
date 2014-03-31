#pragma once

using namespace SPEngine;

namespace SV8TemplCommandEvent
{
	Handle<ObjectTemplate> GetTemplate();

	void RefreshGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RefreshSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RepeatGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RepeatSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ReadGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ReadSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
}
