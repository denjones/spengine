//////////////////////////////////////////////////////////////////////////
/// @file		SPScreenManager.h the header file of SPScreenManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-30
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPComponent.h"
#include "SPBaseScreen.h"
#include "SPSingleton.h"
#include "SPStringMap.h"
#include <vector>

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPScreenManager
	/// A singleton to hold and manage game screen.
	///
	//////////////////////////////////////////////////////////////////////
	class SPScreenManager :
		public SPComponent,
		public SPSingleton<SPScreenManager>
	{
	protected:
		vector<SPBaseScreenPtr> displayStack;	///< The stack of screens which would be displayed.
		SPWStringMap<SPBaseScreenPtr> screensMap; ///< The map to hold all screens.

	public:
		SPScreenManager(void);
		virtual ~SPScreenManager(void);

		bool Load();
		bool Unload();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();

		/// @name Screen Management.
		/// @{
		bool Register(SPString name);
		bool Unregister(SPString name);
		bool CreateScreen(SPString name, SPBaseScreenPtr screen);
		bool DestroyScreen(SPString name);
		/// @}
	};
}


