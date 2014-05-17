#include "StdAfx.h"
#include "SUITransformation.h"


SUITransformation::SUITransformation(void) 
{
}

SUITransformation::SUITransformation( SPString path )
{
	Load(path);
}


SUITransformation::~SUITransformation(void)
{
}

void SUITransformation::SetTarget( SPTexturePtr setTarget )
{
	SetTexture(1, setTarget);
}

void SUITransformation::Update( float timeDelta )
{
	if (state == Hidden)
	{
		return;
	}

	SUITransition::Update(timeDelta);

	SetFloat("transitionPosition", GetTransition());

	if (transitionPosition >= 1)
	{
		return;
	}
}
