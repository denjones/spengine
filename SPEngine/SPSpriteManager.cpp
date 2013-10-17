//////////////////////////////////////////////////////////////////////////
/// @file		SPSpriteManager.cpp the complement file of SPSpriteManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPSpriteManager.h"
#include "SPGame.h"
#include "SPColorHelper.h"
#include "SPDevice.h"
#include <vector>
#include <algorithm>
#include "SPTextureManager.h"
#include "SPConfigManager.h"
#include "SPStringHelper.h"
#include "SPTextureSprite.h"

#pragma warning (disable:4244)

namespace SPEngine
{
	SPSpriteManager::SPSpriteManager(void)
	{
		Renderer = NULL;
		innerRenderer = NULL;
		currentTarget = NULL;
		isTopological = true;
		//blendEffect = new SPEffect(L"blend/blend_normal.fx");
	}

	SPSpriteManager::~SPSpriteManager(void)
	{
		Unload();
	}

	bool SPSpriteManager::Initialize()
	{
		Load();

		return true;
	}

	bool SPSpriteManager::DrawSimple(float timeDelta)
	{
		Renderer->Begin(D3DXSPRITE_ALPHABLEND);// | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);

		foreach(SPSpritePtr, sprite, list<SPSpritePtr>, sprites)
		{
			sprite->Draw(Renderer, innerRenderer, NULL, NULL);
		}

		Renderer->End();

		sprites.clear();

		return true;
	}

	bool CompareSprite(SPSpritePtr a, SPSpritePtr b)
	{
		return a->depth > b->depth;
	}

	bool SPSpriteManager::DrawTopological( float timeDelta )
	{
		TopologicalSort();

		SPSpriteIterator iter = sprites.begin();

		while(iter != sprites.end())
		{
			HRESULT hr;
			ID3DXRenderToSurface* renderToSurface = NULL;
			LPDIRECT3DSURFACE9 pRenderSurface = NULL;

			currentTarget = (*iter)->renderTarget;
			vector<SPSpritePtr> spritesToRender;

			// Add sprite to render.
			while(iter != sprites.end() && (*iter)->renderTarget == currentTarget)
			{
				spritesToRender.push_back(*iter);

				iter++;
			}

			// Sort.
			sort(spritesToRender.begin(), spritesToRender.end(), CompareSprite);

			// Begin rendering off screen.
			if (currentTarget && currentTarget->IsRenderTarget())
			{
				hr = SPDevice::GetSingleton().GetD3DDevice()->EndScene();

				hr = currentTarget->GetD3DTexture()->GetSurfaceLevel(0, &pRenderSurface);

				D3DSURFACE_DESC desc;
				hr = pRenderSurface->GetDesc( &desc );

				hr = D3DXCreateRenderToSurface(
					SPDevice::GetSingleton().GetD3DDevice(), 
					desc.Width, 
					desc.Height,
					desc.Format,
					FALSE, 
					D3DFMT_D24S8,
					&renderToSurface);

				hr = renderToSurface->BeginScene(pRenderSurface, NULL);	

				//hr = SPDevice::GetSingleton().GetD3DDevice()->BeginScene();	

				hr = SPDevice::GetSingleton().GetD3DDevice()->Clear(1, 0, D3DCLEAR_TARGET, currentTarget->GetBackgroundColor(), 1.0f, 0); 
			}

			// Begin rendering.
			
			hr = Renderer->Begin( D3DXSPRITE_DONOTSAVESTATE );

			// Render all sprite with the same target.
			vector<SPSpritePtr>::iterator sprite = spritesToRender.begin();
			
			while(sprite != spritesToRender.end())
			{
				PreDraw();
				(*sprite)->Draw(Renderer, innerRenderer, pRenderSurface, renderToSurface);

				sprite++;
			}

			// End rendering.
			hr = Renderer->End();
			
			// End rendering off screen.
			if(currentTarget && currentTarget->IsRenderTarget())
			{
				hr = renderToSurface->EndScene(0);

				hr = pRenderSurface->Release();
				hr = renderToSurface->Release();

				pRenderSurface = NULL;
				renderToSurface = NULL;

				hr = SPDevice::GetSingleton().GetD3DDevice()->BeginScene();
			}
		}

		// Clear the sprite drawn in the frame.
		sprites.clear();

		return true;
	}

