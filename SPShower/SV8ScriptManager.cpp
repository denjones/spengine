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
	exitAsync = new uv_async_t();
	gotoFile = L"";
	gotoTag = L"";
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

	if (exitAsync)
	{
		delete exitAsync;
		exitAsync = NULL;
	}
}

void SV8ScriptManager::Initialize()
{
	// Init uv callback

	uv_async_init(uv_default_loop(), (uv_async_t*)async, HandleCommandCallback);
	uv_async_init(uv_default_loop(), (uv_async_t*)exitAsync, OnExit);

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

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
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
}

void SV8ScriptManager::Update( float timeDelta )
{
	if(!isScriptRunning) 
	{
		isScriptRunning = true;

		SPV8ScriptEngine::GetSingleton()->RunScriptFromFile(L"init.js");
	}

	uv_async_send((uv_async_t*)async);
}

void SV8ScriptManager::Load()
{
}

void SV8ScriptManager::Reload()
{
}

void SV8ScriptManager::Unload()
{
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
	exports->Set(SPV8ScriptEngine::SPStringToString(L"addTag"), FunctionTemplate::New(SV8Function::AddTag)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"goto"), FunctionTemplate::New(SV8Function::Goto)->GetFunction());
	exports->Set(SPV8ScriptEngine::SPStringToString(L"saveStateAs"), FunctionTemplate::New(SV8Function::SaveStateAs)->GetFunction());

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

	if (gotoFile != L"")
	{
		commands.clear();

		HandleScope handleScope(SPV8ScriptEngine::GetSingleton()->GetIsolate());
		SPV8ScriptEngine::GetSingleton()->EvalFile(gotoFile, true);

		if (gotoTag != L"")
		{
			while(commands.size() > 0)
			{
				SV8ScriptCommandPtr command = commands.front();
				if (command->tag == gotoTag)
				{
					break;
				}
				commands.pop_front();
			}
		}

		gotoFile = L"";
		gotoTag = L"";
	}

	while(commands.size() > 0)
	{
		// Accept Function.
		SV8ScriptCommandPtr command = commands.front();
		SV8CommandEventPtr event = new SV8CommandEvent();
		event->read = IsCommandRead(command);

		// Use function.
		if (!command->IsTag())
		{
			command->Call(event);
		}

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
				SetCommandRead(command);
			}
			//SetInsertPosBack();
			break;
		}

		commands.pop_front();
		if (commands.size() > 0)// && commands.front().order != command.order)
		{
			SetCommandRead(command);
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

bool SV8ScriptManager::IsCommandRead( SV8ScriptCommandPtr command )
{
	if (command->file == L"")
	{
		return false;
	}

	if (!readCommands.IsSet(command->file))
	{
		return false;
	}

	ReadListPtr readOrderList = readCommands.Get(command->file);

	ReadList::iterator iter = readOrderList->begin();

	while(iter != readOrderList->end())
	{
		ReadRegionPtr region = (*iter);
		if (region->startLine <= command->line &&
			region->startCol <= command->col &&
			command->line <= region->endLine &&
			command->col <= region->endCol)
		{
			return true;
		}

		iter++;
	}

	return false;
}

void SV8ScriptManager::SetCommandRead( SV8ScriptCommandPtr command )
{
	if (currentRegion)
	{
		currentRegion->endLine = command->line;
		currentRegion->endCol = command->col;
	}
	else if (!IsCommandRead(command))
	{
		ReadRegionPtr region = new ReadRegion();
		region->startCol = command->col;
		region->startLine = command->line;
		region->endCol = command->col;
		region->endLine = command->line;
		ReadListPtr readList;
		if (readCommands.IsSet(command->file))
		{
			readList = readCommands.Get(command->file);
		}
		else
		{
			readList = new ReadList();
			readCommands.Set(command->file, readList);
		}
		readList->push_back(region);
	}
}

void SV8ScriptManager::Goto( SPString file, SPString tag )
{
	gotoFile = file;
	gotoTag = tag;
}

Handle<Object> SV8ScriptManager::SaveAsObj()
{
	// Serialize Command List

	Handle<Object> result = Object::New();
	Handle<Array> commandList = Array::New();

	CommandIterator iter = commands.begin();
	while(iter != commands.end())
	{
		Handle<v8::Function> func = Handle<v8::Function>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), *((*iter)->v8Function));
		commandList->Set(commandList->Length(), func->ToString());
		iter++;
	}

	result->Set(SPV8ScriptEngine::SPStringToString(L"commands"), commandList);

	// Serialize Window Obj

	Handle<Object> windowObj = SPV8ScriptEngine::CopyObject(SV8ScriptManager::GetSingleton()->GetWindowTemplate()->NewInstance());
	if (onExit)
	{
		windowObj->Set(SPV8ScriptEngine::SPStringToString(L"onExit"), GetOnExitFunc()->ToString());
	}
	result->Set(SPV8ScriptEngine::SPStringToString(L"window"), windowObj);

	return result;
}

void SV8ScriptManager::LoadFromObj( Handle<Object> obj )
{
	return;
}

Handle<Object> SV8ScriptManager::SaveReadAsObj()
{
	Handle<Object> result = Object::New();
	SPWStringMapIterator<ReadListPtr> iter(&readCommands);
	for(iter.First(); !iter.IsDone(); iter.Next())
	{
		Handle<Array> readArray = Array::New();
		ReadListPtr readList = iter.CurrentItem();
		ReadList::iterator innerIter = readList->begin();
		while(innerIter != readList->end())
		{
			Handle<Object> item = Object::New();
			item->Set(SPV8ScriptEngine::SPStringToString(L"startLine"), Integer::New((*innerIter)->startLine));
			item->Set(SPV8ScriptEngine::SPStringToString(L"startCol"), Integer::New((*innerIter)->startLine));
			item->Set(SPV8ScriptEngine::SPStringToString(L"endLine"), Integer::New((*innerIter)->startLine));
			item->Set(SPV8ScriptEngine::SPStringToString(L"endCol"), Integer::New((*innerIter)->startLine));
			readArray->Set(readArray->Length(), item);
			innerIter++;
		}
		result->Set(SPV8ScriptEngine::SPStringToString(iter.CurrentIndex()), readArray);
	}
	return result;
}

void SV8ScriptManager::Exit()
{
	uv_async_send((uv_async_t*)exitAsync);
}

void SV8ScriptManager::OnExit( uv_async_t *handle, int status )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);
	Handle<v8::Function> onExit = Handle<v8::Function>::Cast(SV8ScriptManager::GetSingleton()->GetOnExitFunc());
	Handle<Value> a[1];
	if (onExit->IsNull() || onExit->Call(isolate->GetCurrentContext()->Global(), 0, a)->BooleanValue())
	{
		SPGameManager::GetSingleton()->GetGame()->Exit();
	}
}

Handle<v8::Value> SV8ScriptManager::GetOnExitFunc()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	if (onExit)
	{
		return Handle<v8::Function>::New(isolate, *onExit);
	}

	return v8::Null();
}

void SV8ScriptManager::SetOnExitFunc( Handle<v8::Function> func )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	onExit = new Persistent<v8::Function>(isolate,func);
}

NODE_MODULE_CONTEXT_AWARE_BUILTIN(speshow, SV8ScriptManager::InitModule)