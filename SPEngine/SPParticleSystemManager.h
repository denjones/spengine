#pragma once
#include "SPComponent.h"
#include "SPParticleSystem2D.h"
#include "SPParticleSystem3D.h"
#include "SPSingleton.h"
#include "SPStringMap.h"
#include <vector>

using namespace std;

namespace SPEngine
{
	class SPParticleSystemManager :
		public SPComponent,	
		public SPSingleton<SPParticleSystemManager>
	{
	protected:
		SPWStringMap<SPParticleSystem3DPtr> particleSystemMap;
	public:
		SPParticleSystemManager();
		virtual ~SPParticleSystemManager();

		bool Load();
		bool Unload();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();

		bool AllSystemPause();

		//Particle System Management
		bool AddParticleSystem(SPString name, SPParticleSystem3DPtr particleSys);
		bool CreateParticleSystem(SPString name,
			BoundingBox2D positionBox,
			BoundingBox2D boundBox,
			float minVelocity,
			float maxVelocity,
			float minDegree,
			float maxDegree,
			float particleAge,
			D3DXCOLOR particleColor,
			float particleRate,
			float particleSystemAge,
			SPTexturePtr texPtr,
			int numParticle,
			D3DXVECTOR2 systemAcceleration,
			//			float particleSize = 0,
			bool if3D,
			float minStartAngle,
			float maxStartAngle,
			float degreePerSecondMin,
			float degreePerSecondMax,
			D3DXVECTOR3 rotateAxis,
			bool ifSnowRotate,
			float fadeOutT,
			float minScale,
			float maxScale,
			float scaleDeltaMin,
			float scaleDeltaMax);
		bool DestroyParticleSystem(SPString name);

		SPParticleSystem3DPtr GetParticleSystem(SPString name);
	};
}

