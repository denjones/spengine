//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite.h the header file of SPSprite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"
#include "SPEffect.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPSprite to represent a 2D sprite.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPSprite
	{
	public:
		SPTexturePtr	texture;
		SPEffectPtr		effect;
		D3DCOLOR		color; 
		SPTexturePtr	renderTarget;
		float			depth;

	public:
		SPSprite(void);
		virtual ~SPSprite(void);

		virtual bool Draw( ID3DXSprite* renderer,ID3DXSprite* innerRenderer, LPDIRECT3DSURFACE9 pRenderSurface, ID3DXRenderToSurface* renderToSurface ) = 0;
	};

	typedef SPPointer<SPSprite> SPSpritePtr;
}


