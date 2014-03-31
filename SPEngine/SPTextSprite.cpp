#include "StdAfx.h"
#include "SPTextSprite.h"
#include "SPFontManager.h"
#include "SPDevice.h"
#include "SPTextureManager.h"

namespace SPEngine
{
	SPTextSprite::SPTextSprite(void)
	{
		font = NULL;
		effect = NULL;
		text = L"";
		desRect = SPRectangle();
		format = Center;
		count = 0;
		wordSpace = 0;
	}

	SPTextSprite::SPTextSprite( SPFontPtr setFont, SPEffectPtr setPS, wstring setText, int setCount, SPRectangle setRect, TextFormat setFormat, D3DCOLOR setColor, float setSpace, float setDepth, SPTexturePtr setTarget )
	{
		font = setFont;
		effect = setPS;
		text = setText;
		count = setCount;
		desRect = setRect;
		format = setFormat;
		color = setColor;
		wordSpace = setSpace;
		depth = setDepth;
		renderTarget = setTarget;
	}


	SPTextSprite::~SPTextSprite(void)
	{
	}

	bool SPTextSprite::Draw( ID3DXSprite* renderer,ID3DXSprite* innerRenderer, LPDIRECT3DSURFACE9 pRenderSurface, ID3DXRenderToSurface* renderToSurface )
	{		
		HRESULT hr;

		float sizeRate = SPFontManager::GetSingleton()->GetSizeRate();
		float marginRate = SPFontManager::GetSingleton()->GetMarginRate();

		// Apply effect.
		if (effect && effect->GetCore())
		{
			// Get pass num.
			UINT nPass = 1;

			float width = sizeRate * desRect.Width + 2 * sizeRate * font->GetHeight() * marginRate;
			float height = sizeRate * desRect.Height + 2 * sizeRate *  font->GetHeight() * marginRate;

			// Set effect.
			effect->SetFloat("width", 100);
			effect->SetFloat("height", 100);
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
				DrawText(renderer);

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

				SPTexturePtr oldTarget = texture;
				SPTexturePtr newTarget;

				// Create render target and surface.
				LPDIRECT3DSURFACE9 innerSurface = NULL;
				ID3DXRenderToSurface* innerRenderToSurface = NULL;

				oldTarget = SPTextureManager::GetSingleton()->
					CreateRenderTarget(
					sizeRate * desRect.Width + 2 * sizeRate * font->GetHeight() * marginRate,
					sizeRate * desRect.Height + 2 * sizeRate *  font->GetHeight() * marginRate,
					SPColorHelper::AlphaColor(0, color));
				hr = oldTarget->GetD3DTexture()->GetSurfaceLevel(0, &innerSurface);

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
				SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, SPColorHelper::AlphaColor(0, color), 1.0, 0);

				// Render with effect pass.	
				hr = renderer->Begin( D3DXSPRITE_ALPHABLEND	
					| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
					| D3DXSPRITE_SORT_TEXTURE);	

				SPRectangle targetRect = desRect;

				if (text.size() == 1 || wordSpace == 0)
				{
					SPRectangle targetRect = desRect;
					targetRect.X = sizeRate * font->GetHeight() * marginRate;
					targetRect.Y = sizeRate * font->GetHeight() * marginRate;
					targetRect.Width *= sizeRate;
					targetRect.Height *=  sizeRate;

					hr = font->GetD3DXFont()->DrawTextW(
						renderer,
						text.c_str(),
						count,
						&targetRect.CRect(),
						format,
						color);
				}	
				else
				{
					SPRectangle targetRect = desRect;			
					targetRect.X = sizeRate * font->GetHeight() * marginRate;
					targetRect.Y = sizeRate * font->GetHeight() * marginRate;

					for (int num = 0; num < (int)text.size(); num++)
					{
						if (text[num] == L'\n')
						{
							targetRect.Y += font->GetHeight();
							targetRect.X = sizeRate * font->GetHeight() * marginRate;
							continue;
						}

						D3DXVECTOR2 wordSize = font->GetTextSize(wstring(&text[num], 1), NULL, 0);		

						if (text[num] == L' ')
						{
							wordSize.x = font->GetTextSize(L"a a", NULL, 0).x - font->GetTextSize(L"aa", NULL, 0).x;
							wordSize.y = font->GetHeight();
						}

						targetRect.Width = wordSize.x * sizeRate;
						targetRect.Height = wordSize.y * sizeRate;

						hr = font->GetD3DXFont()->DrawTextW(
							renderer,
							wstring(&text[num], 1).c_str(),
							count,
							&targetRect.CRect(),
							format,
							color);

						targetRect.X += (wordSize.x + wordSpace * font->GetHeight()) * sizeRate;
					}
				}

				hr = renderer->End();

				// End rendering.
				hr = innerRenderToSurface->EndScene(0);	

				// Release surface and target.
				hr = innerRenderToSurface->Release();
				hr = innerSurface->Release();

				innerRenderToSurface = NULL;
				innerSurface = NULL;			

				// Loop through passes.
				// Old -pass-> New -> Old
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
				SPRectangle desRect = desRect;
				desRect.X -= font->GetHeight() * marginRate;
				desRect.Y -= font->GetHeight() * marginRate;
				desRect.Width += 2 * font->GetHeight() * marginRate;
				desRect.Height += 2 * font->GetHeight() * marginRate;

				D3DXMATRIX transformMatrix;
				D3DXMatrixTransformation2D(&transformMatrix, NULL,
					0, NULL, NULL,
					0, &D3DXVECTOR2(desRect.X,desRect.Y));

				renderer->SetTransform(&transformMatrix);
				renderer->Draw(
					oldTarget->GetD3DTexture(),
					NULL,
					NULL,
					NULL, 
					SPColor::White );
				renderer->Flush();
			}
		}
		else
		{
			// Render
			DrawText(renderer);
		}	

		return true;
	}

	bool SPTextSprite::DrawText(ID3DXSprite* renderer)
	{
		HRESULT hr;

		float sizeRate = SPFontManager::GetSingleton()->GetSizeRate();
		float marginRate = SPFontManager::GetSingleton()->GetMarginRate();

		if (text.size() == 1 || wordSpace == 0)
		{
			SPRectangle targetRect = desRect;
			//targetRect.X += sizeRate * font->GetHeight() * marginRate;
			//targetRect.Y += sizeRate * font->GetHeight() * marginRate;
			//targetRect.Width *= sizeRate;
			//targetRect.Height *=  sizeRate;

			hr = font->GetD3DXFont()->DrawTextW(
				renderer,
				text.c_str(),
				count,
				&targetRect.CRect(),
				format,
				color);
		}	
		else
		{
			SPRectangle targetRect = desRect;			
			//targetRect.X += sizeRate * font->GetHeight() * marginRate;
			//targetRect.Y += sizeRate * font->GetHeight() * marginRate;

			for (int num = 0; num < (int)text.size(); num++)
			{
				if (text[num] == L'\n')
				{
					targetRect.Y += font->GetHeight();
					//targetRect.X = desRect.X + sizeRate * font->GetHeight() * marginRate;
					continue;
				}

				D3DXVECTOR2 wordSize = font->GetTextSize(wstring(&text[num], 1), NULL, 0);		

				if (text[num] == L' ')
				{
					wordSize.x = font->GetTextSize(L"a a", NULL, 0).x - font->GetTextSize(L"aa", NULL, 0).x;
					wordSize.y = font->GetHeight();
				}

				//targetRect.Width = wordSize.x * sizeRate;
				//targetRect.Height = wordSize.y * sizeRate;

				hr = font->GetD3DXFont()->DrawTextW(
					renderer,
					wstring(&text[num], 1).c_str(),
					count,
					&targetRect.CRect(),
					format,
					color);

				targetRect.X += (wordSize.x + wordSpace * font->GetHeight());// * sizeRate;
			}
		}	

		return true;
	}


}

