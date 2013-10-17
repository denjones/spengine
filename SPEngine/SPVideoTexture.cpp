#include "StdAfx.h"
#include "SPVideoTexture.h"
#include "SPVideoManager.h"

namespace SPEngine
{
	SPVideoTexture::SPVideoTexture(void)
	{
	}

	SPVideoTexture::SPVideoTexture( SPString setName )
	{
		SetVideo(setName);
	}

	SPVideoTexture::~SPVideoTexture(void)
	{
		if (video)
		{
			video->SetTexture(NULL);
			video = NULL;
		}		
	}

	bool SPVideoTexture::Update( float timeDelta )
	{
		if (!video)
		{
			return false;
		}

		//video->UpdateFrame();

		return true;
	}

	void SPVideoTexture::SetVideo( SPString setName )
	{
		videoName = setName;
		video = SPVideoManager::GetSingleton().GetVideo(setName);
		video->SetTexture(this);
	}

	bool SPVideoTexture::Reload()
	{
		video = SPVideoManager::GetSingleton().GetVideo(videoName);
		video->SetTexture(this);

		return true;
	}

	bool SPVideoTexture::Unload()
	{
		video->SetTexture(NULL);
		video = NULL;		

		return SPUpdatableTexture::Unload();
	}

	bool SPVideoTexture::Play()
	{
		if (!video)
		{
			return false;
		}

		return SUCCEEDED(video->Play());
	}

	bool SPVideoTexture::Pause()
	{
		if (!video)
		{
			return false;
		}

		return SUCCEEDED(video->Pause());
	}

	bool SPVideoTexture::Stop()
	{
		if (!video)
		{
			return false;
		}

		return SUCCEEDED(video->Stop());
	}

}

