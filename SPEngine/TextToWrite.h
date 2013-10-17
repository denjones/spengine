#pragma once
#include <string>
#include "SPRectangle.h"
#include "SPFont.h"
#include <d3d9types.h>

using namespace std;

namespace SPEngine
{
	enum TextFormat
	{
		Center		= DT_CENTER,
		Bottom		= DT_BOTTOM,
		WithinRect	= DT_CALCRECT,
		ExpandTabs	= DT_EXPANDTABS,
		Left		= DT_LEFT,
		NoClip		= DT_NOCLIP,
		Right		= DT_RIGHT,
		RightReading = DT_RTLREADING,
		SingleLine	= DT_SINGLELINE,
		Top			= DT_TOP,
		CenterVertical = DT_VCENTER,
		WordBreak	= DT_WORDBREAK,
	};

	class TextToWrite
	{
	public:
		SPFont*	font;
		string		text;
		SPRectangle desRect;
		D3DCOLOR	color;
		TextFormat	format;
		int			count;
	public:
		TextToWrite(void);
		TextToWrite(
			SPFont*,
			string,
			int,
			SPRectangle,
			TextFormat,
			D3DCOLOR);
		~TextToWrite(void);
	};
}


