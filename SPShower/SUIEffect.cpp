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

void SUIEffect::Update( float timeDelta )
{
	if (state == Hidden)
	{
		return;
	}

	SUITransition::Update(timeDelta);

	SetFloat("transitionPosition", GetTransition());
	SetFloat("level", level);
	SetTexture(1, effectTexture);
}

void SUIEffect::SetEffectTexture( SPTexturePtr setTex )
{
	effectTexture = setTex;
}

void SUIEffect::SetLevel( float setLevel )
{
	level = setLevel;
	SetFloat("level", level);
}
