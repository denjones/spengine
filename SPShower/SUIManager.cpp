#include "StdAfx.h"
#include "SUIManager.h"
#include "SV8Function.h"


SUIManager::SUIManager(void)
{
	ZeroMemory(elapsedMouseDownTime, 3 * sizeof(float));
	ZeroMemory(elapsedMouseDownMovementX, 3 * sizeof(int));
	ZeroMemory(elapsedMouseDownMovementY, 3 * sizeof(int));
	ZeroMemory(elapsedMouseClickTime, 3 * sizeof(float));
	ZeroMemory(elapsedMouseClickMovementX, 3 * sizeof(int));
	ZeroMemory(elapsedMouseClickMovementY, 3 * sizeof(int));
	ZeroMemory(interceptMouseButtonEvent, 3 * sizeof(int));
	ZeroMemory(interceptKeyboardKeyEvent, 256 * sizeof(int));
	maxClickTime = 0.300f;
	maxDClickTime = 0.300f;
	dispalyStack = new ScreenStack();
	eventQueue = new EventQueue();
	asyncEvent = new uv_async_t();
}


SUIManager::~SUIManager(void)
{
	if (asyncEvent)
	{
		delete asyncEvent;
		asyncEvent = NULL;
	}
}

SUIScreenPtr SUIManager::GetScreen( SPString name )
{
	if (screenMap.IsSet(name))
	{
		return screenMap[name];
	}

	return NULL;
}

void SUIManager::AddScreen( SUIScreenPtr newScreen )
{
	screenMap.Set(newScreen->GetName(), newScreen);
	newScreen->Initialize();
	newScreen->Load();
	SetPersistentScreen(newScreen);
}

void SUIManager::Initialize()
{
	uv_async_init(uv_default_loop(), (uv_async_t*)asyncEvent, SUIManager::HandleAllEventCallback);
}

void SUIManager::Load()
{
	ScreenIterator iter(&screenMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Load();
		}		
	}
}

void SUIManager::Unload()
{
	ScreenIterator iter(&screenMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Unload();
		}		
	}
}

void SUIManager::Reload()
{
	ScreenIterator iter(&screenMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Reload();
		}		
	}
}

void SUIManager::Update( float timeDelta )
{
	GenerateEvent(timeDelta);
	bool isInputValid = true;
	bool isVisible = true;

	ScreenStackIterator screen = dispalyStack->rbegin();
	while(screen != dispalyStack->rend())
	{
		(*screen)->UpdateScreen(timeDelta, isInputValid, isVisible);

		if ((*screen)->State() == TransitionOn ||
			(*screen)->State() == Active)
		{
			if (isInputValid)
			{
				(*screen)->HandleInput(timeDelta);
				isInputValid = false;
			}

			if (!(*screen)->IsPopup())// && !(*screen)->GetTargetScreen())
			{
				isVisible = false;
			}
		}

		screen++;
	}

	if (eventQueue->size() > 0)
	{
		uv_async_send((uv_async_t*)asyncEvent);
	}
}

void SUIManager::Draw( float timeDelta )
{
	displayLock.Lock();

	ScreenStack::iterator screen = dispalyStack->begin();
	while(screen != dispalyStack->end())
	{
		(*screen)->Draw(timeDelta);

		screen++;
	}

	displayLock.Unlock();
}

void SUIManager::CreateScreen( SPString name, SUIScreenPtr newScreen )
{
	if (!newScreen)
	{
		return;
	}

	screenMap.Set(name, newScreen);

	newScreen->SetName(name);	
	newScreen->Initialize();
	newScreen->Load();

	SetPersistentScreen(newScreen);
}

SUIScreenPtr SUIManager::GetCurrentScreen()
{
	if (dispalyStack->size() > 0)
	{
		return dispalyStack->back();
	}

	return NULL;
	
}

void SUIManager::FocusScreen( SPString name )
{
	if (!screenMap.IsSet(name))
	{
		return;
	}

	FocusScreen(screenMap[name]);
}

void SUIManager::FocusScreen( SUIScreenPtr screen )
{
	ScreenStack::iterator iter = find(dispalyStack->begin(), dispalyStack->end(), screen);
	if (iter != dispalyStack->end())
	{
		dispalyStack->erase(iter);
	}

	dispalyStack->push_back(screen);
}

void SUIManager::SwitchToScreen( SPString name , SUITransformationPtr trans)
{	
	if (dispalyStack->size() == 0 || !screenMap.IsSet(name))
	{
		return;
	}

	if (dispalyStack->back() == screenMap[name])
	{
		return;
	}

	SUIScreenPtr top = dispalyStack->back();
	dispalyStack->pop_back();

	FocusScreen(name);

	dispalyStack->push_back(top);

	top->SetTargetScreen(screenMap[name]);
	top->SetTransformation(trans);
	trans->Play();
}

