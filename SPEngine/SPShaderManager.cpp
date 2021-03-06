#include "StdAfx.h"
#include "SPShaderManager.h"

namespace SPEngine
{
	SPShaderManager::SPShaderManager(void)
	{
	}


	SPShaderManager::~SPShaderManager(void)
	{
		pixelShaderCores.Clear();
	}

	SPPixelShaderCorePtr SPShaderManager::AddCore( SPString name, SPPixelShaderCorePtr shader )
	{
		pixelShaderCores.Set(name, shader);
		return shader;
	}

	SPPixelShaderCorePtr SPShaderManager::GetCore( SPString name )
	{
		if (pixelShaderCores.IsSet(name))
		{
			return pixelShaderCores[name];
		}
		
		SPPixelShaderCorePtr core = new SPPixelShaderCore();

		core->Load(name);
		pixelShaderCores.Set(name, core);
		return core;
	}

	SPPixelShaderCorePtr SPShaderManager::CreateCore( SPString name, SPString path )
	{
		pixelShaderCores.Set(name, new SPPixelShaderCore(path));
		return pixelShaderCores[name];
	}

	void SPShaderManager::Reload()
	{
		SPWStringMapIterator<SPPixelShaderCorePtr> iter(&pixelShaderCores);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->Reload();
		}
	}


}