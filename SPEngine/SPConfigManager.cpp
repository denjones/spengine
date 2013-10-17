#include "StdAfx.h"
#include "SPConfigManager.h"
#include "SPGame.h"
#include "SPDevice.h"
#include <sxp.h>

#pragma warning(disable:4996)

namespace SPEngine
{
	SPConfigManager::SPConfigManager(void)
	{
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
		file = fopen(configFile.c_str(),"rb");

		if (file)
		{
			fclose(file);
			currentConfig.LoadFromFile(configFile);			
		}
		else
		{
			currentConfig.SaveAsFile(configFile);	
		}		

		return true;
	}

	bool SPConfigManager::SetConfig( SPConfig &config )
	{
		currentConfig = config;
		currentConfig.SaveAsFile(configFile);

		return true;
	}

	SPEngine::SPConfig SPConfigManager::GetCurrentConfig()
	{
		return currentConfig;
	}
}

