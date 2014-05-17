#pragma once
#include "SUIMixMode.h"

using namespace SPEngine;

class SUIMixModeManager :
	public SPComponent,
	public SPSingleton<SUIMixModeManager>
{
	SPWStringMap<SPString> mixModeFileNames;

public:
	SUIMixModeManager(void);
	virtual ~SUIMixModeManager(void);

	void Load();
	SUIMixModePtr GetMixMode(SPString name);
	SUIMixModePtr CreateMixMode(SPString path);
};

