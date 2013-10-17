#include "StdAfx.h"
#include "Sprite.h"
#include "ColorHelper.h"

using namespace SPEngine;

Sprite::Sprite(void)
{
	texture = NULL;
	transformMatrix = D3DXMATRIX();
	sourceRect = RECT();
	center = D3DXVECTOR3();
	position = D3DXVECTOR3();
	color = Color::White;
}

Sprite::~Sprite(void)
{
}

Sprite::Sprite( Texture* setTex,D3DXMATRIX setTrans,RECT setSourceRect,
	D3DXVECTOR3 setCenter, D3DXVECTOR3 setPos, D3DCOLOR setColor )
{
	texture = setTex;
	transformMatrix = setTrans;
	sourceRect = setSourceRect;
	center = setCenter;
	position = setPos;
	color = setColor;
}
