//////////////////////////////////////////////////////////////////////////
/// @file		SPFont.h the header file of SPFont class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9core.h>
#include "SPString.h"
#include "SPRectangle.h"
#include "SPPointer.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFont class to represent a D3DXFont.
	///
	//////////////////////////////////////////////////////////////////////
	class SPFont
	{
		/// @name Properties variables.
		/// @{
		int		width;
		int		height;
		int		weight;
		bool	italic;
		int		miplevel;
		SPString	name;
		/// @}

		LPD3DXFONT font;	///< Inner D3DXFont.

	public:
		const LPD3DXFONT GetD3DXFont() { return font; }
		int GetWidth();
		int GetHeight();
		D3DXVECTOR2 GetTextSize(wstring text, float spaceRate);
		D3DXVECTOR2 GetTextSize(wstring text, DWORD format, float spaceRate);
		SPString GetFontName() {return name;}
		bool GetItalic() { return italic; }
		int GetWeight() { return weight; }
		int GetMipLevel() { return miplevel; }

	public:
		SPFont(
			int		Height,
			int		Width,
			int		Weight,
			int		MipLevels,
			bool	Italic,
			SPString	pFaceName);
		virtual ~SPFont(void);

		/// @name Load methods
		/// @{
		bool Load(
			int		Height,
			int		Width,
			int		Weight, 
			int		MipLevels,
			bool	Italic,
			SPString	pFaceName);

		bool Load(
			INT		Height,
			UINT	Width,
			UINT	Weight, 
			UINT	MipLevels,
			BOOL	Italic, 
			DWORD	CharSet,
			DWORD	OutputPrecision,
			DWORD	Quality,
			DWORD	PitchAndFamily,
			SPString	pFaceName);

		bool Reload();

		bool Unload();
		/// @}
	};

	typedef SPPointer<SPFont> SPFontPtr;
}