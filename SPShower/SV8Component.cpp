#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Component.h"

Handle<ObjectTemplate> SV8Component::GetTemplate()
{
	Handle<ObjectTemplate> templComponent = ObjectTemplate::New();
	templComponent->SetInternalFieldCount(1);

	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"id"), IdGetter, IdSetter);

	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"display"), DisplayGetter, DisplaySetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"absolute"), AbsoluteGetter, AbsoluteSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"depth"), DepthGetter, DepthSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"width"), WidthGetter, WidthSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"height"), HeightGetter, HeightSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"x"), XGetter, XSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"y"), YGetter, YSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"opacity"), OpacityGetter, OpacitySetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotation"), RotationGetter, RotationSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotationCenterX"), RotationCenterXGetter, RotationCenterXSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"rotationCenterY"), RotationCenterYGetter, RotationCenterYSetter);

	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundImage"), BGImageGetter, BGImageSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundColor"), BGColorGetter, BGColorSetter);	
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundX"), BGXGetter, BGXSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundY"), BGYGetter, BGYSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundFillMode"), BGFillModeGetter, BGFillModeSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundPositionMode"), BGPositionModeGetter, BGPositionModeSetter);

	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onClick"), OnClickGetter, OnClickSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onDClick"), OnDClickGetter, OnDClickSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseUp"), OnMouseUpGetter, OnMouseUpSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseDown"), OnMouseDownGetter, OnMouseDownSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseScroll"), OnMouseScrollGetter, OnMouseScrollSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseOver"), OnMouseOverGetter, OnMouseOverSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseIn"), OnMouseInGetter, OnMouseInSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onMouseOut"), OnMouseOutGetter, OnMouseOutSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onKeyPress"), OnKeyPressGetter, OnKeyPressSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onKeyUp"), OnKeyUpGetter, OnKeyUpSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onKeyDown"), OnKeyDownGetter, OnKeyDownSetter);

	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchClick"), CatchClickGetter, CatchClickSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchDClick"), CatchDClickGetter, CatchDClickSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseUp"), CatchMouseUpGetter, CatchMouseUpSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseDown"), CatchMouseDownGetter, CatchMouseDownSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseScroll"), CatchMouseScrollGetter, CatchMouseScrollSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseOver"), CatchMouseOverGetter, CatchMouseOverSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseIn"), CatchMouseInGetter, CatchMouseInSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchMouseOut"), CatchMouseOutGetter, CatchMouseOutSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchKeyPress"), CatchKeyPressGetter, CatchKeyPressSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchKeyUp"), CatchKeyUpGetter, CatchKeyUpSetter);
	templComponent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"catchKeyDown"), CatchKeyDownGetter, CatchKeyDownSetter);

	templComponent->Set(SPV8ScriptEngine::SPStringToString(L"appendChild"), 
		FunctionTemplate::New(AppendChild)->GetFunction());
	templComponent->Set(SPV8ScriptEngine::SPStringToString(L"removeChild"), 
		FunctionTemplate::New(RemoveChild)->GetFunction());

	return templComponent;
}

void SV8Component::ComponentGetter(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
	Local<Object> obj = Handle<Object>();

	Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton().GetScreenTemplate();
	obj = handleTempl->NewInstance();

	if(!obj.IsEmpty() && SUIManager::GetSingletonPtr())
	{
		obj->SetInternalField(0, External::New(
			SPV8ScriptEngine::GetSingleton().GetIsolate(), 
			SUIManager::GetSingleton().GetCurrentScreen()));
		info.GetReturnValue().Set(obj);
	}

	return ;
}

void SV8Component::ComponentSetter(
	Local<String> property,
	Local<Value> value,
	const PropertyCallbackInfo<void>& info) 
{
	return;
}

void SV8Component::GetComponentProperty( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);

	
}

void SV8Component::SetComponentProperty( Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);

	
}

void SV8Component::IdGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(component->GetName()));
}

void SV8Component::IdSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SUIScreen* screen = component->GetScreen();
	SUIComponentPtr componentPtr = screen->GetPersistentComponent(component);
	if (componentPtr);
	{
		screen->RemoveComponent(componentPtr->GetName());
		componentPtr->SetName(SPV8ScriptEngine::StringToSPString(value->ToString()));
		screen->AddComponent(componentPtr);		
	}
}

void SV8Component::DisplayGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Boolean::New(isolate, component->IsDisplay()));
}

void SV8Component::DisplaySetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (!value->BooleanValue())
	{
		component->Hide();
	}
	else
	{
		component->Unhide();
	}
}

void SV8Component::AbsoluteGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Boolean::New(isolate, component->IsAbsoluteRender()));
}

void SV8Component::AbsoluteSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetAbsoluteRender(value->BooleanValue());
}

