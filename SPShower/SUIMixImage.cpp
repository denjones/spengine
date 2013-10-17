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
	SPString result;

	result += PropertiesToString();

	result = SPStringHelper::XMLSurroundWith(result, L"SUIMI");

	return result;
}

bool SUIMixImage::SetProperties( VariableMap args )
{
	for(VariableMap::iterator iter = args.begin();
		iter != args.end(); iter++)
	{
		properties[iter->first] = iter->second;
	}

	return true;
}

SPString SUIMixImage::PropertiesToString()
{
	SPString result = L"";

	VariableMap::iterator iter = properties.begin();

	while(iter != properties.end())
	{
		if (iter->first.size() < 5 
			|| iter->first.find(L"delta") == SPString::npos)
		{
			result += L"<P>";

			result += L"<N>";
			result += iter->first;
			result += L"</N>";

			result += L"<T>";
			result += SPStringHelper::ToWString((int)iter->second.type);
			result += L"</T>";

			result += L"<V>";
			result += iter->second.value;
			result += L"</V>";

			result += L"</P>";
		}

		iter++;
	}

	return result;
}
