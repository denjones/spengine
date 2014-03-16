#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Component.h"
#include "SV8Function.h"
#include "SUIV8FunctionEventHandler.h"

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

	templComponent->Set(SPV8ScriptEngine::SPStringToString(L"addAnimation"), 
		FunctionTemplate::New(AddAnimation)->GetFunction());
	templComponent->Set(SPV8ScriptEngine::SPStringToString(L"addEffect"), 
		FunctionTemplate::New(AddEffect)->GetFunction());

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
			//SPV8ScriptEngine::GetSingleton().GetIsolate(), 
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
	if (componentPtr)
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

	info.GetReturnValue().Set(component->IsDisplay());
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

	info.GetReturnValue().Set(component->IsAbsoluteRender());
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

	info.GetReturnValue().Set(Integer::New(component->GetWidth()));
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

	info.GetReturnValue().Set(Integer::New(component->GetHeight()));
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

	info.GetReturnValue().Set(Integer::New(component->GetTransparency()));
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

	if (value->IsNull() || value->IsUndefined())
	{
		component->SetBackgroundImage(NULL);
		return;
	}

	SPTexturePtr tex = NULL;

	if (value->IsString())
	{
		SPString name = SPV8ScriptEngine::StringToSPString(value->ToString());
		tex = SPTextureManager::GetSingleton().GetTexture(name);
	}
	else
	{
		Handle<Object> argObj = Handle<Object>::Cast(value);
		tex = SV8Function::GetTextureFromObj(argObj);
	}

	component->SetBackgroundImage(tex);
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

	info.GetReturnValue().Set(Integer::New(component->GetBackgroundColor()));
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

	info.GetReturnValue().Set(component->GetBackgroundX());
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

	info.GetReturnValue().Set(component->GetBackgroundY());
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
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIComponent* component = (SUIComponent*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	if (component->onMouseClick)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseClick))->GetFunction());
	}
}

void SV8Component::OnClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseClick = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnDClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseDClick)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseDClick))->GetFunction());
	}
}

void SV8Component::OnDClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseDClick = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseUp)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseUp))->GetFunction());
	}
}

void SV8Component::OnMouseUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseUp = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseDown)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseDown))->GetFunction());
	}
}

void SV8Component::OnMouseDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseDown = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseScrollGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseScroll)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseScroll))->GetFunction());
	}
}

void SV8Component::OnMouseScrollSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseScroll = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseOverGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouse)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouse))->GetFunction());
	}
}

void SV8Component::OnMouseOverSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouse = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseInGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseIn)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseIn))->GetFunction());
	}
}

void SV8Component::OnMouseInSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseIn = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnMouseOutGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onMouseOut)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onMouseOut))->GetFunction());
	}
}

void SV8Component::OnMouseOutSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onMouseOut = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnKeyPressGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onKeyPress)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onKeyPress))->GetFunction());
	}
}

void SV8Component::OnKeyPressSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onKeyPress = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnKeyUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onKeyUp)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onKeyUp))->GetFunction());
	}
}

void SV8Component::OnKeyUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onKeyUp = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::OnKeyDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->onKeyDown)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->onKeyDown))->GetFunction());
	}
}

void SV8Component::OnKeyDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->onKeyDown = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseClick)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseClick))->GetFunction());
	}
}

void SV8Component::CatchClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseClick = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchDClickGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseDClick)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseDClick))->GetFunction());
	}
}

void SV8Component::CatchDClickSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseDClick = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseUp)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseUp))->GetFunction());
	}
}

void SV8Component::CatchMouseUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseUp = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseDown)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseDown))->GetFunction());
	}
}

void SV8Component::CatchMouseDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseDown = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseScrollGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseScroll)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseScroll))->GetFunction());
	}
}

void SV8Component::CatchMouseScrollSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseScroll = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseOverGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouse)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouse))->GetFunction());
	}
}

void SV8Component::CatchMouseOverSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouse = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseInGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseIn)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseIn))->GetFunction());
	}
}

void SV8Component::CatchMouseInSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseIn = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchMouseOutGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchMouseOut)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchMouseOut))->GetFunction());
	}
}

void SV8Component::CatchMouseOutSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchMouseOut = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchKeyPressGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchKeyPress)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchKeyPress))->GetFunction());
	}
}