void SV8Component::DepthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetLayer()));
}

void SV8Component::DepthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetLayer(value->NumberValue());
}

void SV8Component::WidthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetWidth()));
}

void SV8Component::WidthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetWidth(value->NumberValue());
}

void SV8Component::HeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetHeight()));
}

void SV8Component::HeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetHeight(value->NumberValue());
}

void SV8Component::XGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetPosition().x));
}

void SV8Component::XSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPositionX(value->NumberValue());
}

void SV8Component::YGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetPosition().y));
}

void SV8Component::YSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPositionY(value->NumberValue());
}

void SV8Component::OpacityGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetTransparency()));
}

void SV8Component::OpacitySetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetTransparency(value->NumberValue());
}

void SV8Component::RotationGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetRotation()));
}

void SV8Component::RotationSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetRotation(value->NumberValue());
}

void SV8Component::RotationCenterXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetRotationCenter().x));
}

void SV8Component::RotationCenterXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetRotationCenterX(value->NumberValue());
}

void SV8Component::RotationCenterYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(isolate, component->GetRotationCenter().y));
}

void SV8Component::RotationCenterYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetRotationCenterY(value->NumberValue());
}

void SV8Component::BGImageGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (component->GetBackgroundImage())
	{
		info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(component->GetBackgroundImage()->GetPath()));
	}
	else
	{
		info.GetReturnValue().Set(Undefined(isolate));
	}	
}

void SV8Component::BGImageSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundImage(SPTextureManager::GetSingleton().GetTexture(
		SPV8ScriptEngine::StringToSPString(value->ToString())));
}

void SV8Component::BGColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetBackgroundColor()));
}

void SV8Component::BGColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundColor(value->Int32Value());
}

void SV8Component::BGXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetBackgroundX()));
}

void SV8Component::BGXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundX(value->Int32Value());
}

void SV8Component::BGYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, component->GetBackgroundY()));
}

void SV8Component::BGYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundY(value->Int32Value());
}

void SV8Component::BGFillModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(
		SUIProperties::BackgroundModeToString(component->GetBackgroundMode())));
}

void SV8Component::BGFillModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundMode(SUIProperties::StringToBackgroundMode(
		SPV8ScriptEngine::StringToSPString(value->ToString())));
}

void SV8Component::BGPositionModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(
		SUIProperties::BackgroundPositionToString(component->GetBackgroundPositionMode())));
}

void SV8Component::BGPositionModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetBackgroundPositionMode(SUIProperties::StringToBackgroundPosition(
		SPV8ScriptEngine::StringToSPString(value->ToString())));
}

void SV8Component::OnClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnDClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnDClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseScrollGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseScrollSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseOverGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseOverSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseInGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseInSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnMouseOutGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnMouseOutSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnKeyPressGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnKeyPressSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnKeyUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnKeyUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::OnKeyDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::OnKeyDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchDClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchDClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseScrollGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseScrollSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseOverGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseOverSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseInGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseInSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchMouseOutGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchMouseOutSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchKeyPressGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchKeyPressSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchKeyUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchKeyUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::CatchKeyDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Component::CatchKeyDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Component::AppendChild( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (args.Length() == 0)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	Handle<External> fieldChild = Handle<External>::Cast(Handle<Object>::Cast(args[0])->GetInternalField(0));
	SUIComponent* child = (SUIComponent*)fieldChild->Value();

	if (child == NULL)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	SUIScreen* screenFather = component->GetScreen();
	SUIScreen* screenChild = child->GetScreen();

	if (screenFather != screenChild)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Components are not in the same screen.")));
		return;
	}

	component->AddChild(screenFather->GetPersistentComponent(child));
	child->SetFather(screenFather->GetPersistentComponent(component));
}

void SV8Component::RemoveChild( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (args.Length() == 0)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	Handle<External> fieldChild = Handle<External>::Cast(Handle<Object>::Cast(args[0])->GetInternalField(0));
	SUIComponent* child = (SUIComponent*)fieldChild->Value();

	if (child == NULL)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	SUIScreen* screenFather = component->GetScreen();
	SUIScreen* screenChild = child->GetScreen();

	if (screenFather != screenChild)
	{
		isolate->ThrowException(
			Exception::Error(SPV8ScriptEngine::SPStringToString(L"Components are not in the same screen.")));
		return;
	}

	component->RemoveChild(screenFather->GetPersistentComponent(child));
	child->SetFather(NULL);
}

void SV8Component::InsertBefore( const FunctionCallbackInfo<Value>& args )
{

}

void SV8Component::AddAnimation( const FunctionCallbackInfo<Value>& args )
{

}

void SV8Component::AddEffect( const FunctionCallbackInfo<Value>& args )
{

}
