#pragma once

using namespace SPEngine;

namespace SV8TemplScroll
{
	Handle<ObjectTemplate> GetTemplate();

	void ScrollPositionGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ScrollPositionSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void DirectionGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void DirectionSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void MaxCountGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void MaxCountSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnBoundaryReachGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnBoundaryReachSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ScrollBy( const FunctionCallbackInfo<Value>& args );
	void Clear( const FunctionCallbackInfo<Value>& args );
}
