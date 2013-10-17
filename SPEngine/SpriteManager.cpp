#include "StdAfx.h"
#include "SpriteManager.h"
#include "SPGame.h"
#include "ColorHelper.h"

using namespace SPEngine;

SpriteManager::SpriteManager(void)
{
	Renderer = NULL;
	currentGame = NULL;
}

SpriteManager::SpriteManager(SPGame* game)
{
	Register(game);
}

SpriteManager::~SpriteManager(void)
{
	Unload();
}

bool SpriteManager::Initialize()
{
	return true;
}

bool SpriteManager::Draw(float timeDelta)
{
	Renderer->Begin(D3DXSPRITE_ALPHABLEND);

	foreach(Sprite, sprite, list<Sprite>, sprites)
	{
		DrawSprite(sprite);
	}

	Renderer->End();

	sprites.clear();

	return true;
}

bool SpriteManager::DrawSprite( Sprite sprite )
{
	Renderer->SetTransform(&sprite.transformMatrix);
	Renderer->Draw(sprite.texture->texture, &sprite.sourceRect,
		&sprite.center, &sprite.position, sprite.color );

	return true;
}

bool SpriteManager::Update(float timeDelta)
{
	foreach(AnimatedTexture*, anime, list<AnimatedTexture*>, animes)
	{
		if (anime->UpdateFrame(timeDelta))
		{
			animes.remove(anime);
		}
	}
	return true;
}

bool SpriteManager::AddSprite( 
	Texture*	tex,
	D3DXVECTOR3 center,
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	RECT rect;
	SetRect(&rect, 0, 0, tex->Width , tex->Height);
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(&transformMatrix, 
		NULL, 0, NULL, NULL, 0, NULL);

	Sprite sprite(tex, transformMatrix, rect, center,
		position, color);
	sprites.push_back(sprite);

	return true;
}

bool SpriteManager::AddSprite( 
	Texture*	tex , 
	D3DXMATRIX	transformMatrix,
	RECT		srcRect,
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color)
{
	Sprite sprite(tex, transformMatrix, 
		srcRect, center, position, color);
	sprites.push_back(sprite);

	return true;
}

bool SpriteManager::AddSprite( 
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
	D3DCOLOR	color)
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(&transformMatrix, &scalingCenter,
		scalingRotation, &scaling, &rotationCenter,
		rotation, &translation);

	Sprite sprite(tex, transformMatrix, 
		srcRect, center, position, color);
	sprites.push_back(sprite);

	return true;
}

bool SpriteManager::AddAnime(AnimatedTexture* anime)
{
	animes.push_back(anime);
	return true;
}

bool SpriteManager::Load()
{
	if(FAILED(D3DXCreateSprite(currentGame->GetDevice(), &Renderer)))
	{
		return false;
	}

	return true;
}

bool SpriteManager::Unload()
{
	if (Renderer)
	{
		Renderer->Release();
		Renderer = NULL;
	}	

	return true;
}

LPDIRECT3DDEVICE9 SpriteManager::GetDevice()
{
	return currentGame->GetDevice();
}
