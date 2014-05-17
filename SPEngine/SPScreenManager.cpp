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

	void SPScreenManager::Initialize()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Initialize();
		}

		SPComponent::Initialize();
	}

	void SPScreenManager::Load()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Load();
		}

		SPComponent::Load();
	}

	void SPScreenManager::Unload()
	{
		SPWStringMapIterator<SPBaseScreenPtr> iter(&screensMap);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Unload();
		}

		SPComponent::Unload();
	}

	void SPScreenManager::Update( float timeElapsed )
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
	}

	void SPScreenManager::Draw( float timeElapsed )
	{
		if (displayStack.size() > 0)
		{
			vector<SPBaseScreenPtr>::iterator iter;
			for(iter = displayStack.begin(); iter != displayStack.end(); iter++)
			{
				(*iter)->Draw(timeElapsed);
			}
		}
	}

	void SPScreenManager::Register(SPString name)
	{
		if (!screensMap.IsSet(name))
		{
			return;
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
	}

	void SPScreenManager::Unregister( SPString name )
	{
		if (!screensMap.IsSet(name))
		{
			return;
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
	}

	void SPScreenManager::CreateScreen( SPString name, SPBaseScreenPtr screen )
	{
		screensMap.Set(name, screen);
	}

	void SPScreenManager::DestroyScreen( SPString name )
	{
		screensMap.Remove(name);
	}
}
