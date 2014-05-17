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

		void Load();
		void Unload();
		void Update(float timeElapsed);
		void Draw(float timeElapsed);
		void Initialize();

		/// @name Screen Management.
		/// @{
		void Register(SPString name);
		void Unregister(SPString name);
		void CreateScreen(SPString name, SPBaseScreenPtr screen);
		void DestroyScreen(SPString name);
		/// @}
	};
}


