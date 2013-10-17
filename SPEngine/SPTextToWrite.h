//////////////////////////////////////////////////////////////////////////
/// @file		SPTextToWrite.h the header file of SPTextToWrite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPString.h"
#include "SPRectangle.h"
#include "SPFont.h"
#include <d3d9types.h>
#include "SPEffect.h"

using namespace std;

namespace SPEngine
{
	enum TextFormat
	{
		Center			= DT_CENTER,
		Bottom			= DT_BOTTOM,
		WithinRect		= DT_CALCRECT,
		ExpandTabs		= DT_EXPANDTABS,
		Left			= DT_LEFT,
		NoClip			= DT_NOCLIP,
		Right			= DT_RIGHT,
		RightReading	= DT_RTLREADING,
		SingleLine		= DT_SINGLELINE,
		Top				= DT_TOP,
		CenterVertical	= DT_VCENTER,
		WordBreak		= DT_WORDBREAK,
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief class SPTextToWrite to represent a 2D text.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPTextToWrite
	{
	public:
		SPFontPtr	font;
		SPEffectPtr pixelShader;
		wstring		text;
		SPRectangle desRect;
		D3DCOLOR	color;
		TextFormat	format;
		int			count;
		float		depth;
		SPTexturePtr target;
		float		wordSpace;

	public:
		SPTextToWrite(void);
		SPTextToWrite(
			SPFontPtr		setFont,
			SPEffectPtr setPS,
			wstring			setText,
			int				setCount,
			SPRectangle		setRect,
			TextFormat		setFormat,
			D3DCOLOR		setColor,
			float			setSpace,
			float			setDepth,
			SPTexturePtr	setTarget);
		virtual ~SPTextToWrite(void);
	};
}


