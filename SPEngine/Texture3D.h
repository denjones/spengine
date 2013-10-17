#pragma once
#include <d3dx9tex.h>
#include <string>
#include <d3d9.h>
#include "SPRectangle.h"

using namespace std;

namespace SPEngine
{
	class SpriteManager3D;

	struct Vertex3D
	{
		Vertex3D(
			float setX,
			float setY,
			float setZ,
			float setNx,
			float setNy,
			float setNz,
			float setU,
			float setV)
		{
			_x = setX; _y = setY; _z = setZ;
			_nx = setNx; _ny = setNy; _nz = setNz;
			_u = setU; _v = setV;
		}
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v; // texture coordinates
		static const DWORD FVF;
	};

	class Texture3D
	{
		CCritSec		objectLock;

	public:
		LPDIRECT3DTEXTURE9 texture;
		LPDIRECT3DTEXTURE9 textureToReplace;
		SpriteManager3D* spriteManager3D;

	public:
		int width;
		int height;

	public:
		Texture3D(void);
		Texture3D(const Texture3D&);
		Texture3D(
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

		Texture3D(
			SpriteManager3D* manager,
			string		path);

		~Texture3D(void);


		// Load texture for sprite manager.
		bool Load(
			SpriteManager3D* manager, 
			LPDIRECT3DTEXTURE9 tex);
		bool Load(
			SpriteManager3D* manager,
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

		bool Render();

		bool Render( 
			D3DXVECTOR3 scalingCenter, D3DXQUATERNION scalingRotation,
			D3DXVECTOR3 scaling, D3DXVECTOR3 rotationCenter,
			D3DXQUATERNION rotation, D3DXVECTOR3 translation);

		bool RenderByPosition(D3DXVECTOR3 position);

		bool RenderByPositionWithRotateself(D3DXVECTOR3 position, D3DXVECTOR3 rotationPoint, D3DXVECTOR3 rotationAxis, float degree);

		bool Render(D3DXMATRIX transformMatrix);

		bool Switch();
	};
}