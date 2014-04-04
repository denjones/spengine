#define BUILDING_NODE_EXTENSION

#include "StdAfx.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Function.h"
#include "SV8TemplScreen.h"
#include "SV8TemplComponent.h"
#include "SV8TemplWindow.h"
#include "SV8TemplTextBox.h"
#include "SV8TemplDialogBox.h"
#include "SV8TemplPictureBox.h"
#include "SV8TemplScroll.h"
#include <node.h>
#include "SV8TemplEvent.h"
#include "SV8TemplCommandEvent.h"
#include "SV8TemplFPS.h"

SV8ScriptManager::SV8ScriptManager(void)
{
	SPV8ScriptEngine::GetSingleton();
	requireEngine = SPV8ScriptEngine::GetSingleton();
	isScriptRunning = false;
	async = new uv_async_t();
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

	if (pictureBoxTempl)
	{
		pictureBoxTempl->ClearAndLeak();
		pictureBoxTempl = NULL;
	}	

	if (scrollTempl)
	{
		scrollTempl->ClearAndLeak();
		scrollTempl = NULL;
	}	

	if (eventTempl)
	{
		eventTempl->ClearAndLeak();
		eventTempl = NULL;
	}	

	if (commandEventTempl)
	{
		commandEventTempl->ClearAndLeak();
		commandEventTempl = NULL;
	}

	if (fpsTempl)
	{
		fpsTempl->ClearAndLeak();
		fpsTempl = NULL;
	}

	if (async)
	{
		delete async;
		async = NULL;
	}
}

bool SV8ScriptManager::Initialize()
{
	// Init uv callback

	uv_async_init(uv_default_loop(), (uv_async_t*)async, HandleCommandCallback);

	//
	// Init Global Functions
	//

	//SPV8ScriptEngine::GetSingleton()->AddFunction(L"createScreen", SV8Function::CreateScreen);
	//SPV8ScriptEngine::GetSingleton()->AddFunction(L"registerFont", SV8Function::RegisterFont);
	//SPV8ScriptEngine::GetSingleton()->AddFunction(L"createTrack", SV8Function::CreateTrack);
	//SPV8ScriptEngine::GetSingleton()->AddFunction(L"createVideo", SV8Function::CreateVideo);
	//SPV8ScriptEngine::GetSingleton()->AddFunction(L"createParticleSystem", SV8Function::CreateParticleSystem);

	//
	// Enter
	//

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();;
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton()->GetContext();
	Context::Scope contextScope(context);

	//
	// Create All Templates
	//

	fpsTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplFPS::GetTemplate());
	screenTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplScreen::GetTemplate());
	componentTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplComponent::GetTemplate());
	windowTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplWindow::GetTemplate());
	textBoxTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplTextBox::GetTemplate());
	dialogBoxTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplDialogBox::GetTemplate());
	pictureBoxTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplPictureBox::GetTemplate());
	scrollTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplScroll::GetTemplate());
	eventTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplEvent::GetTemplate());
	commandEventTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplCommandEvent::GetTemplate());
	

	////
	//// Set Global Window Object
	////

	//context->Global()->Set(SPV8ScriptEngine::SPStringToString(L"window"), GetWindowTemplate()->NewInstance());

	////
	//// Create Global Screen Object
	////

	//context->Global()->SetAccessor(SPV8ScriptEngine::SPStringToString(L"screen"),
	//	SV8Screen::ScreenGetter);

	////
	//// Create Global Persistent Object
	////

	//context->Global()->Set(SPV8ScriptEngine::SPStringToString(L"global"), Object::New());

	////
	//// Init Script
	////

	return true;
}

bool SV8ScriptManager::Update( float timeDelta )
{
	if(!isScriptRunning) 
	{
		isScriptRunning = true;

		SPV8ScriptEngine::GetSingleton()->RunScriptFromFile(L"init.js");
	}

	uv_async_send((uv_async_t*)async);
	
	return true;
}

bool SV8ScriptManager::Load()
{
	
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
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*screenTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetComponentTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*componentTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetWindowTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*windowTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetTextBoxTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*textBoxTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetDialogBoxTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*dialogBoxTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetPictureBoxTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*pictureBoxTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetScrollTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*scrollTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetEventTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*eventTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetCommandEventTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*commandEventTempl));
}

Handle<ObjectTemplate> SV8ScriptManager::GetFPSTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*fpsTempl));
}

void SV8ScriptManager::HandleCommandCallback( uv_async_t *handle, int status )
{
	SV8ScriptManager::GetSingleton()->HandleCommands();
}

void SV8ScriptManager::InitModule( Handle<Object> exports )
{
	//
	// Init Global Functions
	//

	exports->Set(SPV8ScriptEngine::SPStringToString(L"createScreen"), FunctionTemplate::New(SV8Function::CreateScreen)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"registerFont"), FunctionTemplate::New(SV8Function::RegisterFont)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"createTrack"), FunctionTemplate::New(SV8Function::CreateTrack)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"createVideo"), FunctionTemplate::New(SV8Function::CreateVideo)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"createParticleSystem"), FunctionTemplate::New(SV8Function::CreateParticleSystem)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"include"), FunctionTemplate::New(SPV8ScriptEngine::Include)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"addCommand"), FunctionTemplate::New(SV8Function::AddCommand)->GetFunction());

	//
	// Set Global Window Object
	//

	exports->Set(SPV8ScriptEngine::SPStringToString(L"window"), SV8ScriptManager::GetSingleton()->GetWindowTemplate()->NewInstance());

	//
	// Create Global Screen Object
	//

	exports->SetAccessor(SPV8ScriptEngine::SPStringToString(L"screen"),
		SV8TemplScreen::ScreenGetter);
}

void SV8ScriptManager::LockCommandQueue()
{
	commandLock.Lock();
}

void SV8ScriptManager::UnlockCommandQueue()
{
	commandLock.Unlock();
}

void SV8ScriptManager::HandleCommands()
{
	LockCommandQueue();

	while(commands.size() > 0)
	{
		// Accept Function.
		SV8ScriptCommandPtr command = commands.front();
		SV8CommandEventPtr event = new SV8CommandEvent();


		// Use function.
		command->Call(event);

		// If the function is not finished.
		if (event->repeat)
		{
			break;
		}

		// If the function is finished and need to refresh screen.
		if (event->refresh)
		{
			commands.pop_front();
			if (commands.size() > 0)// && commands.front().order != command.order)
			{
				//SetCommandRead(command);
			}
			//SetInsertPosBack();
			break;
		}

		commands.pop_front();
		if (commands.size() > 0)// && commands.front().order != command.order)
		{
			//SetCommandRead(command);
		}
	}

	UnlockCommandQueue();
}

void SV8ScriptManager::AddCommand( SV8ScriptCommandPtr command )
{
	LockCommandQueue();

	commands.push_back(command);

	UnlockCommandQueue();
}

NODE_MODULE_CONTEXT_AWARE_BUILTIN(speshow, SV8ScriptManager::InitModule)