#pragma once

using namespace SPEngine;

namespace SV8TemplTextBox
{
	Handle<ObjectTemplate> GetTemplate();

	void TextGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void TextSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LineSpaceGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LineSpaceSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void LetterSpaceGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void LetterSpaceSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PaddingTopGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PaddingTopSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PaddingRightGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PaddingRightSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PaddingBottomGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PaddingBottomSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void PaddingLeftGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void PaddingLeftSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void ColorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ColorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AutoHeightGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AutoHeightSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void TextEffectFrontGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void TextEffectFrontSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void TextEffectBackGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void TextEffectBackSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void FontGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void FontSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AddText( const FunctionCallbackInfo<Value>& args );
}
