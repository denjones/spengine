#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"


SV8ScriptManager::SV8ScriptManager(void)
{
}


SV8ScriptManager::~SV8ScriptManager(void)
{
	screenTempl->ClearAndLeak();
	screenTempl = NULL;
}

bool SV8ScriptManager::Initialize()
{
	// Enter

	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton().GetContext();
	Context::Scope contextScope(context);

	// Create Global Screen Object
	// Set ScreenGetter/ScreenSetter

	context->Global()->SetAccessor(	
		SPV8ScriptEngine::SPStringToString(L"screen"),
		ScreenGetter);

	//
	// Create All Templates
	//

	// Screen
	Handle<ObjectTemplate> templScreen = ObjectTemplate::New();
	screenTempl = new Persistent<ObjectTemplate>(isolate, templScreen);
	templScreen->SetInternalFieldCount(1);
	templScreen->SetNamedPropertyHandler(GetScreenProperty, SetScreenProperty);

	// Component

	//
	// Init Script
	//

	SPV8ScriptEngine::GetSingleton().RunScriptFromFile(L"init.js");

	return true;
}

bool SV8ScriptManager::Update( float timeDelta )
{
	return true;
}

bool SV8ScriptManager::Load()
{
	return true;
}

bool SV8ScriptManager::Reload()
{
	return Load();
}

bool SV8ScriptManager::Unload()
{
	return true;
}


void SV8ScriptManager::ScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info)
{
	Handle<ObjectTemplate> realTemplate = SV8ScriptManager::GetSingleton().GetScreenTemplate();
	Local<Object> obj = realTemplate->NewInstance();
	obj->SetInternalField(0, External::New(
		SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SUIManager::GetSingleton().GetCurrentScreen()));

	info.GetReturnValue().Set(obj);

	return ;
}

void SV8ScriptManager::ScreenSetter(
	Local<String> property,
	Local<Value> value,
	const PropertyCallbackInfo<void>& info) 
{
	return;
}

Handle<ObjectTemplate> SV8ScriptManager::GetScreenTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*screenTempl));
}

void SV8ScriptManager::GetScreenProperty( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	TryCatch tryCatch;
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();
	if (screen == NULL)
	{
		SPV8ScriptEngine::GetSingleton().GetIsolate()->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
	}
}

void SV8ScriptManager::SetScreenProperty( Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info )
{
	Handle<External> field = Handle<External>::Cast(info.Holder()->GetInternalField(0));
	SUIScreen* screen = (SUIScreen*)field->Value();
	if (screen == NULL)
	{
		SPV8ScriptEngine::GetSingleton().GetIsolate()->ThrowException(
			Exception::ReferenceError(SPV8ScriptEngine::SPStringToString(L"Null Reference.")));
	}
}

