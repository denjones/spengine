#include "StdAfx.h"
#include "SV8TextBox.h"
#include "SV8Component.h"
#include "SUITextBox.h"
#include "SV8Function.h"
#include "SUIEffectManager.h"

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
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"textEffectFront"), TextEffectFrontGetter, TextEffectFrontSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"textEffectBack"), TextEffectBackGetter, TextEffectBackSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"font"), FontGetter, FontSetter);

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

void SV8TextBox::TextEffectFrontGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	// Nothing
}

void SV8TextBox::TextEffectFrontSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* textBox = (SUITextBox*)field->Value();

	if (value == Undefined(isolate))
	{
		textBox->SetDefaultFrontEffect(NULL);
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(value);
	SUIEffectPtr effect = textBox->GetDefaultFrontEffect();
	effect = SV8Function::GetEffectFromObj(argObj, effect);

	if (!effect)
	{
		isolate->ThrowException(SPV8ScriptEngine::SPStringToString(L"Effect Undefined."));
		return;
	}
	else
	{
		effect->Update(0.01);
	}

	textBox->SetDefaultFrontEffect(effect);
}

void SV8TextBox::TextEffectBackGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	// Nothing
}

void SV8TextBox::TextEffectBackSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* textBox = (SUITextBox*)field->Value();

	if (value == Undefined(isolate))
	{
		textBox->SetDefaultBackEffect(NULL);
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(value);
	SUIEffectPtr effect = textBox->GetDefaultBackEffect();
	effect = SV8Function::GetEffectFromObj(argObj, effect);

	if (!effect)
	{
		isolate->ThrowException(SPV8ScriptEngine::SPStringToString(L"Effect Undefined."));
		return;
	}
	else
	{
		effect->Update(0.01);
	}

	textBox->SetDefaultBackEffect(effect);
}

void SV8TextBox::FontGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* textBox = (SUITextBox*)field->Value();

	SPFontPtr font = textBox->GetDefaultFont();

	int		size = font->GetHeight();
	int		weight = font->GetWeight();
	bool	italic = font->GetItalic();
	SPString fontName = font->GetFontName();

	Handle<Object> obj = Object::New();
	obj->Set(SPV8ScriptEngine::SPStringToString(L"font"), SPV8ScriptEngine::SPStringToString(fontName));
	obj->Set(SPV8ScriptEngine::SPStringToString(L"weight"), Integer::New(weight));
	obj->Set(SPV8ScriptEngine::SPStringToString(L"italic"), Boolean::New(isolate, italic));
	obj->Set(SPV8ScriptEngine::SPStringToString(L"size"), Number::New(isolate, size));

	info.GetReturnValue().Set(obj);
}

void SV8TextBox::FontSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUITextBox* textBox = (SUITextBox*)field->Value();

	if (value->IsNull() || value->IsUndefined())
	{
		textBox->SetDefaultFont(SPFontManager::GetSingleton().GetFont(L"text_box_default"));
		return;
	}

	if (value->IsString())
	{
		SPString name = SPV8ScriptEngine::StringToSPString(value->ToString());

		SPFontPtr font = SPFontManager::GetSingleton().GetFont(name);

		textBox->SetDefaultFont(font);
	}
	else
	{
		Handle<Object> argObj = Handle<Object>::Cast(value);

		SPFontPtr font = textBox->GetDefaultFont();

		int		size = font->GetHeight();
		int		weight = font->GetWeight();
		bool	italic = font->GetItalic();
		SPString fontName = font->GetFontName();

		if (SV8Function::HasProperty(L"size", argObj))
		{
			size = SV8Function::GetProperty(L"size", argObj)->NumberValue();
		}

		if (SV8Function::HasProperty(L"font", argObj))
		{
			fontName = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"font", argObj)->ToString());
		}

		if (SV8Function::HasProperty(L"weight", argObj))
		{
			Handle<Value> weightVal = SV8Function::GetProperty(L"weight", argObj);

			if (weightVal->IsString())
			{
				SPString weightType = SPV8ScriptEngine::StringToSPString(weightVal->ToString());

				if (SPStringHelper::EqualsIgnoreCase(weightType, L"DontCare"))
				{
					weight = FW_DONTCARE;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Thin"))
				{
					weight = FW_THIN;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"ExtraLight") || 
					SPStringHelper::EqualsIgnoreCase(weightType, L"UltraLight"))
				{
					weight = FW_EXTRALIGHT;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Light"))
				{
					weight = FW_LIGHT;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Normal") || 
					SPStringHelper::EqualsIgnoreCase(weightType, L"Regular"))
				{
					weight = FW_NORMAL;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Medium"))
				{
					weight = FW_MEDIUM;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"SemiBold") || 
					SPStringHelper::EqualsIgnoreCase(weightType, L"DemiBold"))
				{
					weight = FW_SEMIBOLD;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Bold"))
				{
					weight = FW_BOLD;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"ExtraBold") ||
					SPStringHelper::EqualsIgnoreCase(weightType, L"UltraBold"))
				{
					weight = FW_EXTRABOLD;
				}
				else if (SPStringHelper::EqualsIgnoreCase(weightType, L"Heavy") ||
					SPStringHelper::EqualsIgnoreCase(weightType, L"Black"))
				{
					weight = FW_HEAVY;
				}
			}
			else
			{
				weight = weightVal->NumberValue();
			}
		}

		if (SV8Function::HasProperty(L"italic", argObj))
		{
			Handle<Value> italicVal = SV8Function::GetProperty(L"weight", argObj);
			italic = italicVal->BooleanValue();
		}

		font = new SPFont(size, 0, weight, 10, italic, fontName);

		textBox->SetDefaultFont(font, true);
	}
}