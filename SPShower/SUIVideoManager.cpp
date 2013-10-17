#include "StdAfx.h"
#include "SUIVideoManager.h"


SUIVideoManager::SUIVideoManager(void)
{
}


SUIVideoManager::~SUIVideoManager(void)
{
}

SPEngine::SPVideoPtr SUIVideoManager::GetVideo( SPString name )
{
	if (videoPaths.IsSet(name))
	{
		return SPVideoManager::GetSingleton().GetVideo(videoPaths[name]);
	}

	return NULL;
}

bool SUIVideoManager::SetVideoPath( SPString name, SPString path )
{
	videoPaths.Set(name, path);
	return true;
}

SPEngine::SPVideoTexturePtr SUIVideoManager::GetVideoTexture( SPString name )
{
	if (videoPaths.IsSet(name))
	{
		return SPTextureManager::GetSingleton().GetVideo(videoPaths[name]);
	}

	return NULL;
}
