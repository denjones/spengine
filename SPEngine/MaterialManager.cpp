#include "StdAfx.h"
#include "MaterialManager.h"
#include "ColorHelper.h"
#include "SPGame.h"

using namespace SPEngine;

// Material constants
const D3DMATERIAL9 MaterialManager::WHITE_MTRL = InitializeMaterial(
	Color::White, Color::White, Color::White, Color::Black, 8.0f); 
const D3DMATERIAL9 MaterialManager::RED_MTRL = InitializeMaterial(
	Color::Red, Color::Red, Color::Red, Color::Black, 8.0f); 
const D3DMATERIAL9 MaterialManager::GREEN_MTRL = InitializeMaterial(
	Color::Green, Color::Green, Color::Green, Color::Black, 8.0f); 
const D3DMATERIAL9 MaterialManager::BLUE_MTRL = InitializeMaterial(
	Color::Blue, Color::Blue, Color::Blue, Color::Black, 8.0f); 
const D3DMATERIAL9 MaterialManager::YELLOW_MTRL = InitializeMaterial(
	Color::Yellow, Color::Yellow, Color::Yellow, Color::Black, 8.0f); 

MaterialManager::MaterialManager(void)
{
	currentGame = NULL;
}

MaterialManager::MaterialManager(SPGame* game)
{
	Register(game);
}

MaterialManager::~MaterialManager(void)
{
}

bool MaterialManager::Initialize()
{
	return true;
}

bool MaterialManager::Load()
{
	return true;
}

bool MaterialManager::Unload()
{
	return true;
}

bool MaterialManager::Update(float timeDelta)
{
	return true;
}

bool MaterialManager::Draw(float timeDelta)
{
	return true;
}

D3DMATERIAL9 MaterialManager::InitializeMaterial( D3DXCOLOR ambient, 
	D3DXCOLOR diffuse, D3DXCOLOR specular, 
	D3DXCOLOR emissive, float power )
{ 
	D3DMATERIAL9 mtrl; 
	mtrl.Ambient = ambient; 
	mtrl.Diffuse = diffuse; 
	mtrl.Specular = specular; 
	mtrl.Emissive = emissive; 
	mtrl.Power = power; 
	return mtrl; 
}

bool MaterialManager::SetMaterial( D3DMATERIAL9 mtrl )
{
	currentGame->GetDevice()->SetMaterial(&mtrl); 
	return true;
}


