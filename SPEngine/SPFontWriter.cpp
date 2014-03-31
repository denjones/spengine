//////////////////////////////////////////////////////////////////////////
/// @file		SPFontWriter.cpp the implement file of SPFontWriter class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPFontWriter.h"
#include "SPDevice.h"
#include "SPLogHelper.h"
#include "SPTextureManager.h"
#include "SPColorHelper.h"
#include "SPSpriteManager.h"
#include "SPFontManager.h"
#include "SPTextSprite.h"

namespace SPEngine
{
	SPFontWriter::SPFontWriter(void)
	{
		defaultFont = SPFontManager::GetSingleton()->CreateFont(L"default", 20, 0, FW_NORMAL, 10, false, L"default");
		renderer = NULL;
	}


	SPFontWriter::~SPFontWriter(void)
	{
	}

	bool SPFontWriter::Load()
	{
		if (!renderer)
		{
			if(FAILED(D3DXCreateSprite(SPDevice::GetSingleton()->GetD3DDevice(), &renderer)))
			{
				SPLogHelper::WriteLog("[Game] WARNING£ºFailed to create SpriteRenderer in SPFontWriter!");
				return false;
			}
		}		

		return true;
	}

	bool SPFontWriter::Unload()
	{
		if (!renderer)
		{
			SPLogHelper::WriteLog("[Game] WARNING£ºTrying to release empty renderer in SPFontWriter!");
			return false;			
		}

		renderer->Release();
		renderer = NULL;

		return true;
	}

	bool SPFontWriter::Draw( float timeDelta )
	{	
		foreach(SPTextToWrite, text, list<SPTextToWrite>, texts)
		{
			WriteText(text);
		}

		texts.clear();

		return true;
	}

	bool SPFontWriter::WriteText( SPTextToWrite text )
	{
		float sizeRate = SPFontManager::GetSingleton()->GetSizeRate();
		float marginRate = SPFontManager::GetSingleton()->GetMarginRate();

		HRESULT hr;

		hr = SPDevice::GetSingleton()->GetD3DDevice()->EndScene();

		ID3DXRenderToSurface* renderToSurface = NULL;
		LPDIRECT3DSURFACE9 pRenderSurface = NULL;

		if (!text.font)
		{
			text.font = defaultFont;
		}

		SPTexturePtr tex = SPTextureManager::GetSingleton()->CreateRenderTarget(
			sizeRate * text.desRect.Width + 2 * sizeRate * text.font->GetHeight() * marginRate,
			sizeRate * text.desRect.Height + 2 * sizeRate *  text.font->GetHeight() * marginRate,
			SPColorHelper::AlphaColor(0, text.color));
		hr = tex->GetD3DTexture()->GetSurfaceLevel(0, &pRenderSurface);

		D3DSURFACE_DESC desc;
		hr = pRenderSurface->GetDesc( &desc );

		hr = D3DXCreateRenderToSurface(
			SPDevice::GetSingleton()->GetD3DDevice(), 
			desc.Width, 
			desc.Height,
			desc.Format,
			FALSE, 
			D3DFMT_D24S8,
			&renderToSurface);

		hr = renderToSurface->BeginScene(pRenderSurface, NULL);

		SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, SPColorHelper::AlphaColor(0,text.color), 1.0, 0);

		hr = renderer->Begin(D3DXSPRITE_ALPHABLEND);// | D3DXSPRITE_DONOTMODIFY_RENDERSTATE);
		
		// Apply effect.
		if (text.pixelShader && text.pixelShader->GetCore())
		{
			//
			// End Scene
			//
			renderer->End();
			renderToSurface->EndScene(0);

			// Loop through passes.
			// Old -pass-> New -> Old
			SPTexturePtr oldTarget;
			SPTexturePtr newTarget;

			//
			// Create first old target.
			//

			// Create render target and surface.
			LPDIRECT3DSURFACE9 innerSurface = NULL;
			ID3DXRenderToSurface* innerRenderToSurface = NULL;

			oldTarget = SPTextureManager::GetSingleton()->
				CreateRenderTarget(tex->GetWidth(),
				tex->GetHeight(), SPColorHelper::AlphaColor(0,text.color));
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
			SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, SPColorHelper::AlphaColor(0,text.color), 1.0, 0);

			// Render with effect pass.	
			hr = renderer->Begin( D3DXSPRITE_ALPHABLEND	
				| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
				| D3DXSPRITE_SORT_TEXTURE);	

			RealWriteText(text);

			hr = renderer->End();

