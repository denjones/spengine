#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Screen.h"
#include "SV8Function.h"
#include "SUIDialogBox.h"
#include "SUIList.h"

Handle<ObjectTemplate> SV8Screen::GetTemplate()
{
	Handle<ObjectTemplate> templScreen = ObjectTemplate::New();
	templScreen->SetInternalFieldCount(1);
	//templScreen->SetNamedPropertyHandler(GetScreenProperty, SetScreenProperty);
	templScreen->SetAccessor(SPV8ScriptEngine::SPStringToString(L"root"), RootGetter, RootSetter);
	templScreen->SetAccessor(SPV8ScriptEngine::SPStringToString(L"popUp"), PopUpGetter, PopUpSetter);
	templScreen->SetAccessor(SPV8ScriptEngine::SPStringToString(L"id"), IdGetter, IdSetter);
	templScreen->SetAccessor(SPV8ScriptEngine::SPStringToString(L"backgroundColor"), BGColorGetter, BGColorSetter);

	// Methods

	templScreen->Set(SPV8ScriptEngine::SPStringToString(L"createComponent"), 
		FunctionTemplate::New(CreateComponent)->GetFunction());
	templScreen->Set(SPV8ScriptEngine::SPStringToString(L"focus"), 
		FunctionTemplate::New(Focus)->GetFunction());
	templScreen->Set(SPV8ScriptEngine::SPStringToString(L"getComponentById"), 
		FunctionTemplate::New(GetComponentById)->GetFunction());

	return templScreen;
}

void SV8Screen::ScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
	SUIScreenPtr screen = SUIManager::GetSingleton().GetCurrentScreen();

	if (screen)
	{
		info.GetReturnValue().Set(screen->GetV8Obj());
	}

	return ;
}

void SV8Screen::ScreenSetter(
	Local<String> property,
	Local<Value> value,
	const PropertyCallbackInfo<void>& info) 
{
	return;
}

void SV8Screen::GetScreenProperty( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);
}

void SV8Screen::SetScreenProperty( Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();
	if (screen == NULL)
	{
		SPV8ScriptEngine::GetSingleton().GetIsolate()->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);
}

void SV8Screen::RootGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SUIComponentPtr root = screen->GetComponent(L"global_root");

	if (root)
	{
		info.GetReturnValue().Set(root->GetV8Obj());
	}
}

void SV8Screen::RootSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	return;
}

void SV8Screen::PopUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Boolean::New(isolate, screen->IsPopup()));
}

void SV8Screen::PopUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	screen->SetPopUp(value->BooleanValue());
}

void SV8Screen::IdGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(screen->GetName()));
}

void SV8Screen::IdSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}
		
	return;
}

void SV8Screen::BGColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(isolate, screen->GetBackgroundColor()));
}

void SV8Screen::BGColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	screen->SetBackgroundColor(value->Int32Value());
}

void SV8Screen::CreateComponent( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(args[0]);

	SUIComponentPtr com;

	if (argObj.IsEmpty() || !SV8Function::HasProperty(L"type", argObj))
	{
		com = new SUIComponent(screen);
	}
	else
	{
		SPString type = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"type", argObj)->ToString());

		if (SPStringHelper::EqualsIgnoreCase(type, L"textBox"))
		{
			com = new SUITextBox(screen);
		}
		else if (SPStringHelper::EqualsIgnoreCase(type, L"dialogBox"))
		{
			com = new SUIDialogBox(screen);
		}
		else if (SPStringHelper::EqualsIgnoreCase(type, L"pictureBox"))
		{
			com = new SUIPictureBox(screen);
		}
		else if (SPStringHelper::EqualsIgnoreCase(type, L"list"))
		{
			com = new SUIList(screen);
		}
		else
		{
			com = new SUIComponent(screen);
		}

		argObj->Delete(SPV8ScriptEngine::SPStringToString(L"type"));
	}

	screen->SetPersistentComponent(com);

	Handle<Object> obj = com->GetV8Obj();

	const Local<Array> props = argObj->GetPropertyNames();
	const uint32_t length = props->Length();
	for (uint32_t i = 0; i < length; i++)
	{
		const Local<Value> key = props->Get(i);
		const Local<Value> value = argObj->Get(key);

		obj->Set(key, value);
	}

	args.GetReturnValue().Set(obj);
}

void SV8Screen::Focus( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen)
	{
		screen->Focus();
	}
}

void SV8Screen::GetComponentById( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	SPString id = SPV8ScriptEngine::StringToSPString(args[0]->ToString());

	SUIComponentPtr com = screen->GetComponent(id);

	if (com)
	{
		args.GetReturnValue().Set(com->GetV8Obj());
	}
}
