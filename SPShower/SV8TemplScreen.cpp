#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8TemplScreen.h"
#include "SV8Function.h"
#include "SUIDialogBox.h"
#include "SUIList.h"

Handle<ObjectTemplate> SV8TemplScreen::GetTemplate()
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
	templScreen->Set(SPV8ScriptEngine::SPStringToString(L"capture"), 
		FunctionTemplate::New(Capture)->GetFunction());

	return templScreen;
}

void SV8TemplScreen::ScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
	if(!SUIManager::GetSingleton())
	{
		return;
	}

	SUIScreenPtr screen = SUIManager::GetSingleton()->GetCurrentScreen();

	if (screen)
	{
		info.GetReturnValue().Set(screen->GetV8Obj());
	}

	return ;
}

void SV8TemplScreen::ScreenSetter(
	Local<String> property,
	Local<Value> value,
	const PropertyCallbackInfo<void>& info) 
{
	return;
}

void SV8TemplScreen::GetScreenProperty( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);
}

void SV8TemplScreen::SetScreenProperty( Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();
	if (screen == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
	}

	SPString propertyStr = SPV8ScriptEngine::StringToSPString(property);
}

void SV8TemplScreen::RootGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
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

void SV8TemplScreen::RootSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	return;
}

void SV8TemplScreen::PopUpGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(screen->IsPopup());
}

void SV8TemplScreen::PopUpSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	screen->SetPopUp(value->BooleanValue());
}

void SV8TemplScreen::IdGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(screen->GetName()));
}

void SV8TemplScreen::IdSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	screen->SetName(SPV8ScriptEngine::StringToSPString(value->ToString()));
		
	return;
}

void SV8TemplScreen::BGColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(screen->GetBackgroundColor()));
}

void SV8TemplScreen::BGColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen == NULL)
	{
		isolate->ThrowException(Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	screen->SetBackgroundColor(value->Int32Value());
}

void SV8TemplScreen::CreateComponent( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
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
		else if (SPStringHelper::EqualsIgnoreCase(type, L"scroll"))
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

	if (SV8Function::HasProperty(L"width", argObj))
	{
		obj->Set(SPV8ScriptEngine::SPStringToString(L"width"), SV8Function::GetProperty(L"width", argObj));
		argObj->Delete(SPV8ScriptEngine::SPStringToString(L"width"));
	}

	if (SV8Function::HasProperty(L"height", argObj))
	{
		obj->Set(SPV8ScriptEngine::SPStringToString(L"height"), SV8Function::GetProperty(L"height", argObj));
		argObj->Delete(SPV8ScriptEngine::SPStringToString(L"height"));
	}

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

void SV8TemplScreen::Focus( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	if (screen)
	{
		screen->Focus();
	}
}

void SV8TemplScreen::GetComponentById( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
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

void SV8TemplScreen::Capture( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();

	SPString fileName = L"capture/default.jpg";

	if(args.Length() >= 0)
	{
		if(args[0]->IsObject())
		{
			Handle<Object> argObj = Handle<Object>::Cast(args[0]);

			if (SV8Function::HasProperty(L"file", argObj))
			{
				fileName = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"file", argObj)->ToString());
			}
		}
		else if (args[0]->IsString())
		{
			fileName = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
		}
	}

	screen->GetComponent(L"global_root")->SaveAsImage(fileName);
}
