#include "StdAfx.h"
#include "SV8Scroll.h"
#include "SV8Component.h"
#include "SUIList.h"

Handle<ObjectTemplate> SV8Scroll::GetTemplate()
{
	Handle<ObjectTemplate> templ = SV8Component::GetTemplate();

	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"scrollPosition"), ScrollPositionGetter, ScrollPositionSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"direction"), DirectionGetter, DirectionSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"maxCount"), MaxCountGetter, MaxCountSetter);
	templ->SetAccessor(SPV8ScriptEngine::SPStringToString(L"onBoundaryReach"), OnBoundaryReachGetter, OnBoundaryReachSetter);

	// Methods

	templ->Set(SPV8ScriptEngine::SPStringToString(L"scrollBy"), 
		FunctionTemplate::New(ScrollBy)->GetFunction());

	templ->Set(SPV8ScriptEngine::SPStringToString(L"clear"), 
		FunctionTemplate::New(Clear)->GetFunction());

	return templ;
}

void SV8Scroll::ScrollPositionGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(component->GetScrollPosition());
}

void SV8Scroll::ScrollPositionSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetScrollPosition(value->NumberValue());
}

void SV8Scroll::DirectionGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	switch(component->GetDirection())
	{
	case SUIList::Vertical:
		info.GetReturnValue().Set(L"vertical");
		break;
	case SUIList::Horizontal:
		info.GetReturnValue().Set(L"horizontal");
		break;
	}
}

void SV8Scroll::DirectionSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	SPString direction = SPV8ScriptEngine::StringToSPString(value->ToString());

	if (SPStringHelper::EqualsIgnoreCase(direction, L"vertical"))
	{
		component->SetDirection(SUIList::Vertical);
	}
	else if (SPStringHelper::EqualsIgnoreCase(direction, L"horizontal"))
	{
		component->SetDirection(SUIList::Horizontal);
	}
}

void SV8Scroll::MaxCountGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(component->GetMaxItemNum());
}

void SV8Scroll::MaxCountSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->SetMaxItemNum(value->Int32Value());
}

void SV8Scroll::OnBoundaryReachGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{

}

void SV8Scroll::OnBoundaryReachSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Scroll::ScrollBy( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
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

	component->Scroll(value->Int32Value());
}

void SV8Scroll::Clear( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Handle<External> field = Handle<External>::Cast(args.Holder()->GetInternalField(0));
	SUIList* component = (SUIList*)field->Value();
	if (component == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	component->ClearChild();
}
