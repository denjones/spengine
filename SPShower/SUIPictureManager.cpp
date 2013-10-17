#include "StdAfx.h"
#include "SUIPictureManager.h"
#include "SScriptHelper.h"
#include "SScriptFunction.h"
#include "SSFPicture.h"
#include "SSFMixPicture.h"


SUIPictureManager::SUIPictureManager(void)
{
}


SUIPictureManager::~SUIPictureManager(void)
{
}

SUIPictureListPtr SUIPictureManager::GetPicture( SPString name )
{
	if (pictures.IsSet(name))
	{
		return pictures[name];
	}

	return NULL;
}

bool SUIPictureManager::SetPicture( SPString setName, SUIPictureListPtr setPicture )
{
	pictures.Set(setName, setPicture);

	return true;
}

bool SUIPictureManager::IsPictureVaild( SPString name )
{
	if (pictures.IsSet(name))
	{
		if (pictures[name])
		{
			return true;
		}
	}

	return false;
}

bool SUIPictureManager::SetCurrentPicture( SUIPictureListPtr setPicture )
{
	currentPicture = setPicture;

	return true;
}

SUIPictureListPtr SUIPictureManager::GetCurrentPicture()
{
	return currentPicture;
}

bool SUIPictureManager::LoadFromString( SPString stringStream )
{
	SPString picturesString = SPStringHelper::XMLExcludeFrom(stringStream, L"Pictures");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Pictures");
	
	while(picturesString.size() > 0)
	{
		SPString pictureString = SPStringHelper::XMLExcludeFrom(picturesString, L"SUIPL");
		picturesString = SPStringHelper::XMLRemoveFirst(picturesString, L"SUIPL");

		SPString propertiesString = SPStringHelper::XMLExcludeFrom(pictureString, L"Properties");
		pictureString = SPStringHelper::XMLRemoveFirst(pictureString, L"Properties");

		VariableMap properties = SScriptHelper::StringToVariables(propertiesString);

		SScriptFunctionPtr buildPicture =  new SSFPicture();
		buildPicture->Function(properties, false);

		SPString mixImagesString = SPStringHelper::XMLExcludeFrom(pictureString, L"MPS");
		pictureString = SPStringHelper::XMLRemoveFirst(pictureString, L"MPS");

		SScriptFunctionPtr mixPicture = new SSFMixPicture();

		while(mixImagesString.size() > 0)
		{
			SPString mixImageString = SPStringHelper::XMLExcludeFrom(mixImagesString, L"SUIMI");
			mixImagesString = SPStringHelper::XMLRemoveFirst(mixImagesString, L"SUIMI");

			VariableMap miProperties = SScriptHelper::StringToVariables(mixImageString);
			mixPicture->Function(miProperties, false);
		}
	}

	SPString currentPictureString = SPStringHelper::XMLExcludeFrom(stringStream, L"CurrentPictureName");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"CurrentPictureName");

	currentPicture = GetPicture(currentPictureString);

	return true;
}

SPString SUIPictureManager::SaveAsString()
{
	SPString result;	
	
	result += L"<Pictures>";

	SPWStringMapIterator<SUIPictureListPtr> iter(&pictures);

	for(iter.First(); !iter.IsDone(); iter.Next())
	{
		result += iter.CurrentItem()->SaveAsString();
	}

	result += L"</Pictures>";

	if (currentPicture)
	{
		result += SPStringHelper::XMLSurroundWith(currentPicture->GetName(),L"CurrentPictureName");
	}

	result = SPStringHelper::XMLSurroundWith(result, L"SUIPictureManager");

	return result;
}
