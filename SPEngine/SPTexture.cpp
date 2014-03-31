#include "StdAfx.h"
#include "SPTexture.h"
#include "SPSpriteManager.h"
#include "SPGame.h"
#include "SPColorHelper.h"
#include "SPDevice.h"
#include "SPFileManager.h"
#include "SPGameManager.h"

namespace SPEngine
{
	SPTexture::SPTexture(void)
	{
		texture = NULL;
		width = 0;
		height = 0;
		format = D3DFMT_A8R8G8B8;
		path = L"";
		isRenderTarget = false;
		backgroundColor = SPColorHelper::AlphaColor(0, SPColor::Black);
	}

	SPTexture::~SPTexture(void)
	{
		if (texture)
		{
			texture->Release();
			texture = NULL;
		}
	}

	SPTexture::SPTexture( 
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
		texture = NULL;
		width = 0;
		height = 0;
		format = D3DFMT_A8R8G8B8;
		isRenderTarget = false;
		backgroundColor = SPColorHelper::AlphaColor(0, SPColor::Black);

		Load(pDevice, pSrcFile, setWidth, setHeight, MipLevels,
			Usage, Format, Pool, Filter, MipFilter, ColorKey);
	}

	SPTexture::SPTexture( SPString setPath )
	{
		texture = NULL;
		width = 0;
		height = 0;
		format = D3DFMT_A8R8G8B8;
		isRenderTarget = false;

		Load(setPath);
	}

	bool SPTexture::Load( SPString setPath )
	{
		D3DXIMAGE_INFO i;
		//PALETTEENTRY p; Don't know why we cannot make use of both palette and info.
		// Ether of them is used.

		// Open texture file.
		SPFilePtr file = SPFileManager::GetSingleton()->OpenFile(setPath);
		
		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPGraphics] WARNING: Failed to open file: " + setPath);
			return false;
		}

		// Read file data.
		LONGLONG length = file->GetFileLength();
		char* pData = new char[(unsigned int)length];
		
		if (!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPGraphics] WARNING: Failed to read file: " + setPath);
			return false;
		}		

		// Create texture from memory.
		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(
			SPDevice::GetSingleton()->GetD3DDevice(), 
			pData, (UINT)length,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_FROM_FILE,	0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			D3DX_FILTER_TRIANGLE, 
			D3DX_FILTER_TRIANGLE,
			D3DCOLOR_RGBA(0,0,0,0),
			&i, NULL,
			&texture);

		// Close texture file.
		SPFileManager::GetSingleton()->CloseFile(setPath);
		delete [] pData;
		pData = NULL;
		if (FAILED(hr))
		{
			texture = NULL;
			return false;
		}
	
		path = setPath;
		height = i.Height;
		width = i.Width;
		format = D3DFMT_A8R8G8B8;

		return true;
	}

	bool SPTexture::Load( 
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
		D3DXIMAGE_INFO i;
		D3DXCreateTextureFromFileExA(pDevice, pSrcFile, setWidth, setHeight,
			MipLevels, Usage,	Format, Pool, Filter, MipFilter, ColorKey,
			&i, NULL, &texture); 

		height = i.Height;
		width = i.Width;
		format = Format;

		return true;
	}

	bool SPTexture::Load()
	{
		return Reload();
	}

	bool SPTexture::Reload()
	{
		if (path == L"")
		{
			return CreateBlank(width, height);
		}

		return Load(path);
	}

	bool SPTexture::CreateBlank( int setWidth, int setHeight )
	{
		// Create texture from memory.
		HRESULT hr = D3DXCreateTexture(
			SPDevice::GetSingleton()->GetD3DDevice(),
			setWidth, setHeight,
			0,	0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			&texture);

		if (FAILED(hr))
		{
			texture = NULL;
			return false;
		}

		height = setHeight;
		width = setWidth;
		format = D3DFMT_A8R8G8B8;

		return true;
	}

	bool SPTexture::Fill( D3DCOLOR color )
	{
		if (!texture)
		{
			return false;
		}

		if (isRenderTarget)
		{
			ID3DXRenderToSurface* renderToSurface = NULL;
			LPDIRECT3DSURFACE9 pRenderSurface = NULL;

			HRESULT hr = texture->GetSurfaceLevel(0, &pRenderSurface);

			D3DSURFACE_DESC desc;
			hr = pRenderSurface->GetDesc( &desc );

			hr = D3DXCreateRenderToSurface(
				SPDevice::GetSingleton()->GetD3DDevice(), 
				desc.Width, 
				desc.Height,
				desc.Format,
				FALSE, 
				D3DFMT_D24S8,
				&renderToSurface);

			if (SPGameManager::GetSingleton()->GetGame()->IsRendering())
			{
				SPDevice::GetSingleton()->GetD3DDevice()->EndScene();
			}

			hr = renderToSurface->BeginScene(pRenderSurface, NULL);

			SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, color, 1.0, 0);

			hr = renderToSurface->EndScene(0);

			renderToSurface->Release();
			renderToSurface = NULL;

			pRenderSurface->Release();
			pRenderSurface = NULL;

			if (SPGameManager::GetSingleton()->GetGame()->IsRendering())
			{
				SPDevice::GetSingleton()->GetD3DDevice()->BeginScene();
			}

			return SUCCEEDED(hr);
		}

		D3DLOCKED_RECT lockedRect;

		texture->LockRect(
			0 /*lock top surface*/,
			&lockedRect, 
			0 /* lock entire tex*/,
			0 /*flags*/);         

		DWORD* imageData = (DWORD*)lockedRect.pBits;
		for(int row = 0; row < height; row++) 
		{
			for(int col = 0; col < width; col++) 
			{
				imageData[row * lockedRect.Pitch / 4 + col] = color;
			}
		}

		texture->UnlockRect(0);

		return true;
	}

	bool SPTexture::CreateRenderTarget( int setWidth, int setHeight, D3DXCOLOR setColor )
	{
		// Create texture from memory.
		HRESULT hr = D3DXCreateTexture(
			SPDevice::GetSingleton()->GetD3DDevice(),
			setWidth, setHeight,
			1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&texture);

		if (FAILED(hr))
		{
			texture = NULL;
			return false;
		}

		height = setHeight;
		width = setWidth;
		format = D3DFMT_A8R8G8B8;
		isRenderTarget = true;
		backgroundColor = setColor;

		//Fill(0x00000000);

		return true;
	}

	SPEngine::SPRectangle SPTexture::SourceRectangle()
	{
		return SPRectangle(0, 0, width, height);
	}

	bool SPEngine::SPTexture::Unload()
	{
		if (texture)
		{
			texture->Release();
			texture = NULL;
		}

		return true;
	}
}