void SV8Component::CatchKeyPressSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchKeyPress = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchKeyUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchKeyUp)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchKeyUp))->GetFunction());
	}
}

void SV8Component::CatchKeyUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchKeyUp = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
}

void SV8Component::CatchKeyDownGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
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

	if (component->catchKeyDown)
	{
		info.GetReturnValue().Set(((SUIV8FunctionEventHandlerPtr)(component->catchKeyDown))->GetFunction());
	}
}

void SV8Component::CatchKeyDownSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
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

	component->catchKeyDown = new SUIV8FunctionEventHandler(Handle<v8::Function>::Cast(value), component->GetV8Obj());
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

	SUIAnimationPtr animation = new SUIAnimation();

	animation->SetStartPoint(component->GetTargetProperties());	

	Handle<Object> argObj = args[0]->ToObject();

	if (SV8Function::HasProperty(L"time", argObj))
	{
		float time = SV8Function::GetProperty(L"time", argObj)->NumberValue();
		animation->SetTime(time);
	}

	SUIProperties endPoint = component->GetTargetProperties();

	//component->SetProperties(args);

	if (SV8Function::HasProperty(L"layer", argObj))
	{
		endPoint.layer = SV8Function::GetProperty(L"layer", argObj)->NumberValue();
	}

	if (SV8Function::HasProperty(L"width", argObj))
	{
		int width = SV8Function::GetProperty(L"width", argObj)->Int32Value();
		endPoint.rectangle.Width = width;
	}

	if (SV8Function::HasProperty(L"height", argObj))
	{
		int height = SV8Function::GetProperty(L"height", argObj)->Int32Value();
		endPoint.rectangle.Height = height;
	}

	if (SV8Function::HasProperty(L"x", argObj))
	{
		int x = SV8Function::GetProperty(L"x", argObj)->Int32Value();
		endPoint.rectangle.X = x;
	}		

	if (SV8Function::HasProperty(L"xDelta", argObj))
	{
		int x =  SV8Function::GetProperty(L"xDelta", argObj)->Int32Value();
		endPoint.rectangle.X += x;
	}	

	if (SV8Function::HasProperty(L"y", argObj))
	{
		int y =  SV8Function::GetProperty(L"y", argObj)->Int32Value();
		endPoint.rectangle.Y = y;
	}

	if (SV8Function::HasProperty(L"yDelta", argObj))
	{
		int y = SV8Function::GetProperty(L"yDelta", argObj)->Int32Value();
		endPoint.rectangle.Y += y;
	}

	if (SV8Function::HasProperty(L"rotation", argObj))
	{
		float rotation = SV8Function::GetProperty(L"rotation", argObj)->NumberValue();
		endPoint.rotation = rotation;
	}

	if (SV8Function::HasProperty(L"rotationDelta", argObj))
	{
		float rotation = SV8Function::GetProperty(L"rotationDelta", argObj)->NumberValue();
		endPoint.rotation += rotation;
	}

	if (SV8Function::HasProperty(L"rotationCenterX", argObj))
	{
		float x =  SV8Function::GetProperty(L"rotationCenterX", argObj)->NumberValue();
		endPoint.rotationCenter.x = x;
	}

	if (SV8Function::HasProperty(L"rotationCenterXDelta", argObj))
	{
		float x = SV8Function::GetProperty(L"rotationCenterXDelta", argObj)->NumberValue();
		endPoint.rotationCenter.x += x;
	}

	if (SV8Function::HasProperty(L"rotationCenterY", argObj))
	{
		float y = SV8Function::GetProperty(L"rotationCenterY", argObj)->NumberValue();
		endPoint.rotationCenter.y = y;
	}

	if (SV8Function::HasProperty(L"rotationCenterYDelta", argObj))
	{
		float y = SV8Function::GetProperty(L"rotationCenterYDelta", argObj)->NumberValue();
		endPoint.rotationCenter.y += y;
	}

	if (SV8Function::HasProperty(L"backgroundImage", argObj))
	{
		endPoint.backgroundImage = SV8Function::GetTextureFromObj(SV8Function::GetProperty(L"backgroundImage", argObj)->ToObject());
	}

	if (SV8Function::HasProperty(L"backgroundColor", argObj))
	{
		endPoint.backgroundColor = SV8Function::GetProperty(L"backgroundColor", argObj)->Int32Value();
	}

	if (SV8Function::HasProperty(L"backgroundX", argObj))
	{
		endPoint.backgroundX = SV8Function::GetProperty(L"backgroundX", argObj)->Int32Value();
	}

	if (SV8Function::HasProperty(L"backgroundXDelta", argObj))
	{
		endPoint.backgroundX += SV8Function::GetProperty(L"backgroundXDelta", argObj)->Int32Value();
	}

	if (SV8Function::HasProperty(L"backgroundY", argObj))
	{
		endPoint.backgroundY = SV8Function::GetProperty(L"backgroundY", argObj)->Int32Value();
	}

	if (SV8Function::HasProperty(L"backgroundYDelta", argObj))
	{
		endPoint.backgroundY += SV8Function::GetProperty(L"backgroundYDelta", argObj)->Int32Value();
	}

	if (SV8Function::HasProperty(L"transparency", argObj))
	{
		endPoint.transparency = SV8Function::GetProperty(L"transparency", argObj)->NumberValue();
	}

	if (SV8Function::HasProperty(L"transparencyDelta", argObj))
	{
		endPoint.transparency +=  SV8Function::GetProperty(L"transparencyDelta", argObj)->NumberValue();
	}

	if (SV8Function::HasProperty(L"canSkip", argObj))
	{
		animation->SetCanSkip(SV8Function::GetProperty(L"transparencyDelta", argObj)->BooleanValue());
	}

	if (SV8Function::HasProperty(L"replay", argObj))
	{
		SPString style = SPV8ScriptEngine::StringToSPString(
			SV8Function::GetProperty(L"transparencyDelta", argObj)->ToString());

		if (SPStringHelper::EqualsIgnoreCase(style, L"SlowIn") || 
			SPStringHelper::EqualsIgnoreCase(style, L"FastOut"))
		{
			animation->SetType(SUITransition::SlowIn);
		}
		else if (SPStringHelper::EqualsIgnoreCase(style, L"SlowOut") || 
			SPStringHelper::EqualsIgnoreCase(style, L"FastIn"))
		{
			animation->SetType(SUITransition::SlowOut);
		}
		else if (SPStringHelper::EqualsIgnoreCase(style, L"SlowInOut"))
		{
			animation->SetType(SUITransition::SlowInOut);
		}
		else if (SPStringHelper::EqualsIgnoreCase(style, L"FastInOut"))
		{
			animation->SetType(SUITransition::FastInOut);
		}
		else
		{
			animation->SetType(SUITransition::Normal);
		}
	}

	animation->SetEndPoint(endPoint);

	if (SV8Function::HasProperty(L"addMode", argObj))
	{
		SPString style = SPV8ScriptEngine::StringToSPString(
			SV8Function::GetProperty(L"transparencyDelta", argObj)->ToString());

		if (SPStringHelper::EqualsIgnoreCase(style, L"Merge"))
		{
			component->MergerAnimation(animation);
		}
		else if (SPStringHelper::EqualsIgnoreCase(style, L"Skip"))
		{
			component->Skip();
			component->AddAnimation(animation);
		}
		else
		{
			component->AddAnimation(animation);
		}
	}
	else
	{
		// style == L"Normal"
		component->AddAnimation(animation);
	}

	component->PlayAnimation();
}

void SV8Component::AddEffect( const FunctionCallbackInfo<Value>& args )
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

	Handle<Object> argObj = args[0]->ToObject();
	SPEffectPtr effect = new SPEffect();
	effect = SV8Function::GetEffectFromObj(argObj, effect);

	if (SV8Function::HasProperty(L"addMode", argObj))
	{
		SPString style = SPV8ScriptEngine::StringToSPString(
			SV8Function::GetProperty(L"addMode", argObj)->ToString());

		if (SPStringHelper::EqualsIgnoreCase(style, L"Skip"))
		{
			component->Skip();
			component->AddEffect(effect);
		}
		else
		{
			component->AddEffect(effect);
		}
	}
	else
	{
		// style == L"Normal"
		component->AddEffect(effect);
	}
}
