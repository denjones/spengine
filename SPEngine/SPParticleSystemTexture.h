//////////////////////////////////////////////////////////////////////////
/// @file		SPParticleSystemTexture.h the header file of SPParticleSystemTexture class.
/// @author		Ken.J
/// @version	Beta 0.8
/// @date		2013-2-25
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"
#include "SPParticleSystem3D.h"
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPParticleSystemTexture class to extend SPTexture class, so that 
	/// it can display a particle system.
	//////////////////////////////////////////////////////////////////////
	class SPParticleSystemTexture : public SPTexture
	{
		SPParticleSystem3DPtr	particleSystem;
		SPString				particleSystemName;

	public:
		void SetParticleSystem(SPString setName);
		SPParticleSystem3DPtr GetParticleSystem();

	public:
		SPParticleSystemTexture(SPString setName);
		virtual ~SPParticleSystemTexture(void);

		virtual void Update( float timeDelta );
		virtual void Play();
		virtual void Pause();
		virtual void Stop();

		virtual SPString GetTextureType();

	};

	typedef SPPointer<SPParticleSystemTexture> SPParticleSystemTexturePtr;
}

