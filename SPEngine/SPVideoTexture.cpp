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

	void SPVideoTexture::Update( float timeDelta )
	{
		if (!video)
		{
			return;
		}

		//video->UpdateFrame();

		return;
	}

	void SPVideoTexture::SetVideo( SPString setName )
	{
		videoName = setName;
		video = SPVideoManager::GetSingleton()->GetVideo(setName);
		video->SetTexture(this);
	}

	void SPVideoTexture::Reload()
	{
		video = SPVideoManager::GetSingleton()->GetVideo(videoName);
		video->SetTexture(this);
	}

	void SPVideoTexture::Unload()
	{
		video->SetTexture(NULL);
		video = NULL;		
		SPTexture::Unload();
	}

	void SPVideoTexture::Play()
	{
		if (!video)
		{
			return;
		}

		video->Play();
	}

	void SPVideoTexture::Pause()
	{
		if (!video)
		{
			return;
		}

		video->Pause();
	}

	void SPVideoTexture::Stop()
	{
		if (!video)
		{
			return;
		}

		video->Stop();
	}

	SPString SPVideoTexture::GetTextureType()
	{
		return L"VideoTexture";
	}

	SPEngine::SPVideoPtr SPVideoTexture::GetVideo()
	{
		return video;
	}

}

