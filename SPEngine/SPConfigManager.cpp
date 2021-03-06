#include "StdAfx.h"
#include "SPConfigManager.h"
#include "SPGame.h"
#include "SPDevice.h"
#include <sxp.h>

namespace SPEngine
{
	SPConfigManager::SPConfigManager(void)
	{
		currentConfig = new SPConfig();
	}


	SPConfigManager::~SPConfigManager(void)
	{
		SXP::DestroyHT();
	}

	bool SPConfigManager::LoadConfig(string path)
	{
		configFile = path;

		FILE* file = NULL;

		// Check if the config file exists.
		fopen_s(&file, configFile.c_str(),"rb");

		if (file)
		{
			fclose(file);
			currentConfig->LoadFromFile(configFile);			
		}
		else
		{
			currentConfig->SaveAsFile(configFile);	
		}		

		return true;
	}

	bool SPConfigManager::SetConfig( SPConfigPtr config )
	{
		modificationLock.Lock();
		currentConfig = config;
		currentConfig->SaveAsFile(configFile);
		modificationLock.Unlock();

		return true;
	}

	SPEngine::SPConfigPtr SPConfigManager::GetCurrentConfig()
	{
		return currentConfig;
	}

	void SPConfigManager::SetDebug( bool on )
	{
		currentConfig->debug = on;
	}

}

