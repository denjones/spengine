//////////////////////////////////////////////////////////////////////////
/// @file		SPSpriteManager3D.cpp the implement file of SPSpriteManager3D class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPSpriteManager3D.h"
#include "SPGame.h"
#include "SPColorHelper.h"
#include <d3d9.h>
#include "SPVertex.h"
#include "SPDevice.h"
#include "SPConfigManager.h"

using namespace SPEngine::SPVertex;

namespace SPEngine
{
	SPSpriteManager3D::SPSpriteManager3D(void)
	{

	}

	SPSpriteManager3D::~SPSpriteManager3D()
	{
		Unload();
	}

	void SPSpriteManager3D::Initialize()
	{
	}

	void SPSpriteManager3D::Load()
	{
	}

	void SPSpriteManager3D::Unload()
	{
	}

	void SPSpriteManager3D::PreDraw()
	{
		// Sample state.
		SPDevice::GetSingleton()->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		SPDevice::GetSingleton()->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

		// Alpha render.
		// Disable lighting.
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
		SPDevice::GetSingleton()->GetD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

		// Set blend.
		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		SPDevice::GetSingleton()->GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	}

	void SPSpriteManager3D::Draw(float timeDelta)
	{
		foreach(SPSprite3D, sprite, list<SPSprite3D>, sprites)
		{
			DrawSprite(sprite);
		}
		sprites.clear();
	}

	void SPSpriteManager3D::PostDraw()
	{
	}

	void SPSpriteManager3D::DrawSprite(SPSprite3D sprite)
	{
		// Create vertex buffer.
		IDirect3DVertexBuffer9* Quad = 0;		

		SPDevice::GetSingleton()->GetD3DDevice()->CreateVertexBuffer(
			6 * sizeof(NormalTexColorVertex), 
			D3DUSAGE_WRITEONLY,
			NormalTexColorVertex::FVF,
			D3DPOOL_MANAGED,
			&Quad,
			0);		

		// Calculate half the texture width and height of the float form.
		float halfWidth, halfHeight;
		halfWidth = (float)(sprite.texture->GetWidth()) / 
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight;
		halfHeight = (float)(sprite.texture->GetHeight()) / 
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight;

		// Set vertex buffer.
		NormalTexColorVertex *v;
		Quad->Lock(0, 0, (void**)&v, 0);

		// VertexBuffer built from two triangles, note texture coordinates: 
		v[0] = NormalTexColorVertex(halfWidth, 0.0f, -halfHeight,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, sprite.color); 
		v[1] = NormalTexColorVertex(halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, sprite.color); 
		v[2] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, sprite.color); 

