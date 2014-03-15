#include "StdAfx.h"
#include "SUIMixImage.h"


SUIMixImage::SUIMixImage(void)
{
	Image = NULL;
	MixMode = NULL;
}

SUIMixImage::SUIMixImage( SPTexturePtr setImage, SUIMixModePtr setMixMode, float setLayer )
{
	Image = setImage;
	MixMode = setMixMode;
	Layer = setLayer;
}


SUIMixImage::~SUIMixImage(void)
{
}

bool SUIMixImage::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIMixImage::SaveAsString()
{
	//SPString result;

	//result += PropertiesToString();

	//result = SPStringHelper::XMLSurroundWith(result, L"SUIMI");

	//return result;

	return L"";
}