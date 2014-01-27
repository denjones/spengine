#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Function.h"
#include "SV8Screen.h"
#include "SV8Component.h"
#include "SV8Window.h"
#include "SV8TextBox.h"
#include "SV8DialogBox.h"


SV8ScriptManager::SV8ScriptManager(void)
{
	SPV8ScriptEngine::GetSingleton();
	requireEngine = SPV8ScriptEngine::GetSingletonPtr();
}


SV8ScriptManager::~SV8ScriptManager(void)
{
	if (screenTempl)
	{
		screenTempl->ClearAndLeak();
		screenTempl = NULL;
	}
	
	if (componentTempl)
	{
		componentTempl->ClearAndLeak();
		componentTempl = NULL;
	}

	if (textBoxTempl)
	{
		textBoxTempl->ClearAndLeak();
		textBoxTempl = NULL;
	}

	if (dialogBoxTempl)
	{
		dialogBoxTempl->ClearAndLeak();
		dialogBoxTempl = NULL;
	}

	if (windowTempl)
	{
		windowTempl->ClearAndLeak();
		windowTempl = NULL;
	}	
}

bool SV8ScriptManager::Initialize()
{
	//
	// Init Global Functions
	//

	SPV8ScriptEngine::GetSingleton().AddFunction(L"createScreen", SV8Function::CreateScreen);

	//
	// Enter
	//

	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton().GetContext();
	Context::Scope contextScope(context);

	//
	// Create All Templates
	//

	screenTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SV8Screen::GetTemplate());
	componentTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SV8Component::GetTemplate());
	windowTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SV8Window::GetTemplate());
	textBoxTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SV8TextBox::GetTemplate());
	dialogBoxTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton().GetIsolate(), 
		SV8DialogBox::GetTemplate());

	//
	// Set Global Window Object
	//

	context->Global()->Set(SPV8ScriptEngine::SPStringToString(L"window"), GetWindowTemplate()->NewInstance());

	//
	// Create Global Screen Object
	//

	context->Global()->SetAccessor(SPV8ScriptEngine::SPStringToString(L"screen"),
		SV8Screen::ScreenGetter);

	//
	// Create Global Persistent Object
	//

	context->Global()->Set(SPV8ScriptEngine::SPStringToString(L"global"), Object::New());

	//
	// Init Script
	//

	return true;
}

bool SV8ScriptManager::Update( float timeDelta )
{
	return true;
}

bool SV8ScriptManager::Load()
{
	SPV8ScriptEngine::GetSingleton().RunScriptFromFile(L"init.js");
	return true;
}

bool SV8ScriptManager::Reload()
{
	return true;
}

bool SV8ScriptManager::Unload()
{
	return true;
}

bool SV8ScriptManager::HasProperty( SPString propertyName, Handle<Object> obj )
{
	return SV8Function::HasProperty(propertyName, obj);
}

Handle<Value> SV8ScriptManager::GetProperty( SPString propertyName, Handle<Object> obj )
{
	return SV8Function::GetProperty(propertyName, obj);
}

Handle<ObjectTemplate> SV8ScriptManager::GetScreenTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*screenTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetComponentTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*componentTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetWindowTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*windowTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetTextBoxTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*textBoxTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetDialogBoxTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton().GetIsolate(), (*dialogBoxTempl));
}