		v[3] = NormalTexColorVertex(halfWidth,  0.0f,-halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, sprite.color); 
		v[4] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, sprite.color); 
		v[5] = NormalTexColorVertex(-halfWidth, 0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, sprite.color); 

		Quad->Unlock();
		
		// Draw.
		SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_WORLD, &sprite.transformMatrix);
		SPDevice::GetSingleton()->GetD3DDevice()->SetTexture(0, sprite.texture->GetD3DTexture());
		SPDevice::GetSingleton()->GetD3DDevice()->SetStreamSource(0, Quad, 0, sizeof(NormalTexColorVertex));
		SPDevice::GetSingleton()->GetD3DDevice()->SetFVF(NormalTexColorVertex::FVF);

		if (sprite.effect)
		{
			sprite.effect->SetFloat("width", (float)sprite.texture->GetWidth());
			sprite.effect->SetFloat("height", (float)sprite.texture->GetHeight());
			sprite.effect->ApplyEffect();
		}
		else
		{
			SPDevice::GetSingleton()->GetD3DDevice()->SetPixelShader(NULL);
		}

		SPDevice::GetSingleton()->GetD3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		// Release vertex buffer.
		if(Quad)
		{
			Quad->Release();
			Quad = NULL;
		}
	}

	void SPSpriteManager3D::Update(float timeDelta)
	{
	}

	void SPSpriteManager3D::AddSprite3D(SPTexturePtr tex, SPEffectPtr ps)
	{
		D3DXMATRIX transformMatrix;
		D3DXMatrixTransformation(&transformMatrix, 
			NULL, NULL, NULL, NULL, NULL, NULL);

		SPSprite3D sprite(tex, ps, transformMatrix, D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0, 0, 0), SPColor::White, 
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
		sprites.push_back(sprite);
	}

	void SPSpriteManager3D::AddSprite3D(SPTexturePtr tex, SPEffectPtr ps, 
		D3DXVECTOR3 scalingCenter, D3DXQUATERNION scalingRotation,
		D3DXVECTOR3 scaling, D3DXVECTOR3 rotationCenter,
		D3DXQUATERNION rotation, D3DXVECTOR3 translation)
	{
		D3DXMATRIX transformMatrix;

		D3DXMatrixTransformation(&transformMatrix, &scalingCenter,
			&scalingRotation, &scaling, &rotationCenter,
			&rotation, &translation);

		//D3DXMatrixAffineTransformation(&transformMatrix, 1, 
		//	&rotationCenter, &rotation, &translation);

		SPSprite3D sprite(tex, ps, transformMatrix, D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0, 0, 0), SPColor::White, 
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	
		sprites.push_back(sprite);
	}

	void SPSpriteManager3D::AddSprite3D(
		SPTexturePtr setTexture, 
		SPEffectPtr ps,
		D3DXVECTOR3 scalingCenter,
		D3DXQUATERNION scalingRotation,
		D3DXVECTOR3 scaling, 
		D3DXVECTOR3 rotationCenter,
		D3DXQUATERNION rotation,
		D3DXVECTOR3 translation,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR color, 
		D3DXVECTOR3 normal, 
		D3DXVECTOR2 addressFind)
	{
		D3DXMATRIX transformMatrix;
		D3DXMatrixTransformation(&transformMatrix,
			&scalingCenter,
			&scalingRotation,
			&scaling,
			&rotationCenter,
			&rotation,
			&translation);

		SPSprite3D sprite3D(setTexture, ps,
			transformMatrix,
			position,
			center,
			color,
			normal,
			addressFind);

		sprites.push_back(sprite3D);
	}

	void SPSpriteManager3D::AddSprite3D(
		SPTexturePtr tex, 
		SPEffectPtr ps, 
		D3DXMATRIX transformMatrix)
	{
		SPSprite3D sprite3D(tex, ps, transformMatrix, D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0, 0, 0), SPColor::White, 
			D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	}

	void SPSpriteManager3D::Render(SPTexturePtr setTexture, SPEffectPtr ps)
	{
		AddSprite3D(setTexture, ps);
	}

	void SPSpriteManager3D::Render( 
		SPTexturePtr	setTexture,
		SPEffectPtr ps,
		D3DXVECTOR3		scalingCenter, 
		D3DXQUATERNION	scalingRotation,
		D3DXVECTOR3		scaling, 
		D3DXVECTOR3		rotationCenter,
		D3DXQUATERNION	rotation, 
		D3DXVECTOR3		translation)
	{
		translation.x = translation.x / 
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight * 2.0f;
		translation.y = translation.y / 
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight * 2.0f;
		translation.z = translation.z / 
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight * 2.0f;

		AddSprite3D(setTexture, ps, scalingCenter,
				scalingRotation, scaling, rotationCenter,
				rotation, translation);
	}

	void SPSpriteManager3D::RenderByPosition(
		SPTexturePtr	setTexture,
		SPEffectPtr ps,
		D3DXVECTOR3		position)
	{
		Render(
			setTexture, ps, 
			D3DXVECTOR3(0, 0, 0), 
			D3DXQUATERNION(0, 0, 0, 0),
			D3DXVECTOR3(1, 1, 1), 
			D3DXVECTOR3(0, 0, 0),
			D3DXQUATERNION(0, 0, 0, 0),
			position);
	}

	void SPSpriteManager3D::RenderByPositionWithRotateself(
		SPTexturePtr	setTexture,
		SPEffectPtr ps,
		D3DXVECTOR3		position,
		D3DXVECTOR3		rotationPoint,
		D3DXVECTOR3		rotationAxis,
		float			degree)
	{
		D3DXQUATERNION quaternion;
		float w = cos(degree / 2);
		float s = sin(degree / 2);
		quaternion.x = rotationAxis.x * s;
		quaternion.y = rotationAxis.y * s;
		quaternion.z = rotationAxis.z * s;
		quaternion.w = w;

		Render(setTexture, ps,
			D3DXVECTOR3(0, 0, 0),
			D3DXQUATERNION(0, 0, 0, 0), 
			D3DXVECTOR3(1, 1, 1), 
			rotationPoint, 
			quaternion, 
			position);
	}

	void SPSpriteManager3D::RenderWithTranformation(
		SPTexturePtr	setTexture,
		SPEffectPtr ps,
		D3DXMATRIX		transformMatrix)
	{
		AddSprite3D(setTexture, ps, transformMatrix);
	}
}