#include "StdAfx.h"
#include "SUIMixMode.h"


SUIMixMode::SUIMixMode(void) : SPEffect()
{
}

SUIMixMode::SUIMixMode( SPString path )
{
	Load(path);
}


SUIMixMode::~SUIMixMode(void)
{
}

bool SUIMixMode::SetTarget( SPTexturePtr setTarget )
{
	SetTexture(1, setTarget);
	
	return true;
}
