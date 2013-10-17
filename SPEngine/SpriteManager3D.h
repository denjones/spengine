#pragma once
#include <d3dx9core.h>
#include <list>
#include "Sprite3D.h"
#include "AnimatedTexture.h"
#include "SPComponent.h"

using namespace std;

namespace SPEngine
{
	class SPGame;

	class SpriteManager3D : public SPComponent
	{
	public:
		list<Sprite3D> sprites;

	public:
		SpriteManager3D(void);
		~SpriteManager3D();

		SpriteManager3D(SPGame* game);

		bool Initialize();

		bool addSprite3D(
			Texture3D* setTexture,
			D3DXVECTOR3 scalingCenter,
			D3DXQUATERNION scalingRotation,
			D3DXVECTOR3 scaling,
			D3DXVECTOR3 rotationCenter,
			D3DXQUATERNION rotation,
			D3DXVECTOR3 translation,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR color,
			D3DXVECTOR3 normal,
			D3DXVECTOR2 addressFind);

		bool addSprite3D(Texture3D* tex);
		bool addSprite3D(Texture3D* tex, 
			D3DXVECTOR3 scalingCenter, D3DXQUATERNION scalingRotation,
			D3DXVECTOR3 scaling, D3DXVECTOR3 rotationCenter,
			D3DXQUATERNION rotation, D3DXVECTOR3 translation);
		bool addSprite3D(Texture3D* tex, D3DXMATRIX transformMatrix);

		LPDIRECT3DDEVICE9 GetDevice();

		bool DrawSprite(Sprite3D sprite);

		bool Load();
		bool Unload();

		bool Update(float timeDelta);
		bool Draw(float timeDelta);

	private:
		void SetFilter();
	};
}