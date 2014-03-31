#include "StdAfx.h"
#include "SV8TemplPictureBox.h"
#include "SUIPictureBox.h"
#include "SV8Function.h"
#include "SUIPictureManager.h"
#include "SV8TemplComponent.h"

Handle<ObjectTemplate> SV8TemplPictureBox::GetTemplate()
{
	Handle<ObjectTemplate> templ = SV8TemplComponent::GetTemplate();

	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"fillMode"), FillModeGetter, FillModeSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"positionMode"), PositionModeGetter, PositionModeSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"positionX"), PositionXGetter, PositionXSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"positionY"), PositionYGetter, PositionYSetter);

	// Methods

	templ->Set(SPV8ScriptEngine::SPStringToString(L"setPicture"), 
		FunctionTemplate::New(SetBaseImage)->GetFunction());

	//templ->Set(SPV8ScriptEngine::SPStringToString(L"mix"), 
	//	FunctionTemplate::New(MixImage)->GetFunction());

	return templ;
}

void SV8TemplPictureBox::FillModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(
		SUIPictureBox::FillModeToString(component->GetFillMode())));
}

void SV8TemplPictureBox::FillModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetFillMode(SUIPictureBox::StringToFillMode(
		SPV8ScriptEngine::StringToSPString(value->ToString())));
}

void SV8TemplPictureBox::PositionModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(
		SUIPictureBox::PositionModeToString(component->GetPositionMode())));
}

void SV8TemplPictureBox::PositionModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPositionMode(SUIPictureBox::StringToPositionMode(
		SPV8ScriptEngine::StringToSPString(value->ToString())));
}

void SV8TemplPictureBox::PositionXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(component->GetImagePositionX()));
}

void SV8TemplPictureBox::PositionXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetImagePositionX(value->Int32Value());
}

void SV8TemplPictureBox::PositionYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(component->GetImagePositionY()));
}

void SV8TemplPictureBox::PositionYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetImagePositionY(value->Int32Value());
}

void SV8TemplPictureBox::SetBaseImage( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIPictureBox* component = (SUIPictureBox*)field->Value();
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

	Handle<Value> value = args[0];

	if (value->IsNull() || value->IsUndefined())
	{
		component->SetBackgroundImage(NULL);
		return;
	}

	SPTexturePtr tex = NULL;

	if (value->IsString())
	{
		SPString name = SPV8ScriptEngine::StringToSPString(value->ToString());
		tex = SPTextureManager::GetSingleton()->GetTexture(name);
	}
	else
	{
		Handle<Object> argObj = Handle<Object>::Cast(value);
		tex = SV8Function::GetTextureFromObj(argObj);
	}

	component->SetBaseImage(tex);
}