bool SUIManager::IsScreenValid( SPString name )
{
	return screenMap.IsSet(name);
}

void SUIManager::GenerateEvent(float timeDelta)
{
	//eventQueue->clear();

	LockEventQueue();

	SPMousePtr mouse = SPInputManager::GetSingleton()->GetMouse();
	SPKeyboardPtr keyboard = SPInputManager::GetSingleton()->GetKeyboard();
	

	if (mouse)
	{
		// Mouse move.
		if (mouse->GetMovementX() != 0 || mouse->GetMovementY() != 0)
		{
			SUIEventPtr e = new SUIEvent();
			
			e->type = SUIEvent::MouseMove;
			e->positionX = mouse->GetPositionX();
			e->positionY = mouse->GetPositionY();
			e->movementX = mouse->GetMovementX();
			e->movementY = mouse->GetMovementY();
			e->absoluteX = mouse->GetPositionX();
			e->absoluteY = mouse->GetPositionY();

			eventQueue->push_back(e);
		}

		// Mouse scroll.
		if (mouse->ScrolledPos() != 0)
		{
			SUIEventPtr e = new SUIEvent();

			e->type = SUIEvent::MouseScroll;
			e->positionX = mouse->GetPositionX();
			e->positionY = mouse->GetPositionY();
			e->movementX = 0;
			e->movementY = mouse->ScrolledPos();
			e->absoluteX = mouse->GetPositionX();
			e->absoluteY = mouse->GetPositionY();

			eventQueue->push_back(e);
		}

		// Mouse button.
		for (int button = 0; button < 3; button++)
		{
			if (interceptMouseButtonEvent[button])
			{
				interceptMouseButtonEvent[button] = 0;
				elapsedMouseDownTime[button] = maxClickTime;
				elapsedMouseClickTime[button] = maxDClickTime;
				continue;
			}

			if (mouse->ButtonJustDown(button))
			{
				// Begin calculate click time.
				elapsedMouseDownTime[button] = 0;
			}

			if (mouse->ButtonDown(button))
			{
				// Calculate click time.
				elapsedMouseDownTime[button] += timeDelta;

				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::MouseDown;
				e->button = button;
				e->positionX = mouse->GetPositionX();
				e->positionY = mouse->GetPositionY();
				e->movementX = mouse->GetMovementX();
				e->movementY = mouse->GetMovementY();
				e->absoluteX = mouse->GetPositionX();
				e->absoluteY = mouse->GetPositionY();

				eventQueue->push_back(e);

			}			

			if (mouse->ButtonJustUp(button) && mouse->IsWithinWindow())
			{
				// Define a click.
				if (elapsedMouseDownTime[button] < maxClickTime)
				{
					

					if (elapsedMouseClickTime[button] > 0 && 
						elapsedMouseClickTime[button] < maxDClickTime)
					{
						// Reset double click time.
						elapsedMouseClickTime[button] = 0;
						SUIEventPtr e = new SUIEvent();
						e->type = SUIEvent::MouseDClick;
						e->button = button;
						e->positionX = mouse->GetPositionX();
						e->positionY = mouse->GetPositionY();
						e->movementX = mouse->GetMovementX();
						e->movementY = mouse->GetMovementY();
						e->absoluteX = mouse->GetPositionX();
						e->absoluteY = mouse->GetPositionY();

						eventQueue->push_back(e);
					}
					else
					{
						// Begin calculate double click time.
						elapsedMouseClickTime[button] = timeDelta;
					}

					SUIEventPtr e = new SUIEvent();
					e->type = SUIEvent::MouseClick;
					e->button = button;
					e->positionX = mouse->GetPositionX();
					e->positionY = mouse->GetPositionY();
					e->movementX = mouse->GetMovementX();
					e->movementY = mouse->GetMovementY();
					e->absoluteX = mouse->GetPositionX();
					e->absoluteY = mouse->GetPositionY();

					eventQueue->push_back(e);
				}

				// Reset mouse down time.
				elapsedMouseDownTime[button] = 0;	

				// Button just Up event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::MouseUp;
				e->button = button;
				e->positionX = mouse->GetPositionX();
				e->positionY = mouse->GetPositionY();
				e->movementX = mouse->GetMovementX();
				e->movementY = mouse->GetMovementY();
				e->absoluteX = mouse->GetPositionX();
				e->absoluteY = mouse->GetPositionY();

				eventQueue->push_back(e);
			}

			// Calculate double click time.
			if(elapsedMouseClickTime[button] > 0)
			{
				elapsedMouseClickTime[button] += timeDelta;
			}
		}
	}

	if (keyboard)
	{
		for (UINT key = DIK_ESCAPE; key <= DIK_DELETE; key++)
		{
			if (interceptKeyboardKeyEvent[key])
			{
				interceptKeyboardKeyEvent[key] = 0;
				continue;
			}

			if (keyboard->ButtonDown(key))
			{
				// Key Press event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::KeyPress;
				e->button = key;

				eventQueue->push_back(e);
			}

			if (keyboard->ButtonJustDown(key))
			{
				// Key Down event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::KeyDown;
				e->button = key;

				eventQueue->push_back(e);
			}

			if (keyboard->ButtonJustUp(key))
			{
				// Key Up event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::KeyUp;
				e->button = key;

				eventQueue->push_back(e);
			}
		}
	}	

	UnlockEventQueue();
}

