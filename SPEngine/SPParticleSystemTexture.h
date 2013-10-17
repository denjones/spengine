//////////////////////////////////////////////////////////////////////////
/// @file		SPParticleSystemTexture.h the header file of SPParticleSystemTexture class.
/// @author		Ken.J
/// @version	Beta 0.8
/// @date		2013-2-25
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPUpdatableTexture.h"
#include "SPParticleSystem3D.h"
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPParticleSystemTexture class to extend SPTexture class, so that 
	/// it can display a particle system.
	//////////////////////////////////////////////////////////////////////
	class SPParticleSystemTexture : public SPUpdatableTexture
	{
		SPParticleSystem3DPtr	particleSystem;
		SPString				particleSystemName;

	public:
		void SetParticleSystem(SPString setName);

	public:
		SPParticleSystemTexture(SPString setName);
		virtual ~SPParticleSystemTexture(void);

		virtual bool Update( float timeDelta );

		virtual bool Play();

		virtual bool Pause();

		virtual bool Stop();

	};

	typedef SPPointer<SPParticleSystemTexture> SPParticleSystemTexturePtr;
}

