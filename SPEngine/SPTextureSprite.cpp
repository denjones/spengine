#include "StdAfx.h"
#include "SPTextureSprite.h"
#include "SPColorHelper.h"
#include "SPConfigManager.h"
#include "SPTextureManager.h"
#include "SPDevice.h"

namespace SPEngine
{
	SPTextureSprite::SPTextureSprite(void)
	{
		texture = NULL;
		sourceRect = RECT();
		center = D3DXVECTOR3();
		position = D3DXVECTOR3();
		scalingCenter = D3DXVECTOR2(0, 0);
		scalingRotation = 0;
		scaling = D3DXVECTOR2(1, 1);
		rotationCenter = D3DXVECTOR2(0, 0);
		rotation = 0;
		translation = D3DXVECTOR2(0, 0);
		isRenderWithMatrix = false;
	}

	SPTextureSprite::SPTextureSprite( SPTexturePtr setTex, SPEffectPtr setPS, RECT setSourceRect, D3DXVECTOR3 setCenter, D3DXVECTOR3 setPos, D3DXVECTOR2 setScalingCenter, float setScalingRotation, D3DXVECTOR2 setScaling, D3DXVECTOR2 setRotationCenter, float setRotation, D3DXVECTOR2 setTranslation, D3DCOLOR setColor, SPTexturePtr setTarget )
	{
		texture = setTex;
		effect = setPS;
		sourceRect = setSourceRect;
		center = setCenter;
		position = setPos;
		scalingCenter = setScalingCenter;
		scalingRotation = setScalingRotation;
		scaling = setScaling;
		rotationCenter = setRotationCenter;
		rotation = setRotation;
		translation = setTranslation;
		color = setColor;
		renderTarget = setTarget;
		depth = position.z;
		isRenderWithMatrix = false;
	}

	SPTextureSprite::SPTextureSprite( SPTexturePtr setTex, SPEffectPtr setPS, RECT setSourceRect, D3DXVECTOR3 setCenter, D3DXVECTOR3 setPos, D3DCOLOR setColor, SPTexturePtr setTarget )
	{
		texture = setTex;
		effect = setPS;
		sourceRect = setSourceRect;
		center = setCenter;
		position = setPos;
		scalingCenter = D3DXVECTOR2(0, 0);
		scalingRotation = 0;
		scaling = D3DXVECTOR2(1, 1);
		rotationCenter = D3DXVECTOR2(0, 0);
		rotation = 0;
		translation = D3DXVECTOR2(0, 0);
		color = setColor;
		renderTarget = setTarget;
		depth = position.z;
		isRenderWithMatrix = false;
	}

	SPTextureSprite::SPTextureSprite( SPTexturePtr setTex, SPEffectPtr setPS, D3DXMATRIX setMatrix, RECT setSourceRect, D3DXVECTOR3 setCenter, D3DXVECTOR3 setPos, D3DCOLOR setColor, SPTexturePtr setTarget )
	{
		isRenderWithMatrix = true;
		texture = setTex;
		effect = setPS;
		transformMatrix = setMatrix;
		sourceRect = setSourceRect;
		center = setCenter;
		position = setPos;
		scalingCenter = D3DXVECTOR2(0, 0);
		scalingRotation = 0;
		scaling = D3DXVECTOR2(1, 1);
		rotationCenter = D3DXVECTOR2(0, 0);
		rotation = 0;
		translation = D3DXVECTOR2(0, 0);
		color = setColor;
		renderTarget = setTarget;
		depth = position.z;
		isRenderWithMatrix = true;
	}


	SPTextureSprite::~SPTextureSprite(void)
	{
	}

	D3DXMATRIX SPTextureSprite::TransformMatrix()
	{
		if (isRenderWithMatrix)
		{
			return transformMatrix;
		}

		D3DXMATRIX newTransformMatrix;
		D3DXMatrixTransformation2D(&newTransformMatrix, &scalingCenter,
			scalingRotation, &scaling, &rotationCenter,
			rotation, &translation);

		return newTransformMatrix;
	}

