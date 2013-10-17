//////////////////////////////////////////////////////////////////////////
/// @file		SPFontWriter.h the header file of SPFontWriter class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTextToWrite.h"
#include "SPComponent.h"
#include "SPSingleton.h"
#include <list>

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPFontWriter to write text with font.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPFontWriter :
		public SPComponent,
		public SPSingleton<SPFontWriter>
	{
		list<SPTextToWrite> texts;		///< Texts list.
		LPD3DXSPRITE renderer;			///< Inner Renderer.
		SPFontPtr defaultFont;

	public:
		SPFontWriter(void);
		virtual ~SPFontWriter(void);

		/// @name Component methods
		/// @{
		bool Load();
		bool Unload();
		bool Draw(float timeDelta);
		bool Initialize();
		/// @}

	protected:
		/// @name Inner render function.
		/// @{
		bool WriteText( SPTextToWrite text );
		bool RealWriteText(SPTextToWrite text);
		bool AddTextToWrite(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			int			count,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		/// @}

	public:
		/// @name Public write methods
		/// @{
		bool Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			D3DXVECTOR2 position,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		bool Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		bool Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		bool Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			int			count,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);

		bool WriteCentered(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			D3DXVECTOR2 position,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		bool WriteCentered(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		bool WriteCentered(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			int			count,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		/// @}
	};
}


