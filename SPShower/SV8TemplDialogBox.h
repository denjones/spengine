#pragma once

using namespace SPEngine;

namespace SV8TemplDialogBox
{
	Handle<ObjectTemplate> GetTemplate();

	void SpeedGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SpeedSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void NextLineImageGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void NextLineImageSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void NextPageImageGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void NextPageImageSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void Next( const FunctionCallbackInfo<Value>& args );
	void IsDisplaying( const FunctionCallbackInfo<Value>& args );
	void IsAllDisplayed( const FunctionCallbackInfo<Value>& args );
	void MarkNextLine( const FunctionCallbackInfo<Value>& args );
	void MarkNextPage( const FunctionCallbackInfo<Value>& args );
}
