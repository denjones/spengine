//////////////////////////////////////////////////////////////////////////
/// @file		SPMaterialManager.h the header file of base SPMaterialManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9math.h>
#include "SPComponent.h"
#include "SPSingleton.h"

namespace SPEngine
{
	///////////////////////////////////////////////////////////////////////
	/// @brief SPMaterialManager to produce materials.
	///
	///////////////////////////////////////////////////////////////////////
	class SPMaterialManager : 
		public SPComponent,
		public SPSingleton<SPMaterialManager>
	{
	public:
		/// @name Static materials
		/// @{
		static const D3DMATERIAL9 WHITE_MTRL; 
		static const D3DMATERIAL9 RED_MTRL; 
		static const D3DMATERIAL9 GREEN_MTRL; 
		static const D3DMATERIAL9 BLUE_MTRL; 
		static const D3DMATERIAL9 YELLOW_MTRL; 
		/// @}

	public:
		SPMaterialManager(void);
		virtual ~SPMaterialManager(void);

		//bool Initialize();
		//bool Load();
		//bool Unload();
		//bool Update(float timeDelta);
		//bool Draw(float timeDelta);

		static D3DMATERIAL9 InitializeMaterial(
			D3DXCOLOR ambient, 
			D3DXCOLOR diffuse, 
			D3DXCOLOR specular, 
			D3DXCOLOR emissive, 
			float power) ;

		bool SetMaterial(D3DMATERIAL9 mtrl);
	};
}


