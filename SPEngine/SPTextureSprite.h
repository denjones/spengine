#pragma once
#include "SPSprite.h"

namespace SPEngine
{
	class SPTextureSprite : public SPSprite
	{
	public:
		RECT		sourceRect;
		D3DXVECTOR3 center;
		D3DXVECTOR3 position;
		D3DXVECTOR2 scalingCenter;
		float		scalingRotation;
		D3DXVECTOR2 scaling;
		D3DXVECTOR2 rotationCenter;
		float		rotation;
		D3DXVECTOR2 translation;
		D3DXMATRIX  transformMatrix;
		bool		isRenderWithMatrix;
	public:
		SPTextureSprite(void);
		SPTextureSprite(
			SPTexturePtr setTex,
			SPEffectPtr setPS, 
			D3DXMATRIX  setMatrix, 
			RECT		setSourceRect, 
			D3DXVECTOR3 setCenter, 
			D3DXVECTOR3 setPos, 
			D3DCOLOR	setColor, 
			SPTexturePtr setTarget );
		SPTextureSprite(
			SPTexturePtr setTex,
			SPEffectPtr setPS, 
			RECT		setSourceRect,
			D3DXVECTOR3 setCenter,
			D3DXVECTOR3 setPos,
			D3DXVECTOR2 setScalingCenter,
			float		setScalingRotation,
			D3DXVECTOR2 setScaling,
			D3DXVECTOR2 setRotationCenter,
			float		setRotation,
			D3DXVECTOR2 setTranslation,
			D3DCOLOR	setColor, 
			SPTexturePtr setTarget );
		SPTextureSprite(
			SPTexturePtr setTex,
			SPEffectPtr setPS, 
			RECT		setSourceRect,
			D3DXVECTOR3 setCenter,
			D3DXVECTOR3 setPos,
			D3DCOLOR	setColor, 
			SPTexturePtr setTarget);
		virtual ~SPTextureSprite(void);

		D3DXMATRIX TransformMatrix();

		virtual bool Draw( ID3DXSprite* renderer,ID3DXSprite* innerRenderer, LPDIRECT3DSURFACE9 pRenderSurface, ID3DXRenderToSurface* renderToSurface );

	};

	typedef SPPointer<SPTextureSprite> SPTextureSpritePtr;
}