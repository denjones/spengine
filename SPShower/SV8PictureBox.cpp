#include "StdAfx.h"
#include "SV8PictureBox.h"
#include "SUIPictureBox.h"
#include "SV8Function.h"
#include "SUIPictureManager.h"
#include "SV8Component.h"

Handle<ObjectTemplate> SV8PictureBox::GetTemplate()
{
	Handle<ObjectTemplate> templ = SV8Component::GetTemplate();

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

void SV8PictureBox::FillModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::FillModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionModeGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionModeSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::PositionYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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

void SV8PictureBox::SetBaseImage( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
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
		tex = SPTextureManager::GetSingleton().GetTexture(name);
	}
	else
	{
		Handle<Object> argObj = Handle<Object>::Cast(value);
		tex = SV8Function::GetTextureFromObj(argObj);
	}

	component->SetBaseImage(tex);
}


