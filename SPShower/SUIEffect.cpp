#include "StdAfx.h"
#include "SUIEffect.h"


SUIEffect::SUIEffect(void) : 
	SPEffect(),
	SUITransition()
{
	level = 0;
	transitionPosition = 0;
}

SUIEffect::~SUIEffect(void)
{
}

bool SUIEffect::Update( float timeDelta )
{
	if (state == Hidden)
	{
		return true;
	}

	SUITransition::Update(timeDelta);

	SetFloat("transitionPosition", GetTransition());
	SetFloat("level", level);
	SetTexture(1, effectTexture);

	if (transitionPosition >= 1)
	{
		return false;
	}

	return true;
}

bool SUIEffect::SetEffectTexture( SPTexturePtr setTex )
{
	effectTexture = setTex;

	return true;
}

bool SUIEffect::SetLevel( float setLevel )
{
	level = setLevel;

	SetFloat("level", level);

	return true;
}
