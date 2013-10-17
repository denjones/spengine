#pragma once
#include "SPComponent.h"
#include "SPSingleton.h"
#include "SPStringMap.h"
#include "SPEffectCore.h"

namespace SPEngine
{
	class SPEffectManager :
		public SPComponent,
		public SPSingleton<SPEffectManager>
	{
		typedef SPWStringMap<SPEffectCorePtr> EffectCoreMap;

		EffectCoreMap effectCores;

	public:
		SPEffectManager(void);
		virtual ~SPEffectManager(void);

		bool Reload();

		SPEffectCorePtr CreateCore(SPString name, SPString path);
		SPEffectCorePtr AddCore(SPString name, SPEffectCorePtr effect);
		SPEffectCorePtr GetCore(SPString name);
	};
}
