#pragma once
#include "SUITransition.h"

using namespace SPEngine;

class SUITransformation : 
	public SPEffect,
	public SUITransition	
{
public:
	bool SetTarget(SPTexturePtr setTarget);

public:
	SUITransformation(SPString path);
	SUITransformation(void);
	~SUITransformation(void);

	bool Update(float timeDelta);
};

typedef SPPointer<SUITransformation> SUITransformationPtr;

