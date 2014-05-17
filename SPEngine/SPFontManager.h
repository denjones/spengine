//////////////////////////////////////////////////////////////////////////
/// @file		SPFontManager.h the header file of SPFontManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <list>
#include <d3dx9core.h>
#include "SPFont.h"
#include <vector>
#include "SPTextToWrite.h"
#include "SPComponent.h"
#include "SPSingleton.h"
#include "SPStringMap.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFontManager class to hold and manage fonts.
	///
	//////////////////////////////////////////////////////////////////////
	class SPFontManager : 
		public SPComponent,
		public SPSingleton<SPFontManager>
	{		
		SPWStringMap<SPFontPtr> fonts;		///< Fonts list.
		float				sizeRate;
		float				marginRate;
		vector<HANDLE>		extendedFont;
		vector<SPString>	extendedFontPath;

	public:
		float GetSizeRate();
		void SetSizeRate(float setRate);
		float GetMarginRate();
		void SetMarginRate(float setRate);

	public:
		SPFontManager(void);
		virtual ~SPFontManager(void);

		/// @name Component methods
		/// @{
		void Initialize();
		void Reload();
		void Unload();
		/// @}

		/// @brief Add a Font
		SPFontPtr AddFont(SPString name, SPFontPtr font);
		SPFontPtr AddFont(
			INT		Height,
			UINT	Width,
			UINT	Weight, 
			UINT	MipLevels,
			BOOL	Italic, 
			SPString	pFaceName);

		/// @brief Create a font
		SPFontPtr CreateFont(
			SPString	name,
			int		Height,
			int		Width,
			int		Weight, 
			int		MipLevels,
			bool	Italic,
			SPString	pFaceName);

		void AddExtendedFont(SPString path);

		SPFontPtr GetFont(SPString name);
		void SetUpFont(wstring path);

		virtual void LoadFromString(SPString stringStream);
		virtual SPString SaveAsString();
	};
}


