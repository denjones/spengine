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
			if (!component->Initialize())
			{
				MessageBoxA(NULL, "Failed to initialize game component!",
					NULL, NULL);

				return false;
			}
		}

		isInitialized = true;

		return true;
	}

	bool SPComponentManager::Load()
	{
		// Force all registered components to load contents.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			if (!component->Load())
			{
				MessageBoxA(NULL, "Failed to load game content!",
					NULL, NULL);

				return false;
			}			
		}

		isLoaded = true;

		return true;
	}

	bool SPComponentManager::Unload()
	{
		// Force all registered components to unload contents.
		foreach(SPComponentPtr, component, list<SPComponentPtr>, components)
		{
			if (!component->Unload())
			{
				MessageBoxA(NULL, "Failed to unload game content!",
					NULL, NULL);

				return false;
			}

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
				if (!component->Update(timeDelta))
				{
					MessageBoxA(NULL, "Runtime error!",
						NULL, NULL);

					return false;
				}
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
				if (!component->PreDraw() ||
					!component->Draw(timeDelta) ||
					!component->PostDraw())
				{				
					MessageBoxA(NULL, "Runtime error!",
						NULL, NULL);

					return false;
				}				
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
			if (!component->Reload())
			{
				MessageBoxA(NULL, "Failed to load game content!",
					NULL, NULL);

				return false;
			}			
		}

		isLoaded = true;

		return true;
	}

	SPEngine::SPComponentPtr SPComponentManager::GetComponent( SPString name )
	{
		return componentMap.Get(name);
	}
}