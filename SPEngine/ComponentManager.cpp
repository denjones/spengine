#include "StdAfx.h"
#include "ComponentManager.h"

namespace SPEngine
{
	ComponentManager::ComponentManager(void)
	{
		isInitialized = false;
		isLoaded = false;
	}


	ComponentManager::~ComponentManager(void)
	{
	}

	bool ComponentManager::Initialize()
	{
		// Initialize registered components.
		foreach(SPComponent*, component, list<SPComponent*>, components)
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

	bool ComponentManager::Load()
	{
		// Force all registered components to load contents.
		foreach(SPComponent*, component, list<SPComponent*>, components)
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

	bool ComponentManager::Unload()
	{
		// Force all registered components to unload contents.
		foreach(SPComponent*, component, list<SPComponent*>, components)
		{
			if (!component->Unload())
			{
				MessageBoxA(NULL, "Failed to unload game content!",
					NULL, NULL);

				return false;
			}

		}

		return true;
	}

	bool ComponentManager::Update( float timeDelta )
	{
		// Update registered components.
		foreach(SPComponent*, component, list<SPComponent*>, components)
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

	bool ComponentManager::Draw( float timeDelta )
	{
		// Draw registered components.
		foreach(SPComponent*, component, list<SPComponent*>, components)
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

	bool ComponentManager::RegisterComponent( SPComponent* newComponent )
	{
		foreach(SPComponent*, component, list<SPComponent*>, components)
		{
			if (component == newComponent)
			{
				return false;
			}
		}

		if (isInitialized && !newComponent->IsInitialized())
		{
			newComponent->Initialize();
		}

		if (isLoaded && !newComponent->IsLoaded())
		{
			newComponent->Load();
		}

		components.push_back(newComponent);

		return true;
	}

	bool ComponentManager::UnregisterComponent( SPComponent* component )
	{
		foreach(SPComponent*, iComponent, list<SPComponent*>, components)
		{
			if (component == iComponent)
			{
				iComponent->Unload();
				components.erase(iter);
				return true;
			}
		}

		return false;
	}
}