#include "StdAfx.h"
#include "Texture.h"
#include "SpriteManager.h"
#include "SPGame.h"
#include "ColorHelper.h"

using namespace SPEngine;

Texture::Texture(void)
{
	spriteManager = NULL;
	texture = NULL;
}

Texture::~Texture(void)
{
	if (texture)
	{
		texture->Release();
		texture = NULL;
	}
}

Texture::Texture( 
	LPDIRECT3DDEVICE9 pDevice,
	LPCSTR		pSrcFile, 
	UINT		setWidth,
	UINT		setHeight,
	UINT		MipLevels,
	DWORD		Usage,
	D3DFORMAT	Format,
	D3DPOOL		Pool,
	DWORD		Filter,
	DWORD		MipFilter,
	D3DCOLOR	ColorKey)
{
	Load(pDevice, pSrcFile, setWidth, setHeight, MipLevels,
		Usage, Format, Pool, Filter, MipFilter, ColorKey);
}

Texture::Texture( SpriteManager* manager, string path )
{
	Load(manager, path);
}

bool Texture::Load( SpriteManager* manager, string path )
{
	spriteManager = manager;
	D3DXIMAGE_INFO i;
	//PALETTEENTRY p; Don't know why we cannot make use of both palette and info.
	// Ether of them is used.

	if (FAILED(D3DXCreateTextureFromFileExA(
		manager->GetDevice(), path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,	0,
		D3DFMT_A8B8G8R8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, 
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0,0,0,255),
		&i, NULL,
		&texture)))
	{
		return false;
	}
	

	Height = i.Height;
	Width = i.Width;

	return true;
}

bool Texture::Load( 
	LPDIRECT3DDEVICE9 pDevice,
	LPCSTR		pSrcFile,
	UINT		setWidth,
	UINT		setHeight,
	UINT		MipLevels,
	DWORD		Usage,
	D3DFORMAT	Format,
	D3DPOOL		Pool, 
	DWORD		Filter,
	DWORD		MipFilter,
	D3DCOLOR	ColorKey )
{
	spriteManager = NULL;
	D3DXIMAGE_INFO i;
	D3DXCreateTextureFromFileExA(pDevice, pSrcFile, setWidth, setHeight,
		MipLevels, Usage,	Format, Pool, Filter, MipFilter, ColorKey,
		&i, NULL, &texture); 

	Height = i.Height;
	Width = i.Width;

	return true;
}

// Simple render function
bool Texture::Render()
{
	return	Render(D3DXVECTOR3(0, 0, 0));
}

bool Texture::Render(
	float		x,
	float		y)
{
	return Render(x, y, Color::White);
}

bool Texture::Render(
	D3DXVECTOR3 position)
{
	return Render(position, Color::White);
}

bool Texture::Render(
	float		x,
	float		y,
	D3DCOLOR	color)
{
	return Render(x, y, color, 0);
}

bool Texture::Render(
	float		x,
	float		y,
	D3DCOLOR	color,
	float		depth)
{
	return Render(D3DXVECTOR3(x, y, depth), color);
}

bool Texture::Render(
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	return Render(D3DXVECTOR3(0, 0, 0), position, color);
}

bool Texture::Render( 
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color )
{
	if (spriteManager)
	{
		spriteManager->AddSprite(this, center, position, color);
	}
	else
	{
		return false;
	}

	return true;
}

bool Texture::Render(
	float		x,
	float		y,
	float		scale,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return Render(D3DXVECTOR3(x, y, depth),
		D3DXVECTOR2(scale, scale), rotation, color);
}

