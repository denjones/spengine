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

bool SUITransformation::SetTarget( SPTexturePtr setTarget )
{
	SetTexture(1, setTarget);

	return true;
}

bool SUITransformation::Update( float timeDelta )
{
	if (state == Hidden)
	{
		return true;
	}

	SUITransition::Update(timeDelta);

	SetFloat("transitionPosition", GetTransition());

	if (transitionPosition >= 1)
	{
		return false;
	}

	return true;
}
