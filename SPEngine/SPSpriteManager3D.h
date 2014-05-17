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
		void Initialize();
		void Load();
		void Unload();
		void Update(float timeDelta);
		void PreDraw();
		void Draw(float timeDelta);
		void PostDraw();
		/// @}

		/// @brief Add Sprite.
		void AddSprite3D(SPTexturePtr tex, SPEffectPtr ps);
		void AddSprite3D(
			SPTexturePtr	tex, 
			SPEffectPtr ps, 
			D3DXMATRIX		transformMatrix);
		void AddSprite3D(
			SPTexturePtr	tex, 
			SPEffectPtr ps, 
			D3DXVECTOR3		scalingCenter, 
			D3DXQUATERNION	scalingRotation,
			D3DXVECTOR3		scaling, 
			D3DXVECTOR3		rotationCenter,
			D3DXQUATERNION	rotation, 
			D3DXVECTOR3		translation);
		void AddSprite3D(
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
		void Render(SPTexturePtr setTexture, SPEffectPtr ps);
		void Render( 
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		scalingCenter, 
			D3DXQUATERNION	scalingRotation,
			D3DXVECTOR3		scaling, 
			D3DXVECTOR3		rotationCenter,
			D3DXQUATERNION	rotation, 
			D3DXVECTOR3		translation);
		void RenderByPosition(
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		position);
		void RenderByPositionWithRotateself(
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXVECTOR3		position,
			D3DXVECTOR3		rotationPoint,
			D3DXVECTOR3		rotationAxis,
			float			degree);
		void RenderWithTranformation(			
			SPTexturePtr	setTexture,
			SPEffectPtr ps, 
			D3DXMATRIX		transformMatrix);		
		/// @}

	protected:
		void DrawSprite(SPSprite3D sprite);		
	};
}