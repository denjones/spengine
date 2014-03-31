#include "StdAfx.h"
#include "SV8TemplEvent.h"
#include "SUIEvent.h"


Handle<ObjectTemplate> SV8TemplEvent::GetTemplate()
{
	Handle<ObjectTemplate> templEvent = ObjectTemplate::New();
	templEvent->SetInternalFieldCount(1);

	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"key"), KeyGetter, KeySetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"absoluteX"), AbsoluteXGetter, AbsoluteXSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"absoluteY"), AbsoluteYGetter, AbsoluteYSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"x"), XGetter, XSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"y"), YGetter, YSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"movementX"), MovementXGetter, MovementXSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"movementY"), MovementYGetter, MovementYSetter);
	templEvent->SetAccessor(SPV8ScriptEngine::SPStringToString(L"returnValue"), ReturnValueGetter, ReturnValueSetter);

	return templEvent;
}

void SV8TemplEvent::KeyGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->button);
}

void SV8TemplEvent::KeySetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->button = value->Int32Value();
}

void SV8TemplEvent::AbsoluteXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->absoluteX);
}

void SV8TemplEvent::AbsoluteXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->absoluteX = value->Int32Value();
}

void SV8TemplEvent::AbsoluteYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->absoluteY);
}

void SV8TemplEvent::AbsoluteYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->absoluteY = value->Int32Value();
}

void SV8TemplEvent::XGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->positionX);
}

void SV8TemplEvent::XSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->positionX = value->Int32Value();
}

void SV8TemplEvent::YGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->positionY);
}

void SV8TemplEvent::YSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->positionY = value->Int32Value();
}

void SV8TemplEvent::MovementXGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->movementX);
}

void SV8TemplEvent::MovementXSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->movementX = value->Int32Value();
}

void SV8TemplEvent::MovementYGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->movementY);
}

void SV8TemplEvent::MovementYSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->movementY = value->Int32Value();
}

void SV8TemplEvent::ReturnValueGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	info.GetReturnValue().Set(handle->returnValue);
}

void SV8TemplEvent::ReturnValueSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIEventHandle handle = (SUIEventHandle)field->Value();
	if (handle == NULL)
	{
		isolate->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
		return;
	}

	handle->returnValue = value->BooleanValue();
}