bool Texture::Render(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	float		rotation,
	D3DCOLOR	color)
{
	return Render(position, D3DXVECTOR2(position.x, position.y), 0, 
		scaling, D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool Texture::Render(
	D3DXVECTOR3 position,			
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderBasic(D3DXVECTOR3(0, 0, 0), position, color, 
		scalingCenter, scalingRotation, scaling,
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

// Render on screen with rectangle
bool Texture::RenderOnScreen(
	SPRectangle	destRect,
	D3DCOLOR	color,
	float		depth)
{
	return RenderOnScreen(SPRectangle(0, 0, Width, Height), destRect, color, depth);
}

bool Texture::RenderOnScreen(
	SPRectangle	srcRect,
	SPRectangle	destRect,
	D3DCOLOR	color,
	float		depth)
{
	return RenderBasic(srcRect.CRect(), D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3((float)destRect.X, (float)destRect.Y, depth),
		color, D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
		D3DXVECTOR2((float)destRect.Width / srcRect.Width, 
		(float)destRect.Height / srcRect.Height), 
		D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
		D3DXVECTOR2(0,0));
}

// Render with matrix
bool Texture::RenderWithMatrix(
	D3DXMATRIX	transformMatrix,
	D3DXVECTOR3 center,
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	RECT srcRect;
	SetRect(&srcRect, 0, 0, Width, Height);
	return RenderWithMatrix(transformMatrix,
		srcRect, center, position, color);
}

bool Texture::RenderWithMatrix( 
	D3DXMATRIX	transformMatrix,
	RECT		srcRect,
	D3DXVECTOR3 center,
	D3DXVECTOR3 position,
	D3DCOLOR	color )
{
	if (spriteManager)
	{
		spriteManager->AddSprite(this, transformMatrix,
			srcRect, center, position, color);
	}
	else
	{
		return false;
	}

	return true;
}

// Render with scaling
bool Texture::RenderWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color)
{
	return RenderWithScaling(x, y, scale, color, 0);
}

bool Texture::RenderWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color,
	float		depth)
{
	return RenderWithScaling(D3DXVECTOR3(x, y, depth), scale, color);
}

bool Texture::RenderWithScaling(
	D3DXVECTOR3 position,
	float		scale,
	D3DCOLOR	color)
{
	return	RenderWithScaling(position, 
		D3DXVECTOR2(scale, scale),	color);
}

bool Texture::RenderWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return RenderWithScaling(position,
		D3DXVECTOR2(position.x, position.y), 0, scaling, color);
}

bool Texture::RenderWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return RenderBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, scalingCenter, scalingRotation, scaling,
		D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0));
}

// Render with rotation
bool Texture::RenderWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderWithRotation(x, y, rotation, color, 0);
}

bool Texture::RenderWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return RenderWithRotation(D3DXVECTOR3(x,y,depth), rotation, color);
}

