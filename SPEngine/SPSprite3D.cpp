//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite3D.cpp the implement file of SPSprite3D class.
/// @author		Ken.J & BlackSky
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPSprite3D.h"
#include "SPColorHelper.h"

namespace SPEngine
{
	SPSprite3D::SPSprite3D(void)
	{
		texture = NULL;
		transformMatrix = D3DXMATRIX();
		center = D3DXVECTOR3();
		position = D3DXVECTOR3();
		color = SPColor::White;
		normal = D3DXVECTOR3();
		addressFind = D3DXVECTOR2();
	}

	SPSprite3D::SPSprite3D(SPTexturePtr setTexture,
		SPEffectPtr setPS,
		D3DXMATRIX setTransform,
		D3DXVECTOR3 setPosition,
		D3DXVECTOR3 setCenter,
		D3DCOLOR setColor, 
		D3DXVECTOR3 setNormal,
		D3DXVECTOR2 setAddress)
	{
		texture = setTexture;
		effect = setPS;
		transformMatrix = setTransform;
		center = setCenter;
		position = setPosition;
		color = setColor;
		normal = setNormal;
		addressFind = setAddress;
	}

	SPSprite3D::~SPSprite3D()
	{

	}
}