#pragma once
#include "Texture.h"

namespace SPEngine
{
	class Sprite
	{
	public:
		Texture* texture;
		D3DXMATRIX transformMatrix;
		RECT sourceRect;
		D3DXVECTOR3 center;
		D3DXVECTOR3 position;
		D3DCOLOR color; 

	public:
		Sprite(void);
		Sprite(
			Texture*,
			D3DXMATRIX,
			RECT,
			D3DXVECTOR3,
			D3DXVECTOR3,
			D3DCOLOR);
		~Sprite(void);
	};
}


