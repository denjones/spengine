#include "StdAfx.h"
#include "SUIProperties.h"


SUIProperties::SUIProperties(void)
{
	rectangle = SRectangle(0, 0, 0, 0);
	rotation = 0;
	rotationCenter = D3DXVECTOR2(0, 0);
	backgroundImage = NULL;
	backgroundColor = D3DXCOLOR(0,0,0,0);
	transparency = 1;
	layer = 0;
	backgroundX = 0;
	backgroundY = 0;
	backgroundPosition = Normal;
	backgroundMode = Positioning;
	//padding = D3DXVECTOR4(0,0,0,0);
}


SUIProperties::~SUIProperties(void)
{
}


