#include "StdAfx.h"
#include "SUITransformationManager.h"


SUITransformationManager::SUITransformationManager(void)
{
}


SUITransformationManager::~SUITransformationManager(void)
{
}

bool SUITransformationManager::Load()
{
	transformationFileNames.Set(L"Fade", L"trans\\trans_fade.fxo");

	return true;
}

SUITransformationPtr SUITransformationManager::GetTransformation( SPString name )
{
	if (transformationFileNames.IsSet(name))
	{
		return new SUITransformation(transformationFileNames[name]);
	}
	else
	{
		SUITransformationPtr transformation = new SUITransformation();

		if (transformation->Load(name))
		{
			return transformation;
		}
	}

	return NULL;
}

SUITransformationPtr SUITransformationManager::CreateTransformation( SPString path )
{
	SUITransformationPtr transformation = new SUITransformation();

	if (transformation->Load(path))
	{
		return transformation;
	}

	return NULL;
}