	bool SPSpriteManager::TopologicalSort()
	{
		if (sprites.size() == 0)
		{
			return true;
		}
		
		vector<SPTexturePtr> targets;
		vector<SPTexturePtr> objects;

		typedef pair<SPTexturePtr, SPTexturePtr> Relation;
		vector<Relation> relationShip;

		// Generate objects and set up relationship.
		SPSpriteIterator iter = sprites.begin();
		while(iter != sprites.end())
		{
			if ((*iter)->texture)
			{
				relationShip.push_back(Relation((*iter)->texture, (*iter)->renderTarget));

				if (find(objects.begin(), objects.end(), (*iter)->texture) == objects.end())
				{
					objects.push_back((*iter)->texture);				
				}

				if ((*iter)->effect)
				{
					SPEffect::SamplerMap samplers = (*iter)->effect->GetSampler();

					SPEffect::SamplerMap::iterator sample = samplers.begin();
					while(sample != samplers.end())
					{
						if (sample->second)
						{
							relationShip.push_back(Relation(sample->second, (*iter)->renderTarget));

							if (find(objects.begin(), objects.end(), sample->second) == objects.end())
							{
								objects.push_back(sample->second);				
							}
						}

						sample++;
					}
				}
			}

			iter++;
		}
		
		// Get the topological queue.
		vector<SPTexturePtr>::iterator object = objects.begin();
		while(objects.size() > 0)
		{
			if (object == objects.end())
			{
				object = objects.begin();
			}

			int targetCount = 0;

			// Find a node without in edge.
			vector<Relation>::iterator relation = relationShip.begin();
			while(relation != relationShip.end())
			{
				if (*object == relation->second)
				{
					targetCount++;
					break;
				}
				relation++;
			}

			if (targetCount > 0)
			{				
				object++;
				continue;
			}			

			// Remove all edges with the input node.
			relation = relationShip.begin();
			while(relation != relationShip.end())
			{
				if (*object == relation->first)
				{
					relation = relationShip.erase(relation);
				}
				else
				{
					relation++;
				}				
			}

			// Record the input node
			targets.push_back(*object);
			object = objects.erase(object);
		}

		// Push top render target.
		targets.push_back(NULL);

		// Sort the sprite list.
		SPSpriteList tempList;
		vector<SPTexturePtr>::iterator texIter = targets.begin();
		while(texIter != targets.end())
		{
			SPSpriteIterator innerIter = sprites.begin();
			while(innerIter != sprites.end())
			{
				if (*texIter == (*innerIter)->renderTarget)
				{
					tempList.push_back(*innerIter);
					innerIter = sprites.erase(innerIter);
				}
				else
				{
					innerIter++;
				}				
			}

			texIter++;
		}

		// Set sprite list.
		sprites = tempList;

		return true;
	}

	bool SPSpriteManager::DrawSprite( SPSpritePtr sprite )
	{
		sprite->Draw(Renderer, innerRenderer, NULL, NULL);

		return true;
	}

	bool SPSpriteManager::Update(float timeDelta)
	{
		return true;
	}

	bool SPSpriteManager::AddSprite( 
		SPTexturePtr	tex,
		SPEffectPtr pixelShader,
		D3DXVECTOR3 center,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		RECT rect = tex->SourceRectangle().CRect();
		//SetRect(&rect, 0, 0, tex->GetWidth() , tex->GetHeight());
		D3DXMATRIX transformMatrix;
		D3DXVECTOR3 realPosition;

		if (target)
		{
			//D3DXMatrixTransformation2D(&transformMatrix, 
			//	NULL, 0, NULL, NULL, 0, NULL);

			// realPosition = position;

			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, rect, center, position, color, target);

			sprites.push_back(sprite);
		}
		else
		{
			float xRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowWidth / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
			float yRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowHeight / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;

			//D3DXMatrixTransformation2D(&transformMatrix, 
			//	NULL, 0, &D3DXVECTOR2(xRate, yRate), NULL, 0, NULL);

			//realPosition = position;
			//realPosition.x *= xRate;
			//realPosition.y *= yRate;

			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, rect, center, position, color, target);
			
			sprite->scaling = D3DXVECTOR2(xRate, yRate);

