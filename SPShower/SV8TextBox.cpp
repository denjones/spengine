#include "StdAfx.h"
#include "SV8TextBox.h"
#include "SV8Component.h"
#include "SUITextBox.h"

Handle<ObjectTemplate> SV8TextBox::GetTemplate()
{
	Handle<ObjectTemplate> templ = SV8Component::GetTemplate();

	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"text"), TextGetter, TextSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"lineSpace"), LineSpaceGetter, LineSpaceSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"letterSpace"), LetterSpaceGetter, LetterSpaceSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"paddingTop"), PaddingTopGetter, PaddingTopSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"paddingRight"), PaddingRightGetter, PaddingRightSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"paddingBottom"), PaddingBottomGetter, PaddingBottomSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"paddingLeft"), PaddingLeftGetter, PaddingLeftSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"color"), ColorGetter, ColorSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"autoHeight"), AutoHeightGetter, AutoHeightSetter);

	// Methods

	templ->Set(SPV8ScriptEngine::SPStringToString(L"addText"), 
		FunctionTemplate::New(AddText)->GetFunction());

	return templ;
}

void SV8TextBox::TextGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(component->GetContent()));
}

void SV8TextBox::TextSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->Clear();
	SUIText text;
	text.text = SPV8ScriptEngine::StringToSPString(value->ToString());
	text.color = component->GetDefaultColor();
	try
	{
		component->AddText(text);
	}
	catch (exception e)
	{
		isolate->ThrowException(SPV8ScriptEngine::SPStringToString(L"Game Exited."));
	}	
}

void SV8TextBox::LineSpaceGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetLineSpace()));
}

void SV8TextBox::LineSpaceSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetLineSpace(value->NumberValue());
}

void SV8TextBox::LetterSpaceGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetWordSpace()));
}

void SV8TextBox::LetterSpaceSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetWordSpace(value->NumberValue());
}

void SV8TextBox::PaddingTopGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetPaddingTop()));
}

void SV8TextBox::PaddingTopSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPaddingTop(value->NumberValue());
}

void SV8TextBox::PaddingRightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetPaddingRight()));
}

void SV8TextBox::PaddingRightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPaddingRight(value->NumberValue());
}

void SV8TextBox::PaddingBottomGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetPaddingTop()));
}

void SV8TextBox::PaddingBottomSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPaddingBottom(value->NumberValue());
}

void SV8TextBox::PaddingLeftGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Number::New(component->GetPaddingLeft()));
}

void SV8TextBox::PaddingLeftSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetPaddingLeft(value->NumberValue());
}

void SV8TextBox::ColorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(component->GetDefaultColor()));
}

void SV8TextBox::ColorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetDefaultColor(value->Int32Value());
}

void SV8TextBox::AutoHeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(Integer::New(component->IsAutoHeight()));
}

void SV8TextBox::AutoHeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* component = (SUITextBox*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetAutoHeight(value->BooleanValue());
}

void SV8TextBox::AddText( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUITextBox* textBox = (SUITextBox*)field->Value();


	if (args.Length() == 0)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Argument.")));
		return;
	}

	if (textBox)
	{
		try
		{
			SUIText text;
			text.text = SPV8ScriptEngine::StringToSPString(args[0]->ToString());
			text.color = textBox->GetDefaultColor();
			textBox->AddText(text);
		}
		catch (exception e)
		{
			isolate->ThrowException(SPV8ScriptEngine::SPStringToString(L"Game Exited."));
		}	
	}
}