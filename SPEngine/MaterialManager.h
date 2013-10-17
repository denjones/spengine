#pragma once
#include <d3dx9math.h>
#include "SPComponent.h"

namespace SPEngine
{
	class SPGame;

	class MaterialManager : public SPComponent
	{
	public:
		// Material
		static const D3DMATERIAL9 WHITE_MTRL; 
		static const D3DMATERIAL9 RED_MTRL; 
		static const D3DMATERIAL9 GREEN_MTRL; 
		static const D3DMATERIAL9 BLUE_MTRL; 
		static const D3DMATERIAL9 YELLOW_MTRL; 

	public:
		MaterialManager(void);
		MaterialManager(SPGame* game);
		~MaterialManager(void);

		bool Initialize();
		bool Load();
		bool Unload();
		bool Update(float timeDelta);
		bool Draw(float timeDelta);

		static D3DMATERIAL9 InitializeMaterial(
			D3DXCOLOR ambient, 
			D3DXCOLOR diffuse, 
			D3DXCOLOR specular, 
			D3DXCOLOR emissive, 
			float power) ;

		bool SetMaterial(D3DMATERIAL9 mtrl);
	};
}


