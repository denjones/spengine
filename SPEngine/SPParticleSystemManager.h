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
		bool Reload();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();

		bool AllSystemPause();

		//Particle System Management
		bool AddParticleSystem(SPString name, SPParticleSystem3DPtr particleSys);
		bool CreateParticleSystem(SPString name,
			BoundingBox2D positionBox = BoundingBox2D(),
			BoundingBox2D boundBox = BoundingBox2D(),
			float minVelocity = 0,
			float maxVelocity = 0,
			float minDegree = 0,
			float maxDegree = 0,
			float particleAge = 0,
			D3DXCOLOR particleColor = SPColor::White,
			float particleRate = 0,
			float particleSystemAge = 100,
			SPTexturePtr texPtr = NULL,
			int numParticle = 5,
			D3DXVECTOR2 systemAcceleration = D3DXVECTOR2(0, 0),
			//			float particleSize = 0,
			bool if3D = false,
			float minStartAngle = 0,
			float maxStartAngle = 0,
			float degreePerSecondMin = 0,
			float degreePerSecondMax = 0,
			D3DXVECTOR3 rotateAxis = D3DXVECTOR3(0, 1, 0),
			bool ifSnowRotate = false,
			float fadeOutT = 0,
			float minScale = 1,
			float maxScale = 1,
			float scaleDeltaMin = 0,
			float scaleDeltaMax = 0);
		bool DestroyParticleSystem(SPString name);

		SPParticleSystem3DPtr GetParticleSystem(SPString name);
	};
}

