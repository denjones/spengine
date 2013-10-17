//////////////////////////////////////////////////////////////////////////
/// @file		SPSpriteManager3D.h the header file of SPSpriteManager3D class.
/// @author		Ken.J & BlackSky
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9core.h>
#include <list>
#include "SPSprite3D.h"
#include "SPAnimatedTexture.h"
#include "SPComponent.h"
#include "SPSingleton.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSpriteManager3D class to hold and render 3d sprites.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSpriteManager3D : 
		public SPComponent,
		public SPSingleton<SPSpriteManager3D>
	{
	public:
		list<SPSprite3D> sprites;		///< Sprites list.

	public:
		SPSpriteManager3D(void);
		virtual ~SPSpriteManager3D();

		/// @name Component methods.
		/// @{
		bool Initialize();
		bool Load();
		bool Unload();
		bool Update(float timeDelta);
		bool PreDraw();
		bool Draw(float timeDelta);
		bool PostDraw();
		/// @}

		/// @brief Add Sprite.
		bool AddSprite3D(SPTexturePtr tex, SPEffectPtr ps);
		bool AddSprite3D(
			SPTexturePtr	tex, 
			SPEffectPtr ps, 
			D3DXMATRIX		transformMatrix);
		bool AddSprite3D(
			SPTexturePtr	tex, 
			SPEffectPtr ps, 
			D3DXVECTOR3		scalingCenter, 
			D3DXQUATERNION	scalingRotation,
			D3DXVECTOR3		scaling, 
			D3DXVECTOR3		rotationCenter,
			D3DXQUATERNION	rotation, 
			D3DXVECTOR3		translation);
		bool AddSprite3D(
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		scalingCenter,
			D3DXQUATERNION	scalingRotation,
			D3DXVECTOR3		scaling,
			D3DXVECTOR3		rotationCenter,
			D3DXQUATERNION	rotation,
			D3DXVECTOR3		translation,
			D3DXVECTOR3		center,
			D3DXVECTOR3		position,
			D3DCOLOR		color,
			D3DXVECTOR3		normal,
			D3DXVECTOR2		addressFind);		

		/// @name Render methods.
		/// @{
		bool Render(SPTexturePtr setTexture, SPEffectPtr ps);
		bool Render( 
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		scalingCenter, 
			D3DXQUATERNION	scalingRotation,
			D3DXVECTOR3		scaling, 
			D3DXVECTOR3		rotationCenter,
			D3DXQUATERNION	rotation, 
			D3DXVECTOR3		translation);
		bool RenderByPosition(
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		position);
		bool RenderByPositionWithRotateself(
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		position,
			D3DXVECTOR3		rotationPoint,
			D3DXVECTOR3		rotationAxis,
			float			degree);
		bool RenderWithTranformation(			
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXMATRIX		transformMatrix);		
		/// @}

	protected:
		bool DrawSprite(SPSprite3D sprite);		
	};
}