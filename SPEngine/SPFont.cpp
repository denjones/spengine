//////////////////////////////////////////////////////////////////////////
/// @file		SPFont.cpp the implement file of SPFont class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPFont.h"
#include "SPFontManager.h"
#include "SPGame.h"
#include <xutility>
#include "SPDevice.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPFontHelper.h"
#include "SPGameManager.h"

namespace SPEngine
{
	SPFont::~SPFont(void)
	{
		Unload();
	}

	bool SPFont::Load(
		int		Height,
		int		Width,
		int		Weight, 
		int		MipLevels,
		bool	Italic,
		SPString	Name)
	{
		return Load(Height, Width, Weight, 
			MipLevels, Italic, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, 
			10, DEFAULT_PITCH | FF_DONTCARE, Name);
	}

	int CALLBACK EnumFontsProc(LOGFONT* lplf, TEXTMETRIC* lptm, DWORD dwType,	LPARAM lpData)
	{
		return 1;
	}

	bool SPFont::Load( 
		INT			Height, 
		UINT		Width, 
		UINT		Weight, 
		UINT		MipLevels, 
		BOOL		Italic, 
		DWORD		CharSet, 
		DWORD		OutputPrecision, 
		DWORD		Quality, 
		DWORD		PitchAndFamily, 
		SPString	FontName )
	{
		unloaded = true;
		float rate = SPFontManager::GetSingleton().GetSizeRate();

		if (FAILED(D3DXCreateFont(
			SPDevice::GetSingleton().GetD3DDevice(),
			Height * rate , Width * rate, Weight, MipLevels, Italic, 
			CharSet, OutputPrecision, Quality,
			PitchAndFamily, FontName.c_str(), &font)))
		{		
			return false;
		}

	
		//D3DXFONT_DESCA des;
		//Font->GetDescA(&des);

		width = Width;
		height = Height;
		weight = Weight;
		italic = Italic == TRUE;
		miplevel = MipLevels;
		name = FontName;
		unloaded = false;

		return true;
	}

	int SPFont::GetWidth()
	{
		return width;
	}

	int SPFont::GetHeight()
	{
		return height;
	}

	bool SPFont::Unload()
	{
		if (font)
		{
			unloaded = true;
			font->Release();
			font = NULL;
		}

		return true;
	}

	SPFont::SPFont( 
		int Height, 
		int Width, 
		int Weight, 
		int MipLevels, 
		bool Italic, 
		SPString pFaceName )
	{
		Load(Height, Width, Weight, MipLevels, Italic, pFaceName);
	}

	bool SPFont::Reload()
	{
		return Load(height, width, weight, 
			miplevel, italic, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, 
			10, DEFAULT_PITCH | FF_DONTCARE, name.c_str());
	}

	D3DXVECTOR2 SPFont::GetTextSize( wstring text, float spaceRate )
	{
		float rate = SPFontManager::GetSingleton().GetSizeRate();
		RECT rect = {0,0,0,0};

		while(unloaded)
		{
			if (SPGameManager::GetSingleton().GetGame()->IsExiting())
			{
				throw exception("Use Font With Game Exited!");
			}

			Sleep(1);
		}

		font->DrawTextW(NULL, text.c_str(), -1, &rect, DT_CALCRECT, 0 );

		D3DXVECTOR2 size((float)(rect.right - rect.left + (height * spaceRate) * ( text.size() - 1 )) / rate, (float)(rect.bottom - rect.top) / rate);

		return size;
	}

	D3DXVECTOR2 SPFont::GetTextSize( wstring text, DWORD format, float spaceRate )
	{
		float rate = SPFontManager::GetSingleton().GetSizeRate();
		RECT rect = {0,0,0,0};

		while(unloaded)
		{
			Sleep(1);
		}

		font->DrawTextW(NULL, text.c_str(), -1, &rect, format | DT_CALCRECT, 0 );

		D3DXVECTOR2 size((float)(rect.right - rect.left  + height * spaceRate * ( text.size() - 1 )) / rate, (float)(rect.bottom - rect.top) / rate);

		return size;
	}
}