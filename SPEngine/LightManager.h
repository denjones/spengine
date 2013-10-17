#pragma once
#include <d3dx9math.h>
#include <hash_map>
#include "SPComponent.h"

using namespace std;

namespace SPEngine
{
	class SPGame;

	class LightManager : public SPComponent
	{
		hash_map<int, D3DLIGHT9*> lights;
		int count;

		public:
		LightManager();
		LightManager(SPGame* game);
		~LightManager(void);

		bool Initialize();

		// Initialize basic light
		static D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3 direction, D3DXCOLOR color); 
		static D3DLIGHT9 InitPointLight(D3DXVECTOR3 position, D3DXCOLOR color); 
		static D3DLIGHT9 InitSpotLight(D3DXVECTOR3 position, D3DXVECTOR3 direction, 
			D3DXCOLOR color);

		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		bool Load();
		bool Unload();

		bool DisableLighting();
		bool EnableLighting();
		bool AddLight(int index, D3DLIGHT9 &light);
		bool DeleteLight(int index);
		bool ModifyLight(int index, D3DLIGHT9 &light);
		bool IsLightValid(int index);
		bool IsLightOn(int index);
		bool Turn(int index);
		bool TurnOn(int index);
		bool TurnOff(int index);
		bool TurnOnAll();
		bool TurnOffAll();
		D3DLIGHT9& operator[](int index);
	};
}