SPString SUIManager::SaveAsString()
{
	SPString result = L"<SUIManager>";

	result += L"<ScreenList>";

	ScreenIterator screenIter(&screenMap);

	for(screenIter.First(); !screenIter.IsDone(); screenIter.Next())
	{
		result += screenIter.CurrentItem()->SaveAsString();
	}

	result += L"</ScreenList>";

	result += L"<DisplayStack>";

	ScreenStackIterator screenStackIter = dispalyStack->rbegin();

	while(screenStackIter != dispalyStack->rend())
	{
		result += L"<ScreenName>";

		result += (*screenStackIter)->GetName();

		result += L"</ScreenName>";

		screenStackIter++;
	}

	result += L"</DisplayStack>";

	result += L"</SUIManager>";

	return result;
}

void SUIManager::LoadFromString( SPString stringStream )
{
	SPString screensString = SPStringHelper::XMLExcludeFrom(stringStream, L"ScreenList");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"ScreenList");

	while(screensString.size() > 0)
	{
		SPString screenString = SPStringHelper::XMLExcludeFrom(screensString, L"SUIScreen");
		screensString = SPStringHelper::XMLRemoveFirst(screensString, L"SUIScreen");

		SPString screenNameString = SPStringHelper::XMLExcludeFrom(screenString, L"Name");

		SUIScreenPtr screen = new SUIScreen();		
		screen->SetName(screenNameString);
		AddScreen(screen);
		dispalyStack->push_back(screen);
		screen->LoadFromString(screenString);		
	}

	dispalyStack->clear();

	SPString displayStackString = SPStringHelper::XMLExcludeFrom(stringStream, L"DisplayStack");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"DisplayStack");

	while(displayStackString.size() > 0)
	{
		SPString screenNameString = SPStringHelper::XMLExcludeFrom(displayStackString, L"ScreenName");
		displayStackString = SPStringHelper::XMLRemoveFirst(displayStackString, L"ScreenName");

		dispalyStack->push_front(GetScreen(screenNameString));
	}
}

void SUIManager::InterceptMouseBotton( int button )
{
	if (button < 0 || button >= 3)
	{
		return;
	}

	interceptMouseButtonEvent[button] = 1;
}

void SUIManager::InterceptKeyboardKey( int key )
{
	if (key < 0 || key >= 256)
	{
		return;
	}

	interceptKeyboardKeyEvent[key] = 1;
}

void SUIManager::SetPersistentScreen( SUIScreenPtr screen )
{
	persistentScreenMap[screen.get()] = screen;
}

SUIScreenPtr SUIManager::GetPersistentScreen( SUIScreen* screenPtr )
{
	if (persistentScreenMap.find(screenPtr) == persistentScreenMap.end())
	{
		return NULL;
	}

	return persistentScreenMap[screenPtr];
}

SUIManager::ScreenStackPtr SUIManager::GetDisplayStack()
{
	return dispalyStack;
}

SUIManager::EventQueuePtr SUIManager::GetEventQueue()
{
	return eventQueue;
}

void SUIManager::HandleAllEventCallback( uv_async_t *handle, int status )
{
	SUIManager::GetSingleton()->HandleAllEvent();
}

void SUIManager::LockEventQueue()
{
	eventLock.Lock();
}

void SUIManager::UnlockEventQueue()
{
	eventLock.Unlock();
}

void SUIManager::HandleAllEvent()
{
	LockEventQueue();

	ScreenStackIterator screen = dispalyStack->rbegin();
	while(screen != dispalyStack->rend())
	{
		if ((*screen)->State() == TransitionOn ||
			(*screen)->State() == Active)
		{
			while (eventQueue->size() > 0)
			{
				(*screen)->HandleEvent(eventQueue->front());
				eventQueue->pop_front();
			}

			break;
		}

		screen++;
	}

	UnlockEventQueue();
}

