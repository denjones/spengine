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
		float scaleDeltaMax = 0)
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