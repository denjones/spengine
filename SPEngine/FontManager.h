#pragma once
#include <list>
#include <d3dx9core.h>
#include "SPFont.h"
#include <vector>
#include "TextToWrite.h"
#include "SPComponent.h"

using namespace std;

namespace SPEngine
{
	class SPGame;

	class FontManager : public SPComponent
	{		
		vector<SPFont*> fonts;
		list<TextToWrite> texts;

	public:
		LPD3DXSPRITE Renderer;

	public:
		FontManager(void);
		FontManager(SPGame* game);
		~FontManager(void);

		bool Update(float timeDelte);
		bool Draw(float timeDelte);

		bool Initialize();
		bool AddFont(SPFont* font);
		bool AddFont(
			INT		Height,
			UINT	Width,
			UINT	Weight, 
			UINT	MipLevels,
			BOOL	Italic, 
			DWORD	CharSet,
			DWORD	OutputPrecision,
			DWORD	Quality,
			DWORD	PitchAndFamily,
			LPCSTR	pFaceName);

		bool AddTextToWrite(
			SPFont*		font,
			string		text,
			int			count,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color);

		SPFont* GetFont(int num);

		LPDIRECT3DDEVICE9 GetDevice();

		bool Load();
		bool Unload();


	private:
		bool WriteText(TextToWrite text);		
	};
}


