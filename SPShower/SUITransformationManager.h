#pragma once
#include "SUITransformation.h"

using namespace SPEngine;

class SUITransformationManager :
	public SPComponent,
	public SPSingleton<SUITransformationManager>
{
	SPWStringMap<SPString> transformationFileNames;

public:
	SUITransformationManager(void);
	~SUITransformationManager(void);

	void Load();
	SUITransformationPtr GetTransformation(SPString name);
	SUITransformationPtr CreateTransformation(SPString path);
};

