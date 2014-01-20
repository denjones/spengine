#pragma once

using namespace SPEngine;

namespace SV8Component
{
	Handle<ObjectTemplate> GetTemplate();

	//
	// Properties Get/Setter
	//

	void ComponentGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void ComponentSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void GetComponentProperty(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void SetComponentProperty(Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info);

	void IdGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void IdSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void DisplayGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void DisplaySetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void AbsoluteGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void AbsoluteSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void DepthGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void DepthSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void WidthGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void WidthSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void HeightGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void HeightSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void XGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void XSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void YGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void YSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OpacityGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OpacitySetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotationGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotationSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotationCenterXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotationCenterXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void RotationCenterYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void RotationCenterYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGImageGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGImageSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGColorGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGColorSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGXGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGXSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGYGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGYSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGFillModeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGFillModeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void BGPositionModeGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void BGPositionModeSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnClickGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnClickSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnDClickGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnDClickSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseUpGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseUpSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseDownGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseDownSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseScrollGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseScrollSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseOverGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseOverSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseInGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseInSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnMouseOutGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnMouseOutSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnKeyPressGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnKeyPressSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnKeyUpGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnKeyUpSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void OnKeyDownGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void OnKeyDownSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchClickGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchClickSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchDClickGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchDClickSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseUpGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseUpSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseDownGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseDownSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseScrollGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseScrollSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseOverGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseOverSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseInGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseInSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchMouseOutGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchMouseOutSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchKeyPressGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchKeyPressSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchKeyUpGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchKeyUpSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	void CatchKeyDownGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	void CatchKeyDownSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);

	//
	// Methods
	//

	void AppendChild( const FunctionCallbackInfo<Value>& args );
	void RemoveChild( const FunctionCallbackInfo<Value>& args );
	void InsertBefore( const FunctionCallbackInfo<Value>& args );
}