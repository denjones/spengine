#include "StdAfx.h"
#include "SPLightManager.h"
#include "SPGame.h"
#include "SPDevice.h"

using namespace SPEngine;

SPLightManager::SPLightManager(void)
{

}

SPLightManager::~SPLightManager(void)
{
	Unload();
}

bool SPLightManager::Update(float timeDelta)
{
	return true;
}

bool SPLightManager::Draw(float timeDelta)
{
	return true;
}

bool SPLightManager::Load()
{
	return true;
}

bool SPLightManager::Unload()
{
	return true;
}

bool SPLightManager::Initialize()
{
	lights.clear();
	count = 0;
	return true;
}

// Light
D3DLIGHT9 SPLightManager::InitDirectionalLight(
	D3DXVECTOR3 direction, D3DXCOLOR color) 
{ 
	D3DLIGHT9 light; 
	ZeroMemory(&light, sizeof(light)); 
	light.Type = D3DLIGHT_DIRECTIONAL; 
	light.Ambient = color * 0.4f; 
	light.Diffuse = color; 
	light.Specular = color * 0.6f; 
	light.Direction = direction; 
	return light; 
} 

D3DLIGHT9 SPLightManager::InitPointLight( 
	D3DXVECTOR3 position, D3DXCOLOR color )
{
	D3DLIGHT9 light; 
	ZeroMemory(&light, sizeof(light)); 
	light.Type = D3DLIGHT_POINT; 
	light.Ambient = color * 0.4f; 
	light.Diffuse = color; 
	light.Specular = color * 0.6f; 
	light.Position = position; 
	light.Range = 300;
	light.Attenuation0 = 1;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;
	return light; 
}

D3DLIGHT9 SPLightManager::InitSpotLight( 
	D3DXVECTOR3 position, D3DXVECTOR3 direction,	D3DXCOLOR color )
{
	D3DLIGHT9 light; 
	ZeroMemory(&light, sizeof(light)); 
	light.Type = D3DLIGHT_POINT; 
	light.Ambient = color * 0.4f; 
	light.Diffuse = color; 
	light.Specular = color * 0.6f; 
	light.Position = position; 
	light.Direction = direction;
	light.Range = 300;
	light.Attenuation0 = 2;
	light.Attenuation1 = 0;
	light.Attenuation2 = 0;
	light.Phi = 3.14f * 0.5f;
	light.Theta = 3.14f * 0.2f;
	light.Falloff = 1.0f;
	return light; 
}

bool SPLightManager::EnableLighting()
{
	SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, true); 

	return true;
}

bool SPLightManager::DisableLighting()
{
	SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, false); 

	return true;
}

bool SPLightManager::AddLight( int index, D3DLIGHT9 &light )
{
	if (!IsLightValid(index))
	{
		lights[index] = light;
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, &light);
		return true;
	}

	return false;
}

bool SPLightManager::ModifyLight( int index, D3DLIGHT9 &light )
{
	if (IsLightValid(index))
	{
		lights[index] = light;
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, &light);
		return true;
	}

	return false;
}

bool SPLightManager::DeleteLight( int index )
{
	if (IsLightValid(index))
	{
		lights.erase(index);
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, NULL);
		return true;
	}

	return false;
}

bool SPLightManager::TurnOn( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, true);
		return true;
	}

	return false;
}

bool SPLightManager::TurnOnAll()
{
	hash_map<int, D3DLIGHT9>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(iter->first, true);
	}

	return true;
}

bool SPLightManager::TurnOff( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, false);
		return true;
	}

	return false;
}

bool SPLightManager::TurnOffAll()
{
	hash_map<int, D3DLIGHT9>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(iter->first, false);
	}

	return true;
}

bool SPLightManager::Turn( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, !IsLightOn(index));
		return true;
	}

	return false;
}

bool SPLightManager::IsLightValid( int index )
{
	if (lights.find(index) == lights.end(index))
	{
		return false;
	}

	return true;
}

bool SPLightManager::IsLightOn( int index )
{
	if (IsLightValid(index))
	{
		BOOL isOn = FALSE;
		SPDevice::GetSingleton()->GetD3DDevice()->GetLightEnable(index, &isOn);
		if (isOn)
		{
			return true;
		}		
	}

	return false;
}
