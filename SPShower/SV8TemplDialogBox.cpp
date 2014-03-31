#include "StdAfx.h"
#include "SV8TemplDialogBox.h"
#include "SV8TemplTextBox.h"
#include "SUIDialogBox.h"
#include "SV8Function.h"

Handle<ObjectTemplate> SV8TemplDialogBox::GetTemplate()
{
	Handle<ObjectTemplate> templ = SV8TemplTextBox::GetTemplate();

	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"speed"), SpeedGetter, SpeedSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"nextLineImage"), NextLineImageGetter, NextLineImageSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"nextPageImage"), NextPageImageGetter, NextPageImageSetter);

	// Methods

	templ->Set(SPV8ScriptEngine::SPStringToString(L"next"), 
		FunctionTemplate::New(Next)->GetFunction());

	return templ;
}

void SV8TemplDialogBox::Next( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIDialogBox* textBox = (SUIDialogBox*)field->Value();

	if (textBox)
	{
		textBox->Next();
	}
}

void SV8TemplDialogBox::SpeedGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIDialogBox* component = (SUIDialogBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(component->GetSpeed());
}

void SV8TemplDialogBox::SpeedSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIDialogBox* component = (SUIDialogBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetSpeed(value->NumberValue());
}

void SV8TemplDialogBox::NextLineImageGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	
}

void SV8TemplDialogBox::NextLineImageSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIDialogBox* textBox = (SUIDialogBox*)field->Value();

	if (value->IsNull() || value->IsUndefined())
	{
		textBox->SetNextLineTex(NULL);
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

	if (tex)
	{
		textBox->SetNextLineTex(tex);
	}
}

void SV8TemplDialogBox::NextPageImageGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8TemplDialogBox::NextPageImageSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIDialogBox* textBox = (SUIDialogBox*)field->Value();

	if (value->IsNull() || value->IsUndefined())
	{
		textBox->SetNextPageTex(NULL);
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

	if (tex)
	{
		textBox->SetNextPageTex(tex);
	}
}

