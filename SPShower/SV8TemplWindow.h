#pragma once

using namespace SPEngine;

namespace SV8TemplWindow
{
	Handle<ObjectTemplate> GetTemplate();

	void WindowGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void WindowSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void TitleGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void TitleSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void WidthGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void WidthSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void HeightGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void HeightSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void FullScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void FullScreenSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CursorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CursorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnExitGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnExitSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void Resize( const FunctionCallbackInfo<Value>& args );
}