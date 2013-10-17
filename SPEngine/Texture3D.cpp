#include "StdAfx.h"
#include "Texture3D.h"
#include "SPGame.h"
#include "ColorHelper.h"
#include "SpriteManager3D.h"
#include "PackageHelper.h"

using namespace SPEngine;

const DWORD Vertex3D::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

Texture3D::Texture3D(void)
{
	spriteManager3D = NULL;
	texture = NULL;
	textureToReplace = NULL;
	width = 0;
	height = 0;
}

Texture3D::Texture3D(
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

Texture3D::Texture3D( SpriteManager3D* manager, string path )
{
	Load(manager, path);
}

Texture3D::~Texture3D()
{
	if(texture)
	{
		texture->Release();
		texture = NULL;
	}
}

bool Texture3D::Load(SpriteManager3D* manager, LPDIRECT3DTEXTURE9 tex)
{
	CAutoLock Lock(&objectLock);

	if (textureToReplace)
	{
		textureToReplace->Release();
	}

	textureToReplace = tex;

	spriteManager3D = manager;
	
	return true;
}

bool Texture3D::Load( SpriteManager3D* manager, string path )
{
	string fullPath;
	CAutoLock Lock(&objectLock);

	if (textureToReplace)
	{
		textureToReplace->Release();
	}

	spriteManager3D = manager;
	fullPath = "Image\\" + path;
	//D3DXIMAGE_INFO i;
	//PALETTEENTRY p; Don't know why we cannot make use of both palette and info.
	// Ether of them is used.

	if (FAILED(D3DXCreateTextureFromFileExA(
		manager->GetDevice(), fullPath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,	0,
		D3DFMT_A8B8G8R8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, 
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0,0,0,255),
		NULL, NULL,
		&textureToReplace)))
	{
		int fileSize;
		char* fileBuffer = NULL;
		if(!PackageHelper::GetFromFile(
			path, "Image.dat", fileBuffer, fileSize))
			return false;
		if(FAILED(D3DXCreateTextureFromFileInMemoryEx(
			manager->GetDevice(),
			fileBuffer,
			fileSize,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_FROM_FILE,	0,
			D3DFMT_A8B8G8R8,
			D3DPOOL_MANAGED,
			D3DX_FILTER_TRIANGLE, 
			D3DX_FILTER_TRIANGLE,
			D3DCOLOR_RGBA(0,0,0,255),
			NULL, NULL,
			&textureToReplace)))
		{
			return false;
		}
	}


	//height = i.Height;
	//width = i.Width;

	return true;
}

bool Texture3D::Load( 
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
	CAutoLock Lock(&objectLock);

	if (textureToReplace)
	{
		textureToReplace->Release();
	}

	spriteManager3D = NULL;
	D3DXIMAGE_INFO i;
	D3DXCreateTextureFromFileExA(pDevice, pSrcFile, setWidth, setHeight,
		MipLevels, Usage,	Format, Pool, Filter, MipFilter, ColorKey,
		&i, NULL, &textureToReplace); 

	height = i.Height;
	width = i.Width;

	return true;
}

bool Texture3D::Render()
{
	Switch();

	if(spriteManager3D)
	{
		spriteManager3D->addSprite3D(this);
	}
	else
	{
		return false;
	}
	return true;
}

bool Texture3D::Render(
	D3DXVECTOR3 scalingCenter, D3DXQUATERNION scalingRotation,
	D3DXVECTOR3 scaling, D3DXVECTOR3 rotationCenter,
	D3DXQUATERNION rotation, D3DXVECTOR3 translation)
{
	Switch();

	translation.x = translation.x / 600.0f * 2.0f;
	translation.y = translation.y / 600.0f * 2.0f;
	translation.z = translation.z / 600.0f * 2.0f;
	if(spriteManager3D)
	{
		spriteManager3D->addSprite3D(this, scalingCenter,
			scalingRotation, scaling, rotationCenter,
			rotation, translation);
	}
	else
	{
		return false;
	}
	return true;
}

bool Texture3D::RenderByPosition(D3DXVECTOR3 position)
{
	return Render(D3DXVECTOR3(0, 0, 0), D3DXQUATERNION(0, 0, 0, 0),
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0),
		D3DXQUATERNION(0, 0, 0, 0), position);
}

bool Texture3D::Render(D3DXMATRIX transformMatrix)
{
	Switch();

	if(spriteManager3D)
	{
		spriteManager3D->addSprite3D(this, transformMatrix);
	}
	else 
	{
		return false;
	}

	return true;
}

bool Texture3D::RenderByPositionWithRotateself(D3DXVECTOR3 position,
	D3DXVECTOR3 rotatePoint, D3DXVECTOR3 rotationAxis, float degree)
{
	D3DXQUATERNION quaternion;
	float w = cos(degree / 2);
	float s = sin(degree / 2);
	quaternion.x = rotationAxis.x * s;
	quaternion.y = rotationAxis.y * s;
	quaternion.z = rotationAxis.z * s;
	quaternion.w = w;
	return Render(D3DXVECTOR3(0, 0, 0), D3DXQUATERNION(0, 0, 0, 0), 
		D3DXVECTOR3(0, 0, 0), rotatePoint, quaternion, position);
}

bool SPEngine::Texture3D::Switch()
{
	if (textureToReplace)
	{
		if (texture)
		{
			texture->Release();
			texture = NULL;
		}

		D3DSURFACE_DESC desc;
		textureToReplace->GetLevelDesc(0, &desc);
		height = desc.Height;
		width = desc.Width;
		
		D3DXCreateTexture(
			spriteManager3D->GetDevice(),
			width, height,
			textureToReplace->GetLevelCount(),
			NULL,desc.Format,
			D3DPOOL_MANAGED, &texture);

		LPDIRECT3DSURFACE9 pSrcSurf = NULL;
		LPDIRECT3DSURFACE9 pDestSurf = NULL;

		for( int i = 0 ; i < textureToReplace->GetLevelCount() ; i++ )
		{
			texture->GetSurfaceLevel( i, &pDestSurf );
			textureToReplace->GetSurfaceLevel( i, &pSrcSurf );

			D3DXLoadSurfaceFromSurface(	pDestSurf,	NULL, NULL,	pSrcSurf,
				NULL, NULL, D3DX_FILTER_NONE, NULL);

			//pDestSurf->Release();
			//pSrcSurf->Release();
		}

		textureToReplace = NULL;
	}

	return true;
}

bool SPEngine::Texture3D::Unload()
{
	if (texture)
	{
		texture->Release();
		texture = NULL;
	}

	return true;
}
