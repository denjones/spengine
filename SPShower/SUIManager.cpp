#include "StdAfx.h"
#include "SUIManager.h"


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
	dispalyStack.clear();
}


SUIManager::~SUIManager(void)
{
}

SUIScreenPtr SUIManager::GetScreen( SPString name )
{
	if (screenMap.IsSet(name))
	{
		return screenMap[name];
	}

	return NULL;
}

bool SUIManager::AddScreen( SUIScreenPtr newScreen )
{
	screenMap.Set(newScreen->GetName(), newScreen);
	newScreen->Initialize();
	newScreen->Load();
	SetPersistentScreen(newScreen);
	return true;
}

bool SUIManager::Initialize()
{
	return true;
}

bool SUIManager::Load()
{
	ScreenIterator iter(&screenMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Load();
		}		
	}

	return true;
}

bool SUIManager::Unload()
{
	ScreenIterator iter(&screenMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Unload();
		}		
	}

	return true;
}

bool SUIManager::Update( float timeDelta )
{
	GenerateEvent(timeDelta);
	bool isInputValid = true;
	bool isVisible = true;

	ScreenStackIterator screen = dispalyStack.rbegin();
	while(screen != dispalyStack.rend())
	{
		if(!(*screen)->UpdateScreen(timeDelta, isInputValid, isVisible))
		{			
			screen =  ScreenStackIterator(dispalyStack.erase((++screen).base()));
			continue;
		}

		if ((*screen)->State() == TransitionOn ||
			(*screen)->State() == Active)
		{
			if (isInputValid)
			{
				while (eventQueue.size() > 0)
				{
					(*screen)->HandleEvent(eventQueue.front());
					eventQueue.pop_front();
				}
				
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

	return true;
}

bool SUIManager::Draw( float timeDelta )
{
	ScreenStack::iterator screen = dispalyStack.begin();
	while(screen != dispalyStack.end())
	{
		(*screen)->Draw(timeDelta);

		screen++;
	}

	return true;
}

bool SUIManager::CreateScreen( SPString name, SUIScreenPtr newScreen )
{
	if (!newScreen)
	{
		return false;
	}

	screenMap.Set(name, newScreen);

	newScreen->SetName(name);	
	newScreen->Initialize();
	newScreen->Load();

	SetPersistentScreen(newScreen);

	return true;
}

SUIScreenPtr SUIManager::GetCurrentScreen()
{
	if (dispalyStack.size() > 0)
	{
		return dispalyStack.back();
	}

	return NULL;
	
}

bool SUIManager::FocusScreen( SPString name )
{
	if (!screenMap.IsSet(name))
	{
		return false;
	}

	return FocusScreen(screenMap[name]);
}

bool SUIManager::FocusScreen( SUIScreenPtr screen )
{
	ScreenStack::iterator iter = find(dispalyStack.begin(), dispalyStack.end(), screen);
	if (iter != dispalyStack.end())
	{
		dispalyStack.erase(iter);
	}

	dispalyStack.push_back(screen);

	return true;
}

bool SUIManager::SwitchToScreen( SPString name , SUITransformationPtr trans)
{	
	if (dispalyStack.size() == 0 || !screenMap.IsSet(name))
	{
		return false;
	}

	if (dispalyStack.back() == screenMap[name])
	{
		return true;
	}

	SUIScreenPtr top = dispalyStack.back();
	dispalyStack.pop_back();

	FocusScreen(name);

	dispalyStack.push_back(top);

	top->SetTargetScreen(screenMap[name]);
	top->SetTransformation(trans);
	trans->Play();

	return true;
}

bool SUIManager::IsScreenValid( SPString name )
{
	return screenMap.IsSet(name);
}

bool SUIManager::GenerateEvent(float timeDelta)
{
	eventQueue.clear();

	SPMousePtr mouse = SPInputManager::GetSingleton().GetMouse();
	SPKeyboardPtr keyboard = SPInputManager::GetSingleton().GetKeyboard();
	

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

			//SPFontWriter::GetSingleton().Write(NULL, NULL, SPStringHelper::ToWString(e->positionX), D3DXVECTOR2(0, 0), SPColor::Red, 0, 0, NULL );
			//SPFontWriter::GetSingleton().Write(NULL, NULL, SPStringHelper::ToWString(e->positionY), D3DXVECTOR2(0, 20), SPColor::Red, 0, 0, NULL );
			//SPFontWriter::GetSingleton().Write(NULL, NULL, SPStringHelper::ToWString(e->movementX), D3DXVECTOR2(0, 40), SPColor::Red, 0, 0, NULL );
			//SPFontWriter::GetSingleton().Write(NULL, NULL, SPStringHelper::ToWString(e->movementY), D3DXVECTOR2(0, 60), SPColor::Red, 0, 0, NULL );

			eventQueue.push_back(e);
		}

		// Mouse scroll.
		if (mouse->IsScrolledUp())
		{
			SUIEventPtr e = new SUIEvent();

			e->type = SUIEvent::MouseScrollUp;
			e->positionX = mouse->GetPositionX();
			e->positionY = mouse->GetPositionY();
			e->movementX = mouse->GetMovementX();
			e->movementY = mouse->GetMovementY();

			eventQueue.push_back(e);
		}
		else if (mouse->IsScrolledDown())
		{
			SUIEventPtr e = new SUIEvent();

			e->type = SUIEvent::MouseScrollDown;
			e->positionX = mouse->GetPositionX();
			e->positionY = mouse->GetPositionY();
			e->movementX = mouse->GetMovementX();
			e->movementY = mouse->GetMovementY();

			eventQueue.push_back(e);
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

				eventQueue.push_back(e);

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

						eventQueue.push_back(e);
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

					eventQueue.push_back(e);
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

				eventQueue.push_back(e);
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

				eventQueue.push_back(e);
			}

			if (keyboard->ButtonJustDown(key))
			{
				// Key Down event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::KeyDown;
				e->button = key;

				eventQueue.push_back(e);
			}

			if (keyboard->ButtonJustUp(key))
			{
				// Key Up event.
				SUIEventPtr e = new SUIEvent();

				e->type = SUIEvent::KeyUp;
				e->button = key;

				eventQueue.push_back(e);
			}
		}
	}	

	return true;
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

	ScreenStackIterator screenStackIter = dispalyStack.rbegin();

	while(screenStackIter != dispalyStack.rend())
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

bool SUIManager::LoadFromString( SPString stringStream )
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
		dispalyStack.push_back(screen);
		screen->LoadFromString(screenString);		
	}

	dispalyStack.clear();

	SPString displayStackString = SPStringHelper::XMLExcludeFrom(stringStream, L"DisplayStack");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"DisplayStack");

	while(displayStackString.size() > 0)
	{
		SPString screenNameString = SPStringHelper::XMLExcludeFrom(displayStackString, L"ScreenName");
		displayStackString = SPStringHelper::XMLRemoveFirst(displayStackString, L"ScreenName");

		dispalyStack.push_front(GetScreen(screenNameString));
	}

	return true;
}

bool SUIManager::InterceptMouseBotton( int button )
{
	if (button < 0 || button >= 3)
	{
		return false;
	}

	interceptMouseButtonEvent[button] = 1;

	return true;
}

bool SUIManager::InterceptKeyboardKey( int key )
{
	if (key < 0 || key >= 256)
	{
		return false;
	}

	interceptKeyboardKeyEvent[key] = 1;

	return true;
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

