//////////////////////////////////////////////////////////////////////////
/// @file		SPLightManager.h the header file of base SPLightManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9math.h>
#include <hash_map>
#include "SPComponent.h"
#include "SPSingleton.h"

using namespace std;

namespace SPEngine
{
	///////////////////////////////////////////////////////////////////////
	/// @brief SPLightManager to produce and manage lights.
	///
	///////////////////////////////////////////////////////////////////////
	class SPLightManager : 
		public SPComponent,
		public SPSingleton<SPLightManager>
	{
		hash_map<int, D3DLIGHT9> lights; ///< Hash map to hold lights.
		int count;	///< Total lights count.

		public:
		SPLightManager();
		virtual ~SPLightManager(void);		

		/// @name Initialize basic light
		/// @{
		static D3DLIGHT9 InitDirectionalLight(
			D3DXVECTOR3 direction, 
			D3DXCOLOR color); 
		static D3DLIGHT9 InitPointLight(
			D3DXVECTOR3 position,
			D3DXCOLOR color); 
		static D3DLIGHT9 InitSpotLight(
			D3DXVECTOR3 position,
			D3DXVECTOR3 direction, 
			D3DXCOLOR color);
		/// @}

		/// @name Component Methods.
		/// @{
		bool Initialize();
		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		bool Load();
		bool Unload();
		/// @}

		/// @name Modification
		/// @{
		bool DisableLighting();
		bool EnableLighting();
		bool AddLight(int index, D3DLIGHT9 &light);
		bool DeleteLight(int index);
		bool ModifyLight(int index, D3DLIGHT9 &light);
		bool Turn(int index);
		bool TurnOn(int index);
		bool TurnOff(int index);
		bool TurnOnAll();
		bool TurnOffAll();
		/// @}

		/// @name Properties
		/// @{
		bool IsLightValid(int index);
		bool IsLightOn(int index);
		D3DLIGHT9& operator[](int index);
		/// @}
	};
}





