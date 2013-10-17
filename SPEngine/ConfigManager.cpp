#include "StdAfx.h"
#include "ConfigManager.h"
#include "SPGame.h"

namespace SPEngine
{
	ConfigManager::ConfigManager(void)
	{
	}


	ConfigManager::~ConfigManager(void)
	{
	}

	bool ConfigManager::Initialize()
	{
		FILE* file = NULL;

		// Check if the config file exists.
		file = fopen("config.cfg","rb");

		if (file)
		{
			fclose(file);
			currentConfig.LoadFromFile("config.cfg");			
		}
		else
		{
			currentConfig.SaveAsFile("config.cfg");	
		}		

		SPComponent::Initialize();

		return true;
	}

	bool ConfigManager::ApplyConfig( Config &config )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		ConfigToD3DParameters(config, d3dpp);

		CurrentGame()->GetWindow()->Hide();

		if (CurrentGame()->ResetDevice(d3dpp))
		{
			// Resize the window.
			CurrentGame()->GetWindow()->AdjustMainWindow(
				!config.windowed, config.windowWidth, config.windowHeight);

			currentConfig = config;
			currentConfig.SaveAsFile("config.cfg");
		}	

		CurrentGame()->GetWindow()->Unhide();

		return true;
	}

	SPEngine::Config ConfigManager::GetCurrentConfig()
	{
		return currentConfig;
	}

	bool ConfigManager::ConfigToD3DParameters(Config &config, D3DPRESENT_PARAMETERS& d3dpp)
	{		
		// Set back buffer type.
		d3dpp.BackBufferHeight = config.backBufferHeight;
		d3dpp.BackBufferWidth = config.backBufferWidth;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;

		// Set multi sample type.
		DWORD qualityLevels;

		while(
			config.multisampleType > 0 ||
			D3D_OK != CurrentGame()->GetD3D()->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, 
			D3DFMT_A8R8G8B8, 
			config.windowed, 
			(D3DMULTISAMPLE_TYPE)config.multisampleType,
			&qualityLevels))
		{
			// Cannot perform the multisample type.

			// Reduce the multisample type.
			config.multisampleType--;	
		}

		if (config.multisampleLevel > qualityLevels)
		{
			config.multisampleLevel = qualityLevels;
		}

		d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)config.multisampleType;
		d3dpp.MultiSampleQuality = config.multisampleLevel;

		// Window related.

		d3dpp.hDeviceWindow = NULL;
		d3dpp.Windowed = config.windowed;

		// Other

		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	

		return true;
	}

}

