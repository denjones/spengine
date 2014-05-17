//////////////////////////////////////////////////////////////////////////
/// @file		SPComponentManager.h the header file of SPComponentManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SPComponent.h"
#include "SPSingleton.h"
#include <list>
#include "SPStringMap.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPComponentManager class to hold game component.
	/// 
	/// ComponentManager is used for adding component and manage 
	/// registered components.
	//////////////////////////////////////////////////////////////////////
	class SPComponentManager : public SPSingleton<SPComponentManager>
	{
	private:
		SPWStringMap<SPComponentPtr> componentMap;
		list<SPComponentPtr> components;	///< A list to hold game components.
		bool isInitialized;					///< If batch initialized.
		bool isLoaded;						///< If batch loaded.

	public:
		SPComponentManager(void);
		virtual ~SPComponentManager(void);

		/// @name Action
		/// @{
	public:
		bool Initialize();
		bool Load();
		bool Unload();
		bool Reload();
		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		/// @}

		/// @name Register
		/// @{
	public:
		bool RegisterComponent(SPString name, SPComponentPtr newComponent);
		bool UnregisterComponent(SPString name);
		SPComponentPtr GetComponent(SPString name);
		void Clear();
		/// @}
	};
}

