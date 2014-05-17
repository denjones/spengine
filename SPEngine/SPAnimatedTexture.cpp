//////////////////////////////////////////////////////////////////////////
/// @file		SPAnimatedTexture.cpp the implement file of SPAnimatedTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-18
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPAnimatedTexture.h"
#include "SPSpriteManager.h"
#include "SPGame.h"
#include "SPColorHelper.h"
#include "SPDevice.h"
#include "SPFile.h"
#include "SPFileManager.h"

namespace SPEngine
{
	SPAnimatedTexture::SPAnimatedTexture(void)
	{
		this->texture = NULL;
		this->origin = D3DXVECTOR2(0, 0);
		this->row = 0;
		this->column = 0;
		this->frameCount = 0;
		this->timePerFrame = 0;
		this->frame = 0;
		this->totalElapsed = 0;
		this->isPaused = true;
		this->isToBeRemoved = true;
		this->width = 0;
		this->height = 0;
	}

	void SPAnimatedTexture::Reload()
	{
		Load(path, row, column, frameCount, (int)(1 / timePerFrame), origin);
	}

	void SPAnimatedTexture::Load(
		SPString setPath,
		int setRow,
		int setColumn, 
		int setFPS)
	{
		Load( setPath, setRow, setColumn,
			setRow * setColumn, setFPS, D3DXVECTOR2(0,0));
	}

	void SPAnimatedTexture::Load(
		SPString setPath,
		int setRow,
		int setColumn, 
		int setFPS, 
		D3DXVECTOR2 setOrigin)
	{
		Load(setPath, setRow, setColumn,
			setRow * setColumn, setFPS, setOrigin);
	}

	void SPAnimatedTexture::Load(
		SPString setPath,
		int setRow,
		int setColumn,
		int setFrame,
		int setFPS, 
		D3DXVECTOR2 setOrigin)
	{
		path = setPath;

		row = setRow;
		column = setColumn;

		if (row <= 0)
		{
			row = 1;
		}

		if (column <= 0)
		{
			column = 1;
		}

		frameCount = setFrame;
		timePerFrame = (float)1 / setFPS;
		isToBeRemoved = false;

		frame = 0;
		totalElapsed = 0;
		isPaused = false;	

		D3DXIMAGE_INFO i;
		//PALETTEENTRY p; Don't know why we cannot make use of both palette and info.
		// Ether of them is used.

		// Open texture file.
		SPFilePtr file = SPFileManager::GetSingleton()->OpenFile(setPath);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPGraphics] WARNING: Failed to open file: " + setPath);
			return;
		}

		// Read file data.
		LONGLONG length = file->GetFileLength();
		char* pData = new char[(unsigned int)length];

		if (!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPGraphics] WARNING: Failed to read file: " + setPath);
			return;
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
			SPLogHelper::WriteLog(L"[SPGraphics] Warning: Failed to load animated texture: " + path);
			return;
		}

		height = i.Height;
		width = i.Width;
		width = width / column;
		height = height / row;
		origin = setOrigin;

		//SpriteManager::GetSingleton()->AddAnime(this);
	}

	SPAnimatedTexture::~SPAnimatedTexture(void)
	{
	}

	SPAnimatedTexture::SPAnimatedTexture(
		SPString		setFilename, 
		int			setRow, 
		int			setColumn, 
		int			setFPS, 
		D3DXVECTOR2 setOrigin )
	{
		Load( setFilename, setRow, 
			setColumn, setFPS, setOrigin);
	}

	SPAnimatedTexture::SPAnimatedTexture( 
		SPString setFilename, 
		int setRow, 
		int setColumn, 
		int setFPS )
	{
		Load(setFilename, setRow, 
			setColumn, setFPS);
	}

	SPAnimatedTexture::SPAnimatedTexture( 
		SPString setFilename, 
		int setRow, 
		int setColumn, 
		int setFrame, 
		int setFPS )
	{
		Load(setFilename, setRow, 
			setColumn, setFrame, setFPS, D3DXVECTOR2(0,0));
	}

	void SPAnimatedTexture::Update( float timeElapsed )
	{
		if (isToBeRemoved)
		{
			return;
		}

		if (isPaused)
		{
			return;
		}

		totalElapsed += timeElapsed;

		if (totalElapsed > timePerFrame)
		{
			frame++;
			// Keep the Frame between 0 and the total frames, minus one.
			frame = frame % frameCount;
			totalElapsed = 0;
		}
	}

	void SPAnimatedTexture::DrawFrame()
	{
	}

	SPRectangle SPAnimatedTexture::SourceRectangle()
	{
		if (column == 0)
		{
			return SPRectangle(0,0,0,0);
		}
		return SPRectangle(
			frame % column * width,
			frame / column * height,
			width, height);
	}

	void SPAnimatedTexture::Remove()
	{
		Stop();
		isToBeRemoved = true;
	}

	bool SPAnimatedTexture::IsToBeRemoved()
	{
		return isToBeRemoved;
	}

	bool SPAnimatedTexture::IsPause()
	{
		return isPaused;
	}

	void SPAnimatedTexture::Reset()
	{
		frame = 0;
		totalElapsed = 0.0f;
	}

	void SPAnimatedTexture::Stop()
	{
		Pause();
		Reset();
	}

	void SPAnimatedTexture::Play()
	{
		isPaused = false;
	}

	void SPAnimatedTexture::Pause()
	{
		isPaused = true;
	}

	void SPAnimatedTexture::SetRow( int setRow )
	{
		row = setRow;
	}

	void SPAnimatedTexture::SetColumn( int setCol )
	{
		column = setCol;
	}

	void SPAnimatedTexture::SetFPS( float setFPS )
	{
		timePerFrame = 1.0f / setFPS;
	}

	SPString SPAnimatedTexture::GetTextureType()
	{
		return L"AnimatedTexture";
	}

	int SPAnimatedTexture::GetRow()
	{
		return row;
	}

	int SPAnimatedTexture::GetColumn()
	{
		return column;
	}

	float SPAnimatedTexture::GetFPS()
	{
		return 1.0f / timePerFrame;
	}

}

