#include "StdAfx.h"
#include "SPEffectManager.h"

namespace SPEngine
{
	SPEffectManager::SPEffectManager(void)
	{
	}


	SPEffectManager::~SPEffectManager(void)
	{
		effectCores.Clear();
	}

	bool SPEffectManager::Reload()
	{
		SPWStringMapIterator<SPEffectCorePtr> iter(&effectCores);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Reload();
		}

		return true;
	}

	SPEffectCorePtr SPEffectManager::CreateCore( SPString name, SPString path )
	{
		effectCores.Set(name, new SPEffectCore(path));
		return effectCores[name];
	}

	SPEffectCorePtr SPEffectManager::AddCore( SPString name, SPEffectCorePtr effect )
	{
		effectCores.Set(name, effect);
		return effect;
	}

	SPEffectCorePtr SPEffectManager::GetCore( SPString name )
	{
		if (effectCores.IsSet(name))
		{
			return effectCores[name];
		}

		SPEffectCorePtr core = new SPEffectCore();

		if(core->Load(name))
		{
			effectCores.Set(name, core);
			return core;
		}

		return NULL;
	}

}