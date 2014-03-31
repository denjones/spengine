#pragma once
#include <SPEngine.h>

using namespace SPEngine;

class SampleGame : public SPGame
{
	SPTexturePtr texture;

public:
	SampleGame(HINSTANCE hInstance) : SPGame(hInstance) {}
	SampleGame(void) : SPGame() { texture = NULL; }
	~SampleGame(void) {}

	bool LoadContent()
	{
		if(!SPGame::LoadContent())
		{
			return false;
		}

		// Load texture.
		texture = SPTextureManager::GetSingleton()->GetTexture(L"sicily.jpg");

		return true;
	}

	bool Draw(float timeDelta)
	{
		// Using 3D sprite manager.
		
		static float angle = 0;
		angle += timeDelta;

		SPSpriteManager3D::GetSingleton()->Render(texture, NULL, D3DXVECTOR3(0, 0, 0), 
			D3DXQUATERNION(0, 0, 0, 0),	D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.2f, 0, 0.2f),
			D3DXQUATERNION(0, 0, sin(angle / 2), cos(angle / 2)), D3DXVECTOR3(-100, 0, -200));

		//SPSpriteManager3D::GetSingleton()->RenderByPosition(texture, NULL, D3DXVECTOR3(0, 0, 0));

		SPSpriteManager3D::GetSingleton()->RenderByPositionWithRotateself(texture, NULL,
			D3DXVECTOR3(100, 0, 100), D3DXVECTOR3(0.2f, 0, 0.2f),
			D3DXVECTOR3(0, 0, 1), angle);

		return SPGame::Draw(timeDelta);
	}
};

