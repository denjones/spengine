#pragma once
#include "Config.h"
#include "SPComponent.h"

namespace SPEngine
{
	class ConfigManager : public SPComponent
	{
		Config currentConfig;

	public:
		ConfigManager(void);
		~ConfigManager(void);

		bool Initialize();
		bool ApplyConfig(Config &config);
		Config GetCurrentConfig();
		bool ConfigToD3DParameters(Config &config, D3DPRESENT_PARAMETERS& d3dpp);
	};
}


