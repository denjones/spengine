#pragma once
#include "StdAfx.h"
#include "SPParticleSystemManager.h"

using namespace std;

namespace SPEngine
{
	SPParticleSystemManager::SPParticleSystemManager()
	{
		Load();
	}

	SPParticleSystemManager::~SPParticleSystemManager()
	{
		particleSystemMap.Clear();
		Unload();
	}

	bool SPParticleSystemManager::Initialize()
	{
		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Reset();
		}
		SPComponent::Initialize();
		return true;
	}

	bool SPParticleSystemManager::Load()
	{
		SPComponent::Load();
		return true;
	}

	bool SPParticleSystemManager::Unload()
	{
		SPComponent::Unload();

		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			SPParticleSystem3DPtr particleSystem = iter.CurrentItem();

			particleSystem->Unload();
		}
		return true;

		return true;
	}

	bool SPParticleSystemManager::Reload()
	{
		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			SPParticleSystem3DPtr particleSystem = iter.CurrentItem();

			particleSystem->Reload();
		}
		return true;
	}

	bool SPParticleSystemManager::Update(float timeElapsed)
	{
		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			SPParticleSystem3DPtr particleSystem = iter.CurrentItem();

			particleSystem->Update(timeElapsed);
		}
		return true;
	}

	bool SPParticleSystemManager::Draw(float timeElapsed)
	{
		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Draw(timeElapsed);
		}
		return true;
	}

	bool SPParticleSystemManager::AddParticleSystem(SPString name, SPParticleSystem3DPtr particleSys)
	{
		particleSystemMap.Set(name, particleSys);
		return true;
	}

	bool SPParticleSystemManager::DestroyParticleSystem(SPString name)
	{
		particleSystemMap.Remove(name);
		return true;
	}

	bool SPParticleSystemManager::AllSystemPause()
	{
		SPWStringMapIterator<SPParticleSystem3DPtr> iter (&particleSystemMap);
		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Pause();
		}
		return true;
	}

	bool SPParticleSystemManager::CreateParticleSystem(SPString name,
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
		float scaleDeltaMax)
	{
		SPParticleSystem3DPtr parSys;
		parSys = new SPParticleSystem3D;
		parSys->LoadWith2D(positionBox, boundBox, minVelocity, maxVelocity, minDegree, maxDegree,
			particleAge, particleColor, particleRate, particleSystemAge, texPtr, numParticle,
			systemAcceleration , if3D, minStartAngle, maxStartAngle,
			degreePerSecondMin, degreePerSecondMax, rotateAxis,
			ifSnowRotate, fadeOutT, minScale, maxScale, scaleDeltaMin, scaleDeltaMax);
		AddParticleSystem(name, parSys);
		return true;
	}

	SPParticleSystem3DPtr SPParticleSystemManager::GetParticleSystem( SPString name )
	{
		if (particleSystemMap.IsSet(name))
		{
			return particleSystemMap.Get(name);
		}

		return NULL;
	}
}