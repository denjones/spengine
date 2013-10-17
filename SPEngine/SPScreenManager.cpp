#include "StdAfx.h"
#include "SPScreenManager.h"

using namespace std;

namespace SPEngine
{
	SPScreenManager::SPScreenManager(void)
	{
	}

	SPScreenManager::~SPScreenManager(void)
	{
		displayStack.clear();

		Unload();

		screensMap.Clear();
	}

	bool SPScreenManager::Initialize()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Initialize();
		}

		SPComponent::Initialize();

		return true;
	}

	bool SPScreenManager::Load()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Load();
		}

		SPComponent::Load();

		return true;
	}

	bool SPScreenManager::Unload()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Unload();
		}

		SPComponent::Unload();

		return true;
	}

	bool SPScreenManager::Update( float timeElapsed )
	{
		bool isInputValid = true;//Game.IsActive;
		bool isVisible = true;

		for (int num = displayStack.size() - 1; num >= 0; num--)
		{
			SPBaseScreenPtr screen = displayStack[num];

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

	bool SPScreenManager::Draw( float timeElapsed )
	{
		if (displayStack.size() > 0)
		{
			vector<SPBaseScreenPtr>::iterator iter;
			for(iter = displayStack.begin(); iter != displayStack.end(); iter++)
			{
				(*iter)->Draw(timeElapsed);
			}
		}

		return true;
	}

	bool SPScreenManager::Register(SPString name)
	{
		if (!screensMap.IsSet(name))
		{
			return false;
		}

		if (IsInitialized())
		{
			screensMap[name]->Initialize();
		}	

		if (IsLoaded())
		{
			screensMap[name]->Load();
		}

		displayStack.push_back(screensMap[name]);

		return true;
	}

	bool SPScreenManager::Unregister( SPString name )
	{
		if (!screensMap.IsSet(name))
		{
			return true;
		}

		SPBaseScreenPtr screen = screensMap[name];
		vector<SPBaseScreenPtr>::iterator iter;
		for (iter = displayStack.begin(); iter != displayStack.end(); iter++ )
		{
			if (*iter == screen)
			{			
				displayStack.erase(iter);

				break;
			}
		}

		return true;
	}

	bool SPScreenManager::CreateScreen( SPString name, SPBaseScreenPtr screen )
	{
		screensMap.Set(name, screen);

		return true;
	}

	bool SPScreenManager::DestroyScreen( SPString name )
	{
		screensMap.Remove(name);

		return true;
	}
}
