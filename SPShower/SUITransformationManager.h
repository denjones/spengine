#pragma once
#include "SUITransformation.h"

using namespace SPEngine;

class SUITransformationManager :
	public SPComponent,
	public SPSingleton<SUITransformationManager>
{
	SPWStringMap<KString> transformationFileNames;

public:
	SUITransformationManager(void);
	~SUITransformationManager(void);

	bool Load();
	SUITransformationPtr GetTransformation(SPString name);
	SUITransformationPtr CreateTransformation(SPString path);
};