Handle<Object> SUIManager::SaveAsObj()
{
	Handle<Object> resultObj = Object::New();

	Handle<Object> screenDict = Object::New();
	ScreenIterator screenIter = ScreenIterator(&screenMap);
	for (screenIter.First(); !screenIter.IsDone(); screenIter.Next())
	{
		screenDict->Set(SPV8ScriptEngine::SPStringToString(screenIter.CurrentIndex()), screenIter.CurrentItem()->SaveAsObj());
	}
	resultObj->Set(SPV8ScriptEngine::SPStringToString(L"screens"), screenDict);

	Handle<Array> displayStackArr = Array::New();
	for (ScreenStackIterator displayIter = dispalyStack->rbegin(); displayIter != dispalyStack->rend(); displayIter++)
	{
		displayStackArr->Set(displayStackArr->Length(), SPV8ScriptEngine::SPStringToString((*displayIter)->GetName()));
	}
	resultObj->Set(SPV8ScriptEngine::SPStringToString(L"display"), displayStackArr);

	return resultObj;
}

Handle<Object> SUIManager::SaveScreenAsObj( SPString screensStr )
{
	Handle<Object> resultObj = Object::New();
	Handle<Object> screenDict = Object::New();

	if (screensStr == L"*")
	{
		
		ScreenIterator screenIter = ScreenIterator(&screenMap);
		for (screenIter.First(); !screenIter.IsDone(); screenIter.Next())
		{
			screenDict->Set(SPV8ScriptEngine::SPStringToString(screenIter.CurrentIndex()), screenIter.CurrentItem()->SaveAsObj());
		}
		resultObj->Set(SPV8ScriptEngine::SPStringToString(L"screens"), screenDict);

		Handle<Array> displayStackArr = Array::New();
		for (ScreenStackIterator displayIter = dispalyStack->rbegin(); displayIter != dispalyStack->rend(); displayIter++)
		{
			displayStackArr->Set(displayStackArr->Length(), SPV8ScriptEngine::SPStringToString((*displayIter)->GetName()));
		}
		resultObj->Set(SPV8ScriptEngine::SPStringToString(L"display"), displayStackArr);
	}
	else
	{
		size_t pos = screensStr.find(',');
		if (pos == SPString::npos)
		{
			SPString screenName = screensStr;
			if (screenMap.IsSet(screenName))
			{
				screenDict->Set(SPV8ScriptEngine::SPStringToString(screenName), screenMap[screenName]->SaveAsObj());
			}
		}
		else
		{
			do
			{
				SPString screenStr = screensStr.substr(0, pos);
				screensStr = screensStr.substr(pos + 1);
				if (screenMap.IsSet(screenStr))
				{
					screenDict->Set(SPV8ScriptEngine::SPStringToString(screenStr), screenMap[screensStr]->SaveAsObj());
				}
				pos = screensStr.find(L',');
			}while(pos != SPString::npos);

			if (screenMap.IsSet(screensStr))
			{
				screenDict->Set(SPV8ScriptEngine::SPStringToString(screensStr), screenMap[screensStr]->SaveAsObj());
			}
		}
		resultObj->Set(SPV8ScriptEngine::SPStringToString(L"screens"), screenDict);
	}
	return resultObj;
}

void SUIManager::LoadFromObj(Handle<Object> obj)
{
	displayLock.Lock();

	if (SV8Function::HasProperty(L"display", obj))
	{
		dispalyStack->clear();
		screenMap.Clear();
	}

	if (SV8Function::HasProperty(L"screens", obj))
	{
		Handle<Object> screens = Handle<Object>::Cast(SV8Function::GetProperty(L"screens", obj));
		const Local<Array> props = screens->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = screens->Get(key);

			SUIScreenPtr screen = new SUIScreen();
			screen->LoadFromObj(Handle<Object>::Cast(value));
			screenMap.Set(SPV8ScriptEngine::StringToSPString(key->ToString()), screen);
			SetPersistentScreen(screen);
		}
	}

	if (SV8Function::HasProperty(L"display", obj))
	{
		Handle<Array> display = Handle<Array>::Cast(SV8Function::GetProperty(L"display", obj));
		for (int i = 0; i < display->Length(); i++)
		{
			SPString screenName = SPV8ScriptEngine::StringToSPString(display->Get(i)->ToString());
			if (screenMap.IsSet(screenName))
			{
				dispalyStack->push_back(screenMap[screenName]);
			}
		}

		dispalyStack->back()->Focus();
	}

	displayLock.Unlock();
}