			// End rendering.
			hr = innerRenderToSurface->EndScene(0);	

			// Release surface and target.
			hr = innerRenderToSurface->Release();
			hr = innerSurface->Release();

			innerRenderToSurface = NULL;
			innerSurface = NULL;							

			//
			// Get pass num.
			//

			UINT nPass = 1;


			//
			// Loop through all passes.
			//

			for (int num = 0; num < (int)nPass; num++)
			{								
				LPDIRECT3DSURFACE9 innerSurface = NULL;
				ID3DXRenderToSurface* innerRenderToSurface = NULL;
				
				if (num != nPass - 1)
				{
					// Create render target and surface.
					newTarget = SPTextureManager::GetSingleton()->
						CreateRenderTarget(tex->GetWidth(),
						tex->GetHeight(), SPColorHelper::AlphaColor(0, text.color));
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
				}
				else
				{
					hr = renderToSurface->BeginScene(pRenderSurface, NULL);
				}
				
				SPDevice::GetSingleton()->GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, SPColorHelper::AlphaColor(0,text.color), 1.0, 0);

				// Render with effect pass.	
				hr = renderer->Begin( D3DXSPRITE_ALPHABLEND	
					| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
					| D3DXSPRITE_SORT_TEXTURE);PreDraw();	

				// Set effect.
				text.pixelShader->SetFloat("width", (float)tex->GetWidth());
				text.pixelShader->SetFloat("height", (float)tex->GetHeight());
				D3DVIEWPORT9 viewPort;
				SPDevice::GetSingleton()->GetD3DDevice()->GetViewport(&viewPort);
				D3DXMATRIX transfromation;
				D3DXMatrixOrthoOffCenterLH(&transfromation, 0, viewPort.Width,
					viewPort.Height, 0, 0, 1);
				D3DXMATRIX translation;
				D3DXMatrixTranslation(&translation, -0.5, -0.5, 0);
				text.pixelShader->SetMatrix("MatrixTransform", translation * transfromation);
				text.pixelShader->ApplyEffect();

				// Begin effect pass.
				hr = text.pixelShader->GetCore()->GetEffect()->Begin(&nPass, D3DXFX_DONOTSAVESTATE);																				
				hr = text.pixelShader->GetCore()->GetEffect()->BeginPass(num);

				// Draw.
				hr = renderer->Draw(oldTarget->GetD3DTexture(), 0, 0, 0, SPColor::White );
				hr = renderer->Flush();

				// End pass.
				hr = text.pixelShader->GetCore()->GetEffect()->EndPass();							
				hr = text.pixelShader->GetCore()->GetEffect()->End();

				if (num != nPass - 1)
				{
					hr = renderer->End();

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
			}

			//
			// Restart scene.
			//

			//renderToSurface->BeginScene(pRenderSurface, NULL);

			//hr = renderer->Begin(
			//	D3DXSPRITE_ALPHABLEND
			//	| D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
			//	| D3DXSPRITE_SORT_TEXTURE);
			//PreDraw();