			sprites.push_back(sprite);
		}

		return true;
	}

	bool SPSpriteManager::AddSprite( 
		SPTexturePtr	tex , 
		SPEffectPtr		pixelShader,
		D3DXMATRIX		transformMatrix,
		RECT			srcRect,
		D3DXVECTOR3		center, 
		D3DXVECTOR3		position, 
		D3DCOLOR		color,
		SPTexturePtr	target)
	{
		if (target)
		{
			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, transformMatrix, 
				srcRect, center, position, color, target);
			sprites.push_back(sprite);
		}
		else
		{
			float xRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowWidth / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
			float yRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowHeight / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;

			D3DXMATRIX mulMatrix;
			D3DXMatrixTransformation2D(&mulMatrix, 
				NULL, 0, &D3DXVECTOR2(xRate, yRate), NULL, 0, NULL);

			transformMatrix = mulMatrix * transformMatrix;

			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, transformMatrix, 
				srcRect, center, position, color, target);
			sprites.push_back(sprite);
		}		

		return true;
	}

	bool SPSpriteManager::AddSprite( 
		SPTexturePtr	tex ,
		SPEffectPtr pixelShader,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		RECT		srcRect,
		D3DXVECTOR3 center,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		//D3DXMATRIX transformMatrix;
		//D3DXVECTOR3 realPosition;

		if (target)
		{
			//D3DXMatrixTransformation2D(&transformMatrix, &scalingCenter,
			//	scalingRotation, &scaling, &rotationCenter,
			//	rotation, &translation);

			//realPosition = position;

			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, srcRect, center, position,
				scalingCenter, scalingRotation, scaling, rotationCenter,
				rotation, translation, color, target);

			sprites.push_back(sprite);
		}
		else
		{
			float xRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowWidth / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
			float yRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().windowHeight / 
				SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;

			D3DXVECTOR2 realScalingCenter = D3DXVECTOR2(scalingCenter.x * xRate, scalingCenter.y * yRate);
			D3DXVECTOR2 realScaling = D3DXVECTOR2(scaling.x * xRate, scaling.y * yRate);
			D3DXVECTOR2 realTranslation = D3DXVECTOR2(translation.x * xRate, translation.y * yRate);
			
			//D3DXMatrixTransformation2D(&transformMatrix, &realScalingCenter,
			//	scalingRotation, &realScaling, 
			//	&rotationCenter, rotation,  &realTranslation);

			//realPosition = position;
			position.x *= xRate;
			position.y *= yRate;

			SPTextureSpritePtr sprite = new SPTextureSprite(tex, pixelShader, srcRect, center, position,
				realScalingCenter, scalingRotation, realScaling, rotationCenter,
				rotation, realTranslation, color, target);

			sprites.push_back(sprite);
		}

		return true;
	}

	bool SPSpriteManager::AddSprite( SPSpritePtr sprite )
	{
		if (!sprite)
		{
			return false;
		}

		sprites.push_back(sprite);

		return true;
	}

	bool SPSpriteManager::Load()
	{
		if (!Renderer)
		{
			if(FAILED(D3DXCreateSprite(SPDevice::GetSingleton().GetD3DDevice(), &Renderer)))
			{
				return false;
			}
		}

		if (!innerRenderer)
		{
			if(FAILED(D3DXCreateSprite(SPDevice::GetSingleton().GetD3DDevice(), &innerRenderer)))
			{
				return false;
			}
		}	

		return true;
	}

	bool SPSpriteManager::Unload()
	{
		if (Renderer)
		{
			Renderer->Release();
			Renderer = NULL;
		}

		if (innerRenderer)
		{
			innerRenderer->Release();
			innerRenderer = NULL;
		}

		sprites.clear();

		return true;
	}

	//LPDIRECT3DDEVICE9 SpriteManager::GetDevice()
	//{
	//	return currentGame->GetDevice();
	//}
	// Simple render function
	bool SPSpriteManager::Render( 
		SPTexturePtr tex, 
		SPEffectPtr ps,
		SPTexturePtr target)
	{
		return	Render(tex, ps, D3DXVECTOR3(0, 0, 0), target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		SPTexturePtr	target)
	{
		return Render(tex, ps, x, y, SPColor::White, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		SPTexturePtr	target)
	{
		return Render(tex, ps, position, SPColor::White, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return Render(tex, ps, x, y, color, 0, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return Render(tex, ps, D3DXVECTOR3(x, y, depth), color, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return Render(tex, ps, D3DXVECTOR3(0, 0, 0), position, color, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps, 
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position, 
		D3DCOLOR	color,
		SPTexturePtr	target )
	{
		AddSprite(tex, ps, center, position, color, target);

		return true;
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return Render(tex, ps, D3DXVECTOR3(x, y, depth),
			D3DXVECTOR2(scale, scale), rotation, color, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return Render(tex, ps, position, D3DXVECTOR2(position.x, position.y), 0, 
			scaling, D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::Render( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,			
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, color, 
			scalingCenter, scalingRotation, scaling,
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	// Render on screen with rectangle
	bool SPSpriteManager::RenderOnScreen( 
		SPTexturePtr tex, SPEffectPtr ps,
		SPRectangle	destRect,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderOnScreen(tex, ps, SPRectangle(0, 0, tex->GetWidth(), 
			tex->GetHeight()), destRect, color, depth, target);
	}

	bool SPSpriteManager::RenderOnScreen( 
		SPTexturePtr tex, SPEffectPtr ps,
		SPRectangle	srcRect,
		SPRectangle	destRect,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderBasic(tex, ps, srcRect.CRect(), D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3((float)destRect.X, (float)destRect.Y, depth),
			color, D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
			D3DXVECTOR2((float)destRect.Width / srcRect.Width, 
			(float)destRect.Height / srcRect.Height), 
			D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
			D3DXVECTOR2(0,0), target);
	}

	// Render with matrix
	bool SPSpriteManager::RenderWithMatrix( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXMATRIX	transformMatrix,
		D3DXVECTOR3 center,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		//RECT srcRect;
		//SetRect(&srcRect, 0, 0, tex->GetWidth(), tex->GetHeight());
		//return RenderWithMatrix(tex, ps, transformMatrix,
		//	tex->SourceRectangle().CRect(), center, position, color, target);
		AddSprite(tex, ps, transformMatrix,
			tex->SourceRectangle().CRect(), center, position, color, target);

		return true;
	}

	bool SPSpriteManager::RenderWithMatrix( 
		SPTexturePtr tex, SPEffectPtr ps, 
		D3DXMATRIX	transformMatrix,
		RECT		srcRect,
		D3DXVECTOR3 center,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target )
	{
		if (!tex)
		{
			return false;
		}

		SPRectangle realSrcRect = tex->SourceRectangle();

		realSrcRect.X += srcRect.left;
		realSrcRect.Y += srcRect.top;
		realSrcRect.Width = srcRect.right - srcRect.left;
		realSrcRect.Height = srcRect.bottom - srcRect.top;

		AddSprite(tex, ps, transformMatrix,
			realSrcRect.CRect(), center, position, color, target);

		return true;
	}

	// Render with scaling
	bool SPSpriteManager::RenderWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderWithScaling(tex, ps, x, y, scale, color, 0, target);
	}

	bool SPSpriteManager::RenderWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderWithScaling(tex, ps, D3DXVECTOR3(x, y, depth), scale, color, target);
	}

	bool SPSpriteManager::RenderWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return	RenderWithScaling(tex, ps, position, 
			D3DXVECTOR2(scale, scale),	color, target);
	}

	bool SPSpriteManager::RenderWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderWithScaling(tex, ps, position,
			D3DXVECTOR2(position.x, position.y), 0, scaling, color, target);
	}

	bool SPSpriteManager::RenderWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, scalingCenter, scalingRotation, scaling,
			D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0), target);
	}

	// Render with rotation
	bool SPSpriteManager::RenderWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderWithRotation(tex, ps, x, y, rotation, color, 0, target);
	}

	bool SPSpriteManager::RenderWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return RenderWithRotation(tex, ps, D3DXVECTOR3(x,y,depth), rotation, color, target);
	}

	bool SPSpriteManager::RenderWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderWithRotation(tex, ps, position, 
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::RenderWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::RenderBasic( 
		SPTexturePtr tex, SPEffectPtr ps, 
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position, 
		D3DCOLOR	color, 
		D3DXVECTOR2 scalingCenter, 
		float		scalingRotation, 
		D3DXVECTOR2 scaling, 
		D3DXVECTOR2 rotationCenter, 
		float		rotation, 
		D3DXVECTOR2 translation ,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		RECT srcRect;
		SetRect(&srcRect, 0, 0, tex->GetWidth(), tex->GetHeight());

		return RenderBasic(tex, ps, srcRect, center, position, color, scalingCenter, 
			scalingRotation, scaling, rotationCenter, 
			rotation, translation, target);
	}

	bool SPSpriteManager::RenderBasic( 
		SPTexturePtr tex, SPEffectPtr ps,
		RECT		srcRect,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		SPTexturePtr	target)
	{
		SPRectangle realSrcRect = tex->SourceRectangle();

		realSrcRect.X += srcRect.left;
		realSrcRect.Y += srcRect.top;
		realSrcRect.Width = srcRect.right - srcRect.left;
		realSrcRect.Height = srcRect.bottom - srcRect.top;

		AddSprite(tex, ps,
			scalingCenter, scalingRotation,	scaling,
			rotationCenter, rotation, translation,
			realSrcRect.CRect(), center, position, color, target);

		return true;
	}

	// Render centered
	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, 
		SPEffectPtr ps,
		SPTexturePtr	target)
	{
		return	RenderCentered(tex, ps, D3DXVECTOR3(0, 0, 0), target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, x, y, SPColor::White, target);
	}

	bool SPSpriteManager::RenderCentered(
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, position, SPColor::White, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, x, y, color, 0, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, D3DXVECTOR3(x, y, depth), color, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, D3DXVECTOR3(0, 0, 0), position, color, target);
	}

	bool SPSpriteManager::RenderCentered( SPTexturePtr tex, SPEffectPtr ps, 
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position, 
		D3DCOLOR	color ,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		AddSprite(tex, ps, center, 
			D3DXVECTOR3(position.x - tex->GetWidth() / 2, 
			position.y - tex->GetHeight() / 2, position.z), color, target);

		return true;
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, D3DXVECTOR3(x, y, depth),
			D3DXVECTOR2(scale, scale), rotation, color, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, position, D3DXVECTOR2(position.x, position.y), 0, 
			scaling, D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,			
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, color, 
			scalingCenter, scalingRotation, scaling,
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		SPRectangle srcRect,
		D3DXVECTOR3 position,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCentered(tex, ps, srcRect, position, scale,
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::RenderCentered( 
		SPTexturePtr tex, SPEffectPtr ps,
		SPRectangle srcRect,
		D3DXVECTOR3 position,
		float		scale,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderBasic(tex, ps, srcRect.CRect(), D3DXVECTOR3(0, 0, 0), 
			D3DXVECTOR3(position.x - srcRect.Width / 2,
			position.y - srcRect.Height / 2, position.z),
			color, D3DXVECTOR2(position.x, position.y), 
			0, D3DXVECTOR2(scale, scale),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	// Render with scaling
	bool SPSpriteManager::RenderCenteredWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredWithScaling(tex, ps, x, y, scale, color, 0, target);
	}

	bool SPSpriteManager::RenderCenteredWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return RenderCenteredWithScaling(tex, ps, D3DXVECTOR3(x, y, depth), scale, color, target);
	}

	bool SPSpriteManager::RenderCenteredWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return	RenderCenteredWithScaling(tex, ps, position, 
			D3DXVECTOR2(scale, scale),	color, target);
	}

	bool SPSpriteManager::RenderCenteredWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredWithScaling(tex, ps, position,
			D3DXVECTOR2(position.x, position.y), 0, scaling, color, target);
	}

	bool SPSpriteManager::RenderCenteredWithScaling( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, scalingCenter, scalingRotation, scaling,
			D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0), target);
	}

	// Render with rotation
	bool SPSpriteManager::RenderCenteredWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredWithRotation(tex, ps, x, y, rotation, color, 0, target);
	}

	bool SPSpriteManager::RenderCenteredWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return RenderCenteredWithRotation(tex, ps, D3DXVECTOR3(x,y,depth), rotation, color, target);
	}

	bool SPSpriteManager::RenderCenteredWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredWithRotation(tex, ps, position, 
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::RenderCenteredWithRotation( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return RenderCenteredBasic(tex, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::RenderCenteredBasic( 
		SPTexturePtr tex, SPEffectPtr ps,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		RECT srcRect;
		SetRect(&srcRect, 0, 0, tex->GetWidth(), tex->GetHeight());

		return RenderCenteredBasic(tex, ps, srcRect, center, position, 
			color, scalingCenter, scalingRotation, scaling, 
			rotationCenter, rotation,translation, target);
	}

	bool SPSpriteManager::RenderCenteredBasic( 
		SPTexturePtr tex, SPEffectPtr ps,
		RECT		srcRect,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		SPTexturePtr	target)
	{
		if (!tex)
		{
			return false;
		}

		return RenderBasic(tex, ps, srcRect, center, D3DXVECTOR3(position.x - tex->GetWidth() / 2,
			position.y - tex->GetHeight() / 2, position.z),
			color, scalingCenter, scalingRotation, scaling,
			rotationCenter, rotation, translation, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime,
		SPEffectPtr ps,
		SPTexturePtr	target)
	{
		return	ARender(anime, ps, D3DXVECTOR3(0, 0, 0), target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime,
		SPEffectPtr ps,
		float		x,
		float		y,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, x, y, SPColor::White, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, position, SPColor::White, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, x, y, color, 0, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, D3DXVECTOR3(x, y, depth), color, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, D3DXVECTOR3(0, 0, 0), position, color, target);
	}

	bool SPSpriteManager::ARender( 
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position, 
		D3DCOLOR	color ,
		SPTexturePtr	target)
	{
		return ARenderBasic(anime, ps, center, position, color, 
			D3DXVECTOR2(position.x, position.y), 
			0, D3DXVECTOR2(1, 1),
			D3DXVECTOR2(position.x, position.y),
			0, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, D3DXVECTOR3(x, y, depth),
			D3DXVECTOR2(scale, scale), rotation, color, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARender(anime, ps, position, D3DXVECTOR2(position.x, position.y), 0, 
			scaling, D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::ARender(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,			
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, color, 
			scalingCenter, scalingRotation, scaling,
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	// Render on screen with rectangle
	bool SPSpriteManager::ARenderOnScreen(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		SPRectangle	destRect,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		if (!anime)
		{
			return false;
		}

		return ARenderBasic(anime, ps, D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3((float)destRect.X, (float)destRect.Y, depth),
			color, D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
			D3DXVECTOR2((float)destRect.Width / anime->SourceRectangle().Width, 
			(float)destRect.Height / anime->SourceRectangle().Height), 
			D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
			D3DXVECTOR2(0,0), target);
	}

	// Render animation with scaling
	bool SPSpriteManager::ARenderWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!anime)
		{
			return false;
		}

		return ARenderWithScaling(anime, ps, x, y, scale, color, 0, target);
	}

	bool SPSpriteManager::ARenderWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderWithScaling(anime, ps, D3DXVECTOR3(x, y, depth), scale, color, target);
	}

	bool SPSpriteManager::ARenderWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return	ARenderWithScaling(anime, ps, position, 
			D3DXVECTOR2(scale, scale),	color, target);
	}

	bool SPSpriteManager::ARenderWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderWithScaling(anime, ps, position,
			D3DXVECTOR2(position.x, position.y), 0, scaling, color, target);
	}

	bool SPSpriteManager::ARenderWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, scalingCenter, scalingRotation, scaling,
			D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0), target);
	}

	// Render with rotation
	bool SPSpriteManager::ARenderWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderWithRotation(anime, ps, x, y, rotation, color, 0, target);
	}

	bool SPSpriteManager::ARenderWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderWithRotation(anime, ps, D3DXVECTOR3(x,y,depth), rotation, color, target);
	}

	bool SPSpriteManager::ARenderWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderWithRotation(anime, ps, position, 
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::ARenderWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::ARenderBasic(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		SPTexturePtr	target)
	{
		if (!anime)
		{
			return false;
		}

		return RenderBasic(anime, ps, anime->SourceRectangle().CRect(), 
			center, position, color,	scalingCenter, scalingRotation, 
			scaling, rotationCenter,	rotation, translation, target);
	}

	// Render centered
	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		SPTexturePtr	target)
	{
		return	ARenderCentered(anime, ps, D3DXVECTOR3(0, 0, 0), target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime,
		SPEffectPtr ps,
		float		x,
		float		y,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, x, y, SPColor::White, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, position, SPColor::White, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, x, y, color, 0, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		float		x,
		float		y,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, D3DXVECTOR3(x, y, depth), color, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime,
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, D3DXVECTOR3(0, 0, 0), position, color, target);
	}

	bool SPSpriteManager::ARenderCentered( 
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position, 
		D3DCOLOR	color,
		SPTexturePtr	target )
	{
		if (!anime)
		{
			return false;
		}

		return ARender(anime, ps, center, D3DXVECTOR3(
			position.x - anime->SourceRectangle().Width / 2, 
			position.y - anime->SourceRectangle().Height / 2,
			position.z), color, target);
		return true;
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime,
		SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, D3DXVECTOR3(x, y, depth),
			D3DXVECTOR2(scale, scale), rotation, color, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, position, D3DXVECTOR2(position.x, position.y), 0, 
			scaling, D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,			
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, color, 
			scalingCenter, scalingRotation, scaling,
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCentered(anime, ps, position, scale,
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::ARenderCentered(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		if (!anime)
		{
			return false;
		}

		return ARenderBasic(anime, ps, D3DXVECTOR3(0, 0, 0), 
			D3DXVECTOR3(position.x - anime->SourceRectangle().Width / 2,
			position.y - anime->SourceRectangle().Height / 2, position.z),
			color, D3DXVECTOR2(position.x, position.y), 
			0, D3DXVECTOR2(scale, scale),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	// Render with scaling
	bool SPSpriteManager::ARenderCenteredWithScaling(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithScaling(anime, ps, x, y, scale, color, 0, target);
	}

	bool SPSpriteManager::ARenderCenteredWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		scale,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithScaling(anime, ps, D3DXVECTOR3(x, y, depth), scale, color, target);
	}

	bool SPSpriteManager::ARenderCenteredWithScaling(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		scale,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return	ARenderCenteredWithScaling(anime, ps, position, 
			D3DXVECTOR2(scale, scale),	color, target);
	}

	bool SPSpriteManager::ARenderCenteredWithScaling(
		SPAnimatedTexturePtr anime, 
		SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithScaling(anime, ps, position,
			D3DXVECTOR2(position.x, position.y), 0, scaling, color, target);
	}

	bool SPSpriteManager::ARenderCenteredWithScaling(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, scalingCenter, scalingRotation, scaling,
			D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0), target);
	}

	// Render with rotation
	bool SPSpriteManager::ARenderCenteredWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithRotation(anime, ps, x, y, rotation, color, 0, target);
	}

	bool SPSpriteManager::ARenderCenteredWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		float		x,
		float		y,
		float		rotation,
		D3DCOLOR	color,
		float		depth,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithRotation(anime, ps, D3DXVECTOR3(x,y,depth), rotation, color, target);
	}

	bool SPSpriteManager::ARenderCenteredWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredWithRotation(anime, ps, position, 
			D3DXVECTOR2(position.x, position.y), rotation, color, target);
	}

	bool SPSpriteManager::ARenderCenteredWithRotation(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 position,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DCOLOR	color,
		SPTexturePtr	target)
	{
		return ARenderCenteredBasic(anime, ps, D3DXVECTOR3(0, 0, 0), position, 
			color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
			rotationCenter, rotation, D3DXVECTOR2(0, 0), target);
	}

	bool SPSpriteManager::ARenderCenteredBasic(
		SPAnimatedTexturePtr anime, SPEffectPtr ps,
		D3DXVECTOR3 center, 
		D3DXVECTOR3 position,
		D3DCOLOR	color,
		D3DXVECTOR2 scalingCenter,
		float		scalingRotation,
		D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCenter,
		float		rotation,
		D3DXVECTOR2 translation,
		SPTexturePtr	target)
	{
		if (!anime)
		{
			return false;
		}

		return RenderCenteredBasic(anime, ps, anime->SourceRectangle().CRect(), center, position, 
			color, scalingCenter, scalingRotation, scaling, 
			rotationCenter, rotation,translation, target);
	}

	bool SPSpriteManager::Draw( float timeDelta )
	{
		if (isTopological)
		{
			DrawTopological(timeDelta);
		}
		else
		{
			DrawSimple(timeDelta);
		}

		return true;
	}

	bool SPSpriteManager::PreDraw()
	{
		HRESULT hr = S_OK;
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, TRUE );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );
		hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_ALPHAREF, 0x00000000 );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_FOGENABLE, FALSE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 0, D3DTSS_RESULTARG, D3DTA_CURRENT );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
		//hr = SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
		return true;
	}

	bool SPSpriteManager::PostDraw()
	{
		return true;
	}
}