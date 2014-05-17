#pragma once
#include "SUITransition.h"

using namespace SPEngine;

class SUITransformation : 
	public SPEffect,
	public SUITransition	
{
public:
	void SetTarget(SPTexturePtr setTarget);

public:
	SUITransformation(SPString path);
	SUITransformation(void);
	~SUITransformation(void);

	void Update(float timeDelta);
};

typedef SPPointer<SUITransformation> SUITransformationPtr;

