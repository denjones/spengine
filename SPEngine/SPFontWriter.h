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
		void Load();
		void Unload();
		void Draw(float timeDelta);
		void Initialize();
		/// @}

	protected:
		/// @name Inner render function.
		/// @{
		void WriteText( SPTextToWrite text );
		void RealWriteText(SPTextToWrite text);
		void AddTextToWrite(
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
		void Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			D3DXVECTOR2 position,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		void Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		void Write(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			TextFormat	format,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		void Write(
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

		void WriteCentered(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			D3DXVECTOR2 position,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		void WriteCentered(
			SPFontPtr	font,
			SPEffectPtr ps,
			wstring		text,
			SPRectangle destRect,
			D3DCOLOR	color,
			float		space,
			float		depth,
			SPTexturePtr target);
		void WriteCentered(
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


