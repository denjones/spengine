#include "StdAfx.h"
#include "LightManager.h"
#include "SPGame.h"

using namespace SPEngine;

LightManager::LightManager(SPGame* game)
{
	Register(game);
}

LightManager::LightManager(void)
{
	currentGame = NULL;
}

LightManager::~LightManager(void)
{
	Unload();
}

bool LightManager::Update(float timeDelta)
{
	return true;
}

bool LightManager::Draw(float timeDelta)
{
	return true;
}

bool LightManager::Load()
{
	return true;
}

bool LightManager::Unload()
{
	return true;
}

bool LightManager::Initialize()
{
	lights.clear();
	count = 0;
	return true;
}

// Light
D3DLIGHT9 LightManager::InitDirectionalLight(
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

D3DLIGHT9 LightManager::InitPointLight( 
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

D3DLIGHT9 LightManager::InitSpotLight( 
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

bool LightManager::EnableLighting()
{
	currentGame->GetDevice()->SetRenderState(D3DRS_LIGHTING, true); 

	return true;
}

bool LightManager::DisableLighting()
{
	currentGame->GetDevice()->SetRenderState(D3DRS_LIGHTING, false); 

	return true;
}

bool LightManager::AddLight( int index, D3DLIGHT9 &light )
{
	if (!IsLightValid(index))
	{
		lights[index] = &light;
		currentGame->GetDevice()->SetLight(index, &light);
		return true;
	}

	return false;
}

bool LightManager::ModifyLight( int index, D3DLIGHT9 &light )
{
	if (IsLightValid(index))
	{
		lights[index] = &light;
		currentGame->GetDevice()->SetLight(index, &light);
		return true;
	}

	return false;
}

bool LightManager::DeleteLight( int index )
{
	if (IsLightValid(index))
	{
		lights.erase(index);
		currentGame->GetDevice()->SetLight(index, NULL);
		return true;
	}

	return false;
}

bool LightManager::TurnOn( int index )
{
	if (IsLightValid(index))
	{
		currentGame->GetDevice()->LightEnable(index, true);
		return true;
	}

	return false;
}

bool LightManager::TurnOnAll()
{
	hash_map<int, D3DLIGHT9*>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		currentGame->GetDevice()->LightEnable(iter->first, true);
	}

	return true;
}

bool LightManager::TurnOff( int index )
{
	if (IsLightValid(index))
	{
		currentGame->GetDevice()->LightEnable(index, false);
		return true;
	}

	return false;
}

bool LightManager::TurnOffAll()
{
	hash_map<int, D3DLIGHT9*>::iterator iter;
	for(iter = lights.begin(); iter != lights.end(); iter++)
	{
		currentGame->GetDevice()->LightEnable(iter->first, false);
	}

	return true;
}

bool LightManager::Turn( int index )
{
	if (IsLightValid(index))
	{
		currentGame->GetDevice()->LightEnable(index, !IsLightOn(index));
		return true;
	}

	return false;
}

bool LightManager::IsLightValid( int index )
{
	if (lights.find(index) == lights.end(index))
	{
		return false;
	}

	return true;
}

bool LightManager::IsLightOn( int index )
{
	if (IsLightValid(index))
	{
		BOOL isOn = FALSE;
		currentGame->GetDevice()->GetLightEnable(index, &isOn);
		if (isOn)
		{
			return true;
		}		
	}

	return false;
}
