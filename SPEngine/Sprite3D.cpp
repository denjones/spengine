#include "StdAfx.h"
#include "Sprite3D.h"
#include "ColorHelper.h"

using namespace SPEngine;

Sprite3D::Sprite3D(void)
{
	texture = NULL;
	transformMatrix = D3DXMATRIX();
	center = D3DXVECTOR3();
	position = D3DXVECTOR3();
	color = Color::White;
	normal = D3DXVECTOR3();
	addressFind = D3DXVECTOR2();
}

Sprite3D::Sprite3D(Texture3D* setTexture,
	D3DXMATRIX setTransform,
	D3DXVECTOR3 setPosition,
	D3DXVECTOR3 setCenter,
	D3DCOLOR setColor, 
	D3DXVECTOR3 setNormal,
	D3DXVECTOR2 setAddress)
{
	texture = setTexture;
	transformMatrix = setTransform;
	center = setCenter;
	position = setPosition;
	color = setColor;
	normal = setNormal;
	addressFind = setAddress;
}

Sprite3D::~Sprite3D()
{

}