//////////////////////////////////////////////////////////////////////////
/// @file		SPShaderManager.h the header file of SPShaderManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPSingleton.h"
#include "SPStringMap.h"
#include "SPEffect.h"
#include "SPComponent.h"
#include "SPPixelShaderCore.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPShaderManager to hold and manage shader.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPShaderManager : 
		public SPComponent,
		public SPSingleton<SPShaderManager>
	{
		typedef SPWStringMap<SPPixelShaderCorePtr> PixelShaderCoreMap;

		PixelShaderCoreMap pixelShaderCores;

	public:
		SPShaderManager(void);
		virtual ~SPShaderManager(void);

		bool Reload();

		SPPixelShaderCorePtr CreateCore(SPString name, SPString path);
		SPPixelShaderCorePtr AddCore(SPString name, SPPixelShaderCorePtr shader);
		SPPixelShaderCorePtr GetCore(SPString name);
	};
}
