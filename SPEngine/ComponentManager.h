//////////////////////////////////////////////////////////////////////////
/// @file		ComponentManager.h the header file of ComponentManager class.
/// @author		Ken.J
/// @version	Beta 0.3
/// @date		2012-3-9
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SPComponent.h"
#include <list>

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ComponentManager class to hold game component.
	/// 
	/// ComponentManager is in use of adding component and manage 
	/// registered components.
	//////////////////////////////////////////////////////////////////////
	class ComponentManager
	{
	private:
		list<SPComponent*>	components; ///< A list to hold game components.
		bool isInitialized;
		bool isLoaded;

	public:
		ComponentManager(void);
		~ComponentManager(void);

	public:
		bool Initialize();
		bool Load();
		bool Unload();
		bool Update(float timeDelta);
		bool Draw(float timeDelta);

	public:
		bool RegisterComponent(SPComponent* newComponent);
		bool UnregisterComponent(SPComponent* component);
	};
}

