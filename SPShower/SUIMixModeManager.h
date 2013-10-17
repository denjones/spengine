#pragma once
#include "SUIMixMode.h"

using namespace SPEngine;

class SUIMixModeManager :
	public SPComponent,
	public SPSingleton<SUIMixModeManager>
{
	SPWStringMap<KString> mixModeFileNames;

public:
	SUIMixModeManager(void);
	virtual ~SUIMixModeManager(void);

	bool Load();
	SUIMixModePtr GetMixMode(SPString name);
	SUIMixModePtr CreateMixMode(SPString path);
};

