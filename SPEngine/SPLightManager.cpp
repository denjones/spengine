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

void SPLightManager::Update(float timeDelta)
{

}

void SPLightManager::Draw(float timeDelta)
{

}

void SPLightManager::Load()
{

}

void SPLightManager::Unload()
{

}

void SPLightManager::Initialize()
{
	lights.clear();
	count = 0;
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

void SPLightManager::EnableLighting()
{
	SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, true); 
}

void SPLightManager::DisableLighting()
{
	SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, false); 
}

void SPLightManager::AddLight( int index, D3DLIGHT9 &light )
{
	if (!IsLightValid(index))
	{
		lights[index] = light;
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, &light);
		return;
	}

	return;
}

void SPLightManager::ModifyLight( int index, D3DLIGHT9 &light )
{
	if (IsLightValid(index))
	{
		lights[index] = light;
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, &light);
	}
}

void SPLightManager::DeleteLight( int index )
{
	if (IsLightValid(index))
	{
		lights.erase(index);
		SPDevice::GetSingleton()->GetD3DDevice()->SetLight(index, NULL);
	}
}

void SPLightManager::TurnOn( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, true);
	}
}

void SPLightManager::TurnOnAll()
{
	hash_map<int, D3DLIGHT9>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(iter->first, true);
	}
}

void SPLightManager::TurnOff( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, false);
	}
}

void SPLightManager::TurnOffAll()
{
	hash_map<int, D3DLIGHT9>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(iter->first, false);
	}
}

void SPLightManager::Turn( int index )
{
	if (IsLightValid(index))
	{
		SPDevice::GetSingleton()->GetD3DDevice()->LightEnable(index, !IsLightOn(index));
	}
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
