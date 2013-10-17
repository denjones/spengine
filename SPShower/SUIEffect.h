#pragma once
#include "SUITransition.h"

using namespace SPEngine;

class SUIEffect :
	public SPEffect,
	public SUITransition	
{
	SPTexturePtr effectTexture;
	float level;

public:
	SUIEffect(void);
	virtual ~SUIEffect(void);

public:
	bool SetEffectTexture(SPTexturePtr setTex);
	bool SetLevel(float setLevel);
	bool Update(float timeDelta);
};

typedef SPPointer<SUIEffect> SUIEffectPtr;