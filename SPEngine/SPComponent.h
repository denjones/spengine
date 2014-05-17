//////////////////////////////////////////////////////////////////////////
/// @file		SPComponent.h the header file of base SPComponent class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-15
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "ISPUpdatable.h"
#include "ISPLoadable.h"
#include "ISPDrawable.h"
#include "SPPointer.h"

namespace SPEngine
{
	class SPGame;

	class SPComponentManager;

	//////////////////////////////////////////////////////////////////////
	/// @brief	SPComponent class to represent a component in the game, 
	/// which can be updated, drawn and loaded.
	//////////////////////////////////////////////////////////////////////
	class SPComponent : 
		public ISPUpdatable,
		public ISPLoadable,
		public ISPDrawable
	{
	protected:
		bool isInitialized;
		bool isLoaded;
		bool isEnabled;

		/// @name Properties
		/// @{
	public:
		bool IsEnabled() const {return isEnabled;}
		bool IsInitialized() const {return isInitialized;}
		bool IsLoaded() const {return isLoaded;}
		/// @}

	public:
		SPComponent(void);
		//SPComponent(ComponentManager& manager);
		virtual ~SPComponent(void);

		/// @name Enable for updating
		/// @{
		void Enable();
		void Disable();
		/// @}

		/// @name Register
		/// @{
		//bool Register(ComponentManager& manager);
		//bool Unregister(ComponentManager& manager);
		/// @}

		/// @name Action
		/// @{
		virtual void Initialize();
		virtual void Load();
		virtual void Unload();
		virtual void Reload();
		virtual void Update(float timeElapsed);
		virtual void PreDraw();
		virtual void Draw(float timeElapsed);
		virtual void PostDraw();
		/// @}
	};

	typedef SPPointer<SPComponent> SPComponentPtr;
}


