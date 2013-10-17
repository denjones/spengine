#include "StdAfx.h"
#include "screenManager.h"

using namespace SPEngine;
using namespace std;

ScreenManager::ScreenManager(void)
{
}

ScreenManager::~ScreenManager(void)
{
	foreach(BaseScreen*, screen, vector<BaseScreen*>, screens)
	{
		if (screen)
		{
			screen->Unload();
			delete screen;
			screen = NULL;
		}
	}
}

bool ScreenManager::Initialize()
{
	foreach(BaseScreen*, screen, vector<BaseScreen*>, screens)
	{
		screen->Initialize();
	}

	return true;
}

bool ScreenManager::Load()
{
	foreach(BaseScreen*, screen, vector<BaseScreen*>, screens)
	{
		screen->Load();
	}

	return true;
}

bool ScreenManager::Unload()
{
	foreach(BaseScreen*, screen, vector<BaseScreen*>, screens)
	{
		if (screen)
		{
			screen->Unload();
		}
	}

	return true;
}

bool ScreenManager::Update( float timeElapsed )
{
	bool isInputValid = true;//Game.IsActive;
	bool isVisible = true;

	for (int num = screens.size() - 1; num >= 0; num--)
	{
		BaseScreen* screen = screens[num];

		screen->UpdateScreen(timeElapsed, isInputValid, isVisible);

		if (screen->State() == TransitionOn ||
			screen->State() == Active)
		{
			if (isInputValid)
			{
				screen->HandleInput(timeElapsed);
				isInputValid = false;
			}

			if (!screen->IsPopup())
			{
				isVisible = false;
			}
		}
	}

	return true;
}

bool ScreenManager::Draw( float timeElapsed )
{
	if (screens.size() > 0)
	{
		vector<BaseScreen*>::iterator iter;
		for(iter = screens.begin(); iter != screens.end(); iter++)
		{
			(*iter)->Draw(timeElapsed);
		}
	}

	return true;
}

bool ScreenManager::AddScreen( BaseScreen* screen )
{
	screen->Register(this);
	screen->Initialize();
	screen->Load();

	screens.push_back(screen);

	return true;
}

bool ScreenManager::RemoveScreen( BaseScreen* screen )
{
	vector<BaseScreen*>::iterator iter;
	for (iter = screens.begin(); iter != screens.end(); iter++ )
	{
		if (*iter == screen)
		{
			//screen->Unload();
			screens.erase(iter);
			
			break;
		}
	}

	return true;
}
