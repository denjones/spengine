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

	void SPParticleSystemTexture::Update( float timeDelta )
	{
	}

	void SPParticleSystemTexture::Play()
	{
		if (!particleSystem)
		{
			return;
		}

		particleSystem->Play();
	}

	void SPParticleSystemTexture::Pause()
	{
		if (!particleSystem)
		{
			return;
		}

		particleSystem->Pause();
	}

	void SPParticleSystemTexture::Stop()
	{
		if (!particleSystem)
		{
			return;
		}

		particleSystem->Stop();
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

	SPString SPParticleSystemTexture::GetTextureType()
	{
		return L"ParticleSystemTexture";
	}

	SPEngine::SPParticleSystem3DPtr SPParticleSystemTexture::GetParticleSystem()
	{
		return particleSystem;
	}

}