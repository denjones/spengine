#include "StdAfx.h"
#include "SPComponentManager.h"

namespace SPEngine
{
	SPComponentManager::SPComponentManager(void)
	{
		isInitialized = false;
		isLoaded = false;
	}

	SPComponentManager::~SPComponentManager(void)
	{
		//componentMap.Clear();
		//components.clear();
	}

	bool SPComponentManager::Initialize()
	{
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			component->Initialize();
		}

		isInitialized = true;

		return true;
	}

	bool SPComponentManager::Load()
	{
		// Force all registered components to load contents.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			component->Load();	
		}

		isLoaded = true;

		return true;
	}

	bool SPComponentManager::Unload()
	{
		// Force all registered components to unload contents.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			component->Unload();
		}

		isLoaded = false;

		return true;
	}

	bool SPComponentManager::Update( float timeDelta )
	{
		// Update registered components.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			if (component->IsEnabled())
			{
				component->Update(timeDelta);
			}		
		}

		return true;
	}

	bool SPComponentManager::Draw( float timeDelta )
	{
		// Draw registered components.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			if (component->IsEnabled())
			{
				component->PreDraw();
				component->Draw(timeDelta);
				component->PostDraw();		
			}
		}

		return true;
	}

	bool SPComponentManager::RegisterComponent( SPString name, SPComponentPtr newComponent )
	{
		if (componentMap.IsSet(name))
		{
			return false;
		}

		if (isInitialized && !newComponent->IsInitialized())
		{
			newComponent->Initialize();
		}

		if (isLoaded && !newComponent->IsLoaded())
		{
			newComponent->Load();
		}

		componentMap.Set(name, newComponent);
		components.push_back(newComponent);

		return true;
	}

	bool SPComponentManager::UnregisterComponent( SPString name )
	{
		if (!componentMap.IsSet(name))
		{
			return false;
		}

		SPComponentPtr component = GetComponent(name);
		componentMap.Remove(name);

		foreach(SPComponentPtr, iComponent, list<SPComponentPtr>, components)
		{
			if (iComponent == component)
			{
				iComponent = NULL;
				components.erase(iter);
				return true;
			}
		}

		return false;
	}

	bool SPComponentManager::Reload()
	{
		// Force all registered components to load contents.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			component->Reload();
		}

		isLoaded = true;

		return true;
	}

	SPEngine::SPComponentPtr SPComponentManager::GetComponent( SPString name )
	{
		return componentMap.Get(name);
	}

	void SPComponentManager::Clear()
	{
		componentMap.Clear();
		components.clear();
	}
}