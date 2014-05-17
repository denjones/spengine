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
	void SetEffectTexture(SPTexturePtr setTex);
	void SetLevel(float setLevel);
	void Update(float timeDelta);
};

typedef SPPointer<SUIEffect> SUIEffectPtr;