//////////////////////////////////////////////////////////////////////////
/// @file		SPConfigManager.h the header file of SPConfigManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-12
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPConfig.h"
#include "SPSingleton.h"
#include "SPComponent.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ConfigManager class to hold game config.
	//////////////////////////////////////////////////////////////////////
	class SPConfigManager : 
		public SPComponent,
		public SPSingleton<SPConfigManager>
	{
		string configFile;		///< File path;
		SPConfigPtr currentConfig; ///< Current config.
		CCritSec modificationLock;

	public:
		SPConfigManager(void);
		virtual ~SPConfigManager(void);

		void SetDebug(bool on);
		bool LoadConfig(string path);
		bool SetConfig(SPConfigPtr config);
		SPConfigPtr GetCurrentConfig();
	};
}


