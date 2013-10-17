#pragma once
#include "SPSprite.h"
#include "SPFont.h"
#include "SPEffect.h"
#include "SPRectangle.h"
#include "SPTextToWrite.h"

namespace SPEngine
{
	class SPTextSprite : public SPSprite
	{
		SPFontPtr	font;
		SPString	text;
		SPRectangle desRect;
		TextFormat	format;
		int			count;
		float		wordSpace;
	public:
		SPTextSprite(void);
		SPTextSprite(
			SPFontPtr		setFont,
			SPEffectPtr		setPS,
			wstring			setText,
			int				setCount,
			SPRectangle		setRect,
			TextFormat		setFormat,
			D3DCOLOR		setColor,
			float			setSpace,
			float			setDepth,
			SPTexturePtr	setTarget);
		virtual ~SPTextSprite(void);

		bool DrawText(ID3DXSprite* renderer);
		virtual bool Draw( ID3DXSprite* renderer,ID3DXSprite* innerRenderer, LPDIRECT3DSURFACE9 pRenderSurface, ID3DXRenderToSurface* renderToSurface );

	};
}