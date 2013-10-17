#pragma once
#include "Texture3D.h"

namespace SPEngine
{
	class Sprite3D
	{
	public:
		Texture3D* texture;
		D3DXMATRIX transformMatrix;
		D3DXVECTOR3 position;
		D3DXVECTOR3 center;
		D3DCOLOR color;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 addressFind;

	public:
		Sprite3D(void);

		Sprite3D(
			Texture3D* setTexture,
			D3DXMATRIX setTransform,
			D3DXVECTOR3 setPosition,
			D3DXVECTOR3 setCenter,
			D3DCOLOR setColor,
			D3DXVECTOR3 setNormal,
			D3DXVECTOR2 setAddress);

		~Sprite3D();
	};
}