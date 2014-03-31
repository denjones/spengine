#include "StdAfx.h"
#include "SPParticleSystemTexture.h"
#include "SPParticleSystemManager.h"

namespace SPEngine
{
	SPParticleSystemTexture::SPParticleSystemTexture(SPString setName)
	{
		SetParticleSystem(setName);
	}

	SPParticleSystemTexture::~SPParticleSystemTexture(void)
	{
	}

	bool SPParticleSystemTexture::Update( float timeDelta )
	{
		return false;
	}

	bool SPParticleSystemTexture::Play()
	{
		if (!particleSystem)
		{
			return false;
		}

		particleSystem->Play();

		return true;
	}

	bool SPParticleSystemTexture::Pause()
	{
		if (!particleSystem)
		{
			return false;
		}

		particleSystem->Pause();

		return true;
	}

	bool SPParticleSystemTexture::Stop()
	{
		if (!particleSystem)
		{
			return false;
		}

		particleSystem->Stop();

		return true;
	}

	void SPParticleSystemTexture::SetParticleSystem( SPString setName )
	{
		particleSystemName = setName;
		SPParticleSystem3DPtr ptr = SPParticleSystemManager::GetSingleton()->GetParticleSystem(setName);
		if (ptr)
		{
			particleSystem = ptr;
			particleSystem->SetRenderTarget(this);
			backgroundColor = ptr->GetBackgroundColor();
		}
	}

}