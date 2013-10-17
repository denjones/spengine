#pragma once
#include <d3dx9core.h>
#include <list>
#include "Sprite.h"
#include "AnimatedTexture.h"
#include "SPComponent.h"

using namespace std;

namespace SPEngine
{
	class SPGame;

	class SpriteManager : public SPComponent
	{
		list<Sprite> sprites;
		list<AnimatedTexture*> animes;

	public:
		LPD3DXSPRITE Renderer;

	public:
		SpriteManager(void);
		~SpriteManager(void);

		SpriteManager(SPGame* game);

		bool Initialize();
		bool AddSprite(
			Texture*	tex,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool AddSprite( 
			Texture*	tex ,			
			D3DXMATRIX	transformMatrix, 
			RECT		secRect,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool AddSprite( 
			Texture*	tex ,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation,
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color);

		LPDIRECT3DDEVICE9 GetDevice();

		bool AddAnime(AnimatedTexture* anime);
		bool DrawSprite(Sprite sprite);

		bool Load();
		bool Unload();

		bool Update(float timeDelta);
		bool Draw(float timeDelta);
	};
}