			//// Draw the resulting texture.
			////renderer->SetTransform(NULL);
			//renderer->Draw(	oldTarget->GetD3DTexture(), NULL, NULL, NULL, SPColor::White );
			//renderer->Flush();
		}
		else
		{
			RealWriteText(text);
		}

		hr = renderer->End();

		hr = renderToSurface->EndScene(0);

		pRenderSurface->Release();
		renderToSurface->Release();
		pRenderSurface = NULL;
		renderToSurface = NULL;

		hr = SPDevice::GetSingleton()->GetD3DDevice()->BeginScene();

		SPRectangle desRect = text.desRect;
		desRect.X -= text.font->GetHeight() * marginRate;
		desRect.Y -= text.font->GetHeight() * marginRate;
		desRect.Width += 2 * text.font->GetHeight() * marginRate;
		desRect.Height += 2 * text.font->GetHeight() * marginRate;

		SPSpriteManager::GetSingleton()->RenderOnScreen(tex,
			NULL, desRect, SPColor::White, 
			text.depth, text.target);

		return true;
	}

	bool SPFontWriter::AddTextToWrite(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		int			count,
		SPRectangle destRect,
		TextFormat	format,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		//texts.push_back(SPTextToWrite(
		//	font, ps, text, count, destRect, format, color, depth, target));	

		//return true;

		//SPSpriteManager::GetSingleton()->AddSprite(new SPTextSprite(
		//	font, ps, text, count, destRect, format, color, space, depth, target));

		//return true;

		// Immediately!
		return WriteText(SPTextToWrite(
			font, ps, text, count, destRect, format, color, space, depth, target));
	}

	bool SPFontWriter::Write(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		D3DXVECTOR2 position,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		if (!font)
		{
			font = defaultFont;
		}

		D3DXVECTOR2 size = font->GetTextSize(text, space);

		return Write(font, ps, text, SPRectangle((int)position.x,
			(int)position.y, (int)size.x,
			(int)size.y), color, space, depth, target);
	}

	bool SPFontWriter::Write(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		SPRectangle destRect,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		return Write(font, ps, text, -1, destRect, (TextFormat)(Top | Left), color, space, depth, target);
	}

	bool SPFontWriter::Write(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		SPRectangle destRect,
		TextFormat	format,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		return Write(font, ps, text, -1, destRect, format, color, space, depth, target);
	}

	bool SPFontWriter::Write(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		int			count,
		SPRectangle destRect,
		TextFormat	format,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		//AddTextToWrite(font, ps, 
		//	text, count, destRect, format, color, space, depth, target);

		//return true;

		// Immediately!
		return WriteText(SPTextToWrite(font, ps, text, count, 
			destRect, format, color, space, depth, target));
	}

	bool SPFontWriter::WriteCentered(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		D3DXVECTOR2 position,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		if (!font)
		{
			font = defaultFont;
		}

		D3DXVECTOR2 size = font->GetTextSize(text, Center | CenterVertical, space);

		return WriteCentered(font, ps, text, SPRectangle((int)position.x - (int)size.x / 2,
			(int)position.y - (int)size.y / 2, (int)size.x,
			(int)size.y), color, space, depth, target);
	}

	bool SPFontWriter::WriteCentered(
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring		text,
		SPRectangle destRect,
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target)
	{
		return WriteCentered(font, ps, text, -1, destRect, (TextFormat)0, color, space, depth, target);
	}

	bool SPFontWriter::WriteCentered( 
		SPFontPtr	font,
		SPEffectPtr ps,
		wstring	text, 
		int			count,
		SPRectangle destRect, 
		TextFormat	format, 
		D3DCOLOR	color,
		float		space,
		float		depth,
		SPTexturePtr target )
	{
		return Write(font, ps, text, count, destRect, 
			(TextFormat)(format | Center | CenterVertical), color, space, depth, target);
	}

	bool SPFontWriter::Initialize()
	{
		Load();
		return true;
	}

	bool SPFontWriter::RealWriteText( SPTextToWrite text )
	{
		HRESULT hr;
		float sizeRate = SPFontManager::GetSingleton()->GetSizeRate();
		float marginRate = SPFontManager::GetSingleton()->GetMarginRate();

		if (text.text.size() == 1 || text.wordSpace == 0)
		{
			SPRectangle targetRect = text.desRect;
			targetRect.X = sizeRate * text.font->GetHeight() * marginRate;
			targetRect.Y = sizeRate * text.font->GetHeight() * marginRate;
			targetRect.Width *= sizeRate;
			targetRect.Height *=  sizeRate;

			hr = text.font->GetD3DXFont()->DrawTextW(
				renderer,
				text.text.c_str(),
				text.count,
				&targetRect.CRect(),
				text.format,
				text.color);
		}	
		else
		{
			SPRectangle targetRect = text.desRect;			
			targetRect.X = sizeRate * text.font->GetHeight() * marginRate;
			targetRect.Y = sizeRate * text.font->GetHeight() * marginRate;

			for (int num = 0; num < (int)text.text.size(); num++)
			{
				if (text.text[num] == L'\n')
				{
					targetRect.Y += text.font->GetHeight();
					targetRect.X = sizeRate * text.font->GetHeight() * marginRate;
					continue;
				}

				D3DXVECTOR2 wordSize = text.font->GetTextSize(wstring(&text.text[num], 1), NULL, 0);		

				if (text.text[num] == L' ')
				{
					wordSize.x = text.font->GetTextSize(L"a a", NULL, 0).x - text.font->GetTextSize(L"aa", NULL, 0).x;
					wordSize.y = text.font->GetHeight();
				}

				targetRect.Width = wordSize.x * sizeRate;
				targetRect.Height = wordSize.y * sizeRate;

				hr = text.font->GetD3DXFont()->DrawTextW(
					renderer,
					wstring(&text.text[num], 1).c_str(),
					text.count,
					&targetRect.CRect(),
					text.format,
					text.color);

				targetRect.X += (wordSize.x + text.wordSpace * text.font->GetHeight()) * sizeRate;
			}
		}

		return true;
	}

}
