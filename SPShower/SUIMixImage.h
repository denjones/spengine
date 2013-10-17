#pragma once
#include "SUIComponent.h"
#include "SUITransformation.h"
#include "SUIBlankComponent.h"
#include "SUIMixMode.h"
#include "SPEngine.h"

using namespace SPEngine;

class SUIMixImage
{
public:
	SPTexturePtr	Image;
	SUIMixModePtr	MixMode;
	float			Layer;
	VariableMap		properties;

public:
	SUIMixImage(SPTexturePtr setImage, SUIMixModePtr setMixMode, float setLayer);
	SUIMixImage(void);
	virtual ~SUIMixImage(void);

	bool SetProperties(VariableMap args);
	SPString PropertiesToString();

	SPString SaveAsString();
	bool LoadFromString(SPString stringStream);
};

