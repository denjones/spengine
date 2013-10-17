#pragma once
#include <d3dx9tex.h>
#include <string>
#include "SPRectangle.h"

using namespace std;

namespace SPEngine
{
	class SpriteManager;

	class Texture
	{
	public:
		LPDIRECT3DTEXTURE9 texture;
		SpriteManager* spriteManager;

	public:		
		int Width;
		int Height;

	public:
		Texture(void);

		Texture(const Texture&);

		Texture(
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
			D3DCOLOR	ColorKey);

		Texture(
			SpriteManager* manager,
			string		path);

		~Texture(void);


		// Load texture for sprite manager.
		bool Load(
			SpriteManager* manager,
			string		path);
		// Load texture for 3D use.
		bool Load(
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
			D3DCOLOR	ColorKey);
		bool Unload();

		// Render on screen with sprite manager;
		// Render simple
		bool Render();
		bool Render(
			float		x,
			float		y);
		bool Render(
			float		x,
			float		y,
			D3DCOLOR	color);
		bool Render(
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth);
		bool Render(
			D3DXVECTOR3 position);
		bool Render(
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool Render(
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool Render(
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool Render(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color);
		bool Render(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render on screen with rectangle
		bool RenderOnScreen(
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth);
		bool RenderOnScreen(
			SPRectangle srcRect,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth);

		// Render with transform matrix
		bool RenderWithMatrix(
			D3DXMATRIX	transformMatrix,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool RenderWithMatrix(
			D3DXMATRIX	transformMatrix,
			RECT		srcRect,
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);

		// Render with scaling 
		bool RenderWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color);
		bool RenderWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth);
		bool RenderWithScaling(
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color);
		bool RenderWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);
		bool RenderWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);

		// Render with rotation
		bool RenderWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color);
		bool RenderWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool RenderWithRotation(
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color);
		bool RenderWithRotation(
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render basic
		bool RenderBasic(
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);
		bool RenderBasic(
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);

		// Render centered
		bool RenderCentered();
		bool RenderCentered(
			float		x,
			float		y);
		bool RenderCentered(
			float		x,
			float		y,
			D3DCOLOR	color);
		bool RenderCentered(
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth);
		bool RenderCentered(
			D3DXVECTOR3 position);
		bool RenderCentered(
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool RenderCentered(
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool RenderCentered(
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool RenderCentered(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color);
		bool RenderCentered(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);
		bool RenderCentered(
			SPRectangle srcRect,
			D3DXVECTOR3 position,
			float		scale,
			float		rotation,
			D3DCOLOR	color);
		bool RenderCentered(
			SPRectangle srcRect,
			D3DXVECTOR3 position,
			float		scale,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render centered with scaling
		bool RenderCenteredWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color);
		bool RenderCenteredWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth);
		bool RenderCenteredWithScaling(
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color);
		bool RenderCenteredWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);
		bool RenderCenteredWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);

		// Render centered with rotation
		bool RenderCenteredWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color);
		bool RenderCenteredWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool RenderCenteredWithRotation(
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color);
		bool RenderCenteredWithRotation(
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render centered basic
		bool RenderCenteredBasic(
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);
		bool RenderCenteredBasic(
			RECT		srcRect,
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);
	};
}