bool Texture::RenderWithRotation(
	D3DXVECTOR3 position,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderWithRotation(position, 
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool Texture::RenderWithRotation(
	D3DXVECTOR3 position,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool Texture::RenderBasic( 
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color, 
	D3DXVECTOR2 scalingCenter, 
	float		scalingRotation, 
	D3DXVECTOR2 scaling, 
	D3DXVECTOR2 rotationCenter, 
	float		rotation, 
	D3DXVECTOR2 translation )
{
	RECT srcRect;
	SetRect(&srcRect, 0, 0, Width, Height);

	return RenderBasic(srcRect, center, position, color, scalingCenter, 
		scalingRotation, scaling, rotationCenter, 
		rotation, translation);
}

bool Texture::RenderBasic(
	RECT		srcRect,
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR	color,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DXVECTOR2 translation)
{
	if (spriteManager)
	{
		spriteManager->AddSprite(this,
			scalingCenter, scalingRotation,	scaling,
			rotationCenter, rotation, translation,
			srcRect, center, position, color);
	}
	else
	{
		return false;
	}

	return true;
}

// Render centered
bool Texture::RenderCentered()
{
	return	RenderCentered(D3DXVECTOR3(0, 0, 0));
}

bool Texture::RenderCentered(
	float		x,
	float		y)
{
	return RenderCentered(x, y, Color::White);
}

bool Texture::RenderCentered(
	D3DXVECTOR3 position)
{
	return RenderCentered(position, Color::White);
}

bool Texture::RenderCentered(
	float		x,
	float		y,
	D3DCOLOR	color)
{
	return RenderCentered(x, y, color, 0);
}

bool Texture::RenderCentered(
	float		x,
	float		y,
	D3DCOLOR	color,
	float		depth)
{
	return RenderCentered(D3DXVECTOR3(x, y, depth), color);
}

bool Texture::RenderCentered(
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	return RenderCentered(D3DXVECTOR3(0, 0, 0), position, color);
}

bool Texture::RenderCentered( 
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color )
{
	if (spriteManager)
	{
		spriteManager->AddSprite(this, center, 
			D3DXVECTOR3(position.x - Width / 2, 
			position.y - Height / 2, position.z), color);
	}
	else
	{
		return false;
	}

	return true;
}

bool Texture::RenderCentered(
	float		x,
	float		y,
	float		scale,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return RenderCentered(D3DXVECTOR3(x, y, depth),
		D3DXVECTOR2(scale, scale), rotation, color);
}

bool Texture::RenderCentered(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCentered(position, D3DXVECTOR2(position.x, position.y), 0, 
		scaling, D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool Texture::RenderCentered(
	D3DXVECTOR3 position,			
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, color, 
		scalingCenter, scalingRotation, scaling,
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool Texture::RenderCentered(
	SPRectangle srcRect,
	D3DXVECTOR3 position,
	float		scale,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCentered(srcRect, position, scale,
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool Texture::RenderCentered(
	SPRectangle srcRect,
	D3DXVECTOR3 position,
	float		scale,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderBasic(srcRect.CRect(), D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(position.x - srcRect.Width / 2,
		position.y - srcRect.Height / 2, position.z),
		color, D3DXVECTOR2(position.x, position.y), 
		0, D3DXVECTOR2(scale, scale),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}
 
// Render with scaling
bool Texture::RenderCenteredWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color)
{
	return RenderCenteredWithScaling(x, y, scale, color, 0);
}

bool Texture::RenderCenteredWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color,
	float		depth)
{
	return RenderCenteredWithScaling(D3DXVECTOR3(x, y, depth), scale, color);
}

bool Texture::RenderCenteredWithScaling(
	D3DXVECTOR3 position,
	float		scale,
	D3DCOLOR	color)
{
	return	RenderCenteredWithScaling(position, 
		D3DXVECTOR2(scale, scale),	color);
}

bool Texture::RenderCenteredWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return RenderCenteredWithScaling(position,
		D3DXVECTOR2(position.x, position.y), 0, scaling, color);
}

bool Texture::RenderCenteredWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return RenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, scalingCenter, scalingRotation, scaling,
		D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0));
}

// Render with rotation
bool Texture::RenderCenteredWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCenteredWithRotation(x, y, rotation, color, 0);
}

bool Texture::RenderCenteredWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return RenderCenteredWithRotation(D3DXVECTOR3(x,y,depth), rotation, color);
}

bool Texture::RenderCenteredWithRotation(
	D3DXVECTOR3 position,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCenteredWithRotation(position, 
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool Texture::RenderCenteredWithRotation(
	D3DXVECTOR3 position,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return RenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool Texture::RenderCenteredBasic(
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR	color,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DXVECTOR2 translation)
{
	RECT srcRect;
	SetRect(&srcRect, 0, 0, Width, Height);

	return RenderCenteredBasic(srcRect, center, position, 
		color, scalingCenter, scalingRotation, scaling, 
		rotationCenter, rotation,translation);
}

bool Texture::RenderCenteredBasic(
	RECT		srcRect,
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR	color,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DXVECTOR2 translation)
{
	return RenderBasic(srcRect, center, D3DXVECTOR3(position.x - Width / 2,
		position.y - Height / 2, position.z),
		color, scalingCenter, scalingRotation, scaling,
		rotationCenter, rotation, translation);
}

bool SPEngine::Texture::Unload()
{
	if (texture)
	{
		texture->Release();
		texture = NULL;
	}

	return true;
}
