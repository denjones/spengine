#pragma once
#include <SPEngine.h>

using namespace SPEngine;

class SampleGame : public SPGame
{
	SPTexturePtr texture;
	SPTexturePtr texture1;
	SPTexturePtr texture2;
	SPTexturePtr texture3;
	SPTexturePtr renderTarget;

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
		texture = SPTextureManager::GetSingleton().GetTexture(L"sicily.jpg");
		texture1 = SPTextureManager::GetSingleton().GetTexture(L"bg_classroom_01.png");
		texture2 = SPTextureManager::GetSingleton().GetTexture(L"dialog_bg.png");
		texture3 = SPTextureManager::GetSingleton().GetTexture(L"dialog_button_qload.png");
		renderTarget = SPTextureManager::GetSingleton().CreateRenderTarget(800, 600, 0);
		return true;
	}

	bool Draw(float timeDelta)
	{
		// Using sprite manager.

		// Render texture with scaling.
		static float elapsed = 0;
		elapsed += timeDelta;
		//SPSpriteManager::GetSingleton().RenderWithScaling(texture, NULL, D3DXVECTOR3(100, 200, 0.3f),
		//	D3DXVECTOR2(0.5,0.5), SPColorHelper::AlphaColor(1-elapsed * 0.1, SPColor::White), NULL);
		//SPSpriteManager::GetSingleton().RenderWithScaling(texture, NULL, D3DXVECTOR3(100, 200, 0.4f),
		//	D3DXVECTOR2(0.5,0.5), SPColorHelper::AlphaColor(elapsed * 0.1, SPColor::White), NULL);

		// Render texture with rotation.

		static float rotation = 0;
		rotation += timeDelta;

		SPTexturePtr tex = SPTextureManager::GetSingleton().CreateRenderTarget(100,100, 0);

		SPTexturePtr color = SPTextureManager::GetSingleton().GetBlankWhiteTexture();

		SPSpriteManager::GetSingleton().RenderOnScreen(color, NULL, SPRectangle(0,0,800,600), SPColor::Black, 0.9, NULL);

		//SPSpriteManager::GetSingleton().RenderWithRotation(texture, NULL, D3DXVECTOR3(200, 300, 0.9f),
		//	rotation, SPColor::White, NULL);

		//SPSpriteManager::GetSingleton().RenderWithRotation(texture1, NULL, D3DXVECTOR3(0, 0, 0.6f),
		//	0, SPColor::White, NULL);

		//SPSpriteManager::GetSingleton().RenderWithRotation(texture2, NULL, D3DXVECTOR3(0, 0, 0.5f),
		//	0, SPColor::White, NULL);

		//SPSpriteManager::GetSingleton().RenderWithRotation(texture3, NULL, D3DXVECTOR3(20, 20, 0.4f),
		//	0, SPColor::White, NULL);

		SPSpriteManager::GetSingleton().RenderWithRotation(texture1, NULL, D3DXVECTOR3(0, 0, 0.6f),
			0, SPColor::White, renderTarget);

		SPSpriteManager::GetSingleton().RenderWithRotation(texture3, NULL, D3DXVECTOR3(0, 0, 0.4f),
			0, SPColor::White, tex);

		SPSpriteManager::GetSingleton().RenderWithRotation(tex, NULL, D3DXVECTOR3(20, 20, 0.4f),
			0, SPColor::White, renderTarget);

		SPSpriteManager::GetSingleton().RenderWithRotation(texture2, NULL, D3DXVECTOR3(0, 0, 0.5f),
			0, SPColor::White, renderTarget);

		SPSpriteManager::GetSingleton().RenderWithRotation(renderTarget, NULL, D3DXVECTOR3(0, 0, 0.2f),
			0, SPColor::White, NULL);

		// Render part of texture with source rectangle.
		SPRectangle srcRect(100, 100, 200, 200);
		SPRectangle rect(0, 0, 800, 600);
		//SPSpriteManager::GetSingleton().RenderOnScreen(texture, NULL, srcRect, rect, SPColor::White, 1, NULL);
		//SPSpriteManager::GetSingleton().RenderCentered(texture, NULL, srcRect, D3DXVECTOR3(600, 300, 0.4f),
		//	1.5f, rotation, SPColor::White, NULL);

		return SPGame::Draw(timeDelta);
	}
};

