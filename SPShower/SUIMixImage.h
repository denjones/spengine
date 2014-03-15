#pragma once
#include "SUIComponent.h"
#include "SUITransformation.h"
#include "SUIMixMode.h"
#include "SPEngine.h"

using namespace SPEngine;

class SUIMixImage
{
public:
	SPTexturePtr	Image;
	SUIMixModePtr	MixMode;
	float			Layer;

public:
	SUIMixImage(SPTexturePtr setImage, SUIMixModePtr setMixMode, float setLayer);
	SUIMixImage(void);
	virtual ~SUIMixImage(void);

	SPString SaveAsString();
	bool LoadFromString(SPString stringStream);
};

