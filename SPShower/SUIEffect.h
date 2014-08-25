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
	SPTexturePtr GetEffectTexture();
	void SetLevel(float setLevel);
	float GetLevel();
	void Update(float timeDelta);
};

typedef SPPointer<SUIEffect> SUIEffectPtr;