	bool SPTextureSprite::Draw( ID3DXSprite* renderer,ID3DXSprite* innerRenderer, LPDIRECT3DSURFACE9 pRenderSurface, ID3DXRenderToSurface* renderToSurface)
	{
		HRESULT hr = S_FALSE;

		// Apply effect.
		if (effect && effect->GetCore())
		{
			// Get pass num.
			UINT nPass = 1;

			// Set effect.
			effect->SetFloat("width", (float)texture->GetWidth());
			effect->SetFloat("height", (float)texture->GetHeight());
			D3DVIEWPORT9 viewPort;
			SPDevice::GetSingleton()->GetD3DDevice()->GetViewport(&viewPort);
			D3DXMATRIX transfromation;
			D3DXMatrixOrthoOffCenterLH(&transfromation, 0, viewPort.Width,
				viewPort.Height, 0, 0, 1);
			D3DXMATRIX translation;
			D3DXMatrixTranslation(&translation, -0.5, -0.5, 0);
			effect->SetMatrix("MatrixTransform", translation * transfromation);
			effect->ApplyEffect();
			effect->GetCore()->GetEffect()->Begin(&nPass, D3DXFX_DONOTSAVESAMPLERSTATE);

			if (nPass == 1)
			{
				hr = effect->GetCore()->GetEffect()->BeginPass(0);

				// Render
				renderer->SetTransform(&TransformMatrix());
				renderer->Draw(	texture->GetD3DTexture(), &sourceRect, &center,	&position, color );
				renderer->Flush();

				hr = effect->GetCore()->GetEffect()->EndPass();							
				hr = effect->GetCore()->GetEffect()->End();
			}
			else if (nPass > 1)
			{
				// End current scene.
				effect->GetCore()->GetEffect()->End();

				hr = renderer->End();
				if (renderToSurface)
				{
					hr = renderToSurface->EndScene(0);
				}
				else
				{
					hr = SPDevice::GetSingleton()->GetD3DDevice()->EndScene();
				}

				// Loop through passes.
				// Old -pass-> New -> Old
				SPTexturePtr oldTarget = texture;
				SPTexturePtr newTarget;
				for (int num = 0; num < (int)nPass; num++)
				{								
					LPDIRECT3DSURFACE9 innerSurface = NULL;
					ID3DXRenderToSurface* innerRenderToSurface = NULL;

					// Create render target and surface.
					newTarget = SPTextureManager::GetSingleton()->CreateRenderTarget(
						texture->GetWidth(),
						texture->GetHeight(),
						0x00000000);
					hr = newTarget->GetD3DTexture()->GetSurfaceLevel(0, &innerSurface);

					// Create render to surface.
					D3DSURFACE_DESC desc;
					hr = innerSurface->GetDesc( &desc );
					hr = D3DXCreateRenderToSurface(
						SPDevice::GetSingleton()->GetD3DDevice(), 
						desc.Width, 
						desc.Height,
						desc.Format,
						FALSE, 
						D3DFMT_D24S8,
						&innerRenderToSurface);

					// Begin rendering.
					hr = innerRenderToSurface->BeginScene(innerSurface, NULL);	

					hr = SPDevice::GetSingleton()->GetD3DDevice()->BeginScene();

					SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, 0, D3DCLEAR_TARGET, newTarget->GetBackgroundColor(), 1.0f, 0); 

					// Render with effect pass.	
					hr = innerRenderer->Begin( D3DXSPRITE_DONOTSAVESTATE );

					// Set effect.
					effect->SetFloat("width", (float)texture->GetWidth());
					effect->SetFloat("height", (float)texture->GetHeight());
					D3DVIEWPORT9 viewPort;
					SPDevice::GetSingleton()->GetD3DDevice()->GetViewport(&viewPort);
					D3DXMATRIX transfromation;
					D3DXMatrixOrthoOffCenterLH(&transfromation, 0, viewPort.Width,
						viewPort.Height, 0, 0, 1);
					D3DXMATRIX translation;
					D3DXMatrixTranslation(&translation, -0.5, -0.5, 0);
					effect->SetMatrix("MatrixTransform", translation * transfromation);
					effect->ApplyEffect();

					// Begin effect pass.
					hr = effect->GetCore()->GetEffect()->Begin(&nPass, D3DXFX_DONOTSAVESTATE);																				
					hr = effect->GetCore()->GetEffect()->BeginPass(num);

					// Draw.
					hr = innerRenderer->Draw(oldTarget->GetD3DTexture(), 0, 0, 0, SPColor::White );
					hr = innerRenderer->Flush();

					// End pass.
					hr = effect->GetCore()->GetEffect()->EndPass();							
					hr = effect->GetCore()->GetEffect()->End();

					hr = innerRenderer->End();

					// End rendering.
					hr = innerRenderToSurface->EndScene(0);	

					// Release surface and target.
					hr = innerRenderToSurface->Release();
					hr = innerSurface->Release();

					innerRenderToSurface = NULL;
					innerSurface = NULL;							

					oldTarget = newTarget;
					newTarget = NULL;
				}

				// Restart scene.
				if (renderToSurface)
				{
					hr = renderToSurface->BeginScene(pRenderSurface, NULL);
				}
				else
				{
					hr = SPDevice::GetSingleton()->GetD3DDevice()->BeginScene();
				}

				hr = renderer->Begin( D3DXSPRITE_DONOTSAVESTATE );

				// Draw the resulting texture.
				renderer->SetTransform(&TransformMatrix());
				renderer->Draw(
					oldTarget->GetD3DTexture(),
					&sourceRect,
					&center,
					&position, 
					color );
				renderer->Flush();
			}
		}
		else
		{

			// Render
			renderer->SetTransform(&TransformMatrix());
			renderer->Draw(	texture->GetD3DTexture(), &sourceRect, &center,	&position, color );
			renderer->Flush();
		}	

		return true;
	}


}

