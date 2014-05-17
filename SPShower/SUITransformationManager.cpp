#include "StdAfx.h"
#include "SUITransformationManager.h"


SUITransformationManager::SUITransformationManager(void)
{
}


SUITransformationManager::~SUITransformationManager(void)
{
}

void SUITransformationManager::Load()
{
	transformationFileNames.Set(L"Fade", L"trans\\trans_fade.fxo");
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

		transformation->Load(name);
		return transformation;
	}

	return NULL;
}

SUITransformationPtr SUITransformationManager::CreateTransformation( SPString path )
{
	SUITransformationPtr transformation = new SUITransformation();
	transformation->Load(path);
	return transformation;
}
