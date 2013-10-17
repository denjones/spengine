//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite3D.h the header file of SPSprite3D class.
/// @author		Ken.J & BlackSky
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"
#include "SPEffect.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSprite3D class to hold a 3d sprite.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSprite3D
	{
	public:
		SPTexturePtr	texture;
		SPEffectPtr effect;
		D3DXMATRIX		transformMatrix;
		D3DXVECTOR3		position;
		D3DXVECTOR3		center;
		D3DCOLOR		color;
		D3DXVECTOR3		normal;
		D3DXVECTOR2		addressFind;

	public:
		SPSprite3D(void);

		SPSprite3D(
			SPTexturePtr setTexture,
			SPEffectPtr pixelShader,
			D3DXMATRIX setTransform,
			D3DXVECTOR3 setPosition,
			D3DXVECTOR3 setCenter,
			D3DCOLOR setColor,
			D3DXVECTOR3 setNormal,
			D3DXVECTOR2 setAddress);

		virtual ~SPSprite3D();
	};
}