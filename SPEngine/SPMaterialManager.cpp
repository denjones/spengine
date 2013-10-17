#include "StdAfx.h"
#include "SPMaterialManager.h"
#include "SPColorHelper.h"
#include "SPGame.h"
#include "SPDevice.h"

using namespace SPEngine;

// Material constants
const D3DMATERIAL9 SPMaterialManager::WHITE_MTRL = InitializeMaterial(
	SPColor::White, SPColor::White, SPColor::White, SPColor::Black, 8.0f); 
const D3DMATERIAL9 SPMaterialManager::RED_MTRL = InitializeMaterial(
	SPColor::Red, SPColor::Red, SPColor::Red, SPColor::Black, 8.0f); 
const D3DMATERIAL9 SPMaterialManager::GREEN_MTRL = InitializeMaterial(
	SPColor::Green, SPColor::Green, SPColor::Green, SPColor::Black, 8.0f); 
const D3DMATERIAL9 SPMaterialManager::BLUE_MTRL = InitializeMaterial(
	SPColor::Blue, SPColor::Blue, SPColor::Blue, SPColor::Black, 8.0f); 
const D3DMATERIAL9 SPMaterialManager::YELLOW_MTRL = InitializeMaterial(
	SPColor::Yellow, SPColor::Yellow, SPColor::Yellow, SPColor::Black, 8.0f); 

SPMaterialManager::SPMaterialManager(void)
{

}

SPMaterialManager::~SPMaterialManager(void)
{
}

D3DMATERIAL9 SPMaterialManager::InitializeMaterial( D3DXCOLOR ambient, 
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

bool SPMaterialManager::SetMaterial( D3DMATERIAL9 mtrl )
{
	SPDevice::GetSingleton().GetD3DDevice()->SetMaterial(&mtrl); 
	return true;
}


