//////////////////////////////////////////////////////////////////////////
/// @file		SPTextureManager.h the implement file of SPTextureManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPTextureManager.h"
#include "SPColorHelper.h"

namespace SPEngine
{
	SPTextureManager::SPTextureManager(void)
	{
	}


	SPTextureManager::~SPTextureManager(void)
	{
	}

	SPEngine::SPTexturePtr SPTextureManager::GetTexture( SPString path )
	{
		if (textures.IsSet(path))
		{
			return textures[path];
		}

		SPTexturePtr newTexture = new SPTexture(path);
		textures.Set(path, newTexture);

		return newTexture;
	}

	void SPTextureManager::ReleaseTexture( SPString path )
	{
		if (textures.IsSet(path))
		{
			textures.Remove(path);
		}
	}

	SPEngine::SPAnimatedTexturePtr SPTextureManager::GetAnime( SPString path )
	{
		if (textures.IsSet(path))
		{
			return textures[path];
		}

		SPAnimatedTexturePtr newTexture = new SPAnimatedTexture();
		textures.Set(path, newTexture);

		return newTexture;
	}

	SPEngine::SPAnimatedTexturePtr SPTextureManager::GetAnime( 
		SPString path, 
		int setRow, 
		int setColumn, 
		int setFPS )
	{
		if (textures.IsSet(path))
		{
			SPAnimatedTexturePtr anime = textures[path];

			anime->SetColumn(setColumn);
			anime->SetRow(setRow);
			anime->SetFPS(setFPS);

			return anime;
		}

		SPAnimatedTexturePtr newTexture =
			new SPAnimatedTexture(path, setRow, setColumn, setFPS);
		textures.Set(path, newTexture);

		return newTexture;
	}

	void SPTextureManager::Update( float timeDelta )
	{
		// Update all animated texture.
		SPWStringMapIterator<SPTexturePtr> iter(&textures);
		for (iter.First(); !iter.IsDone(); iter.Next())
		{			
			if (iter.CurrentItem())
			{
				SPTexturePtr upTex = iter.CurrentItem();
				if (upTex)
				{
					upTex->Update(timeDelta);
				}				
			}
			
		}
	}

	void SPTextureManager::Unload()
	{
		// Unload all texture.
		SPWStringMapIterator<SPTexturePtr> iterTex(&textures);
		for(iterTex.First(); !iterTex.IsDone(); iterTex.Next())
		{
			if (iterTex.CurrentItem())
			{
				iterTex.CurrentItem()->Unload();
			}			
		}
	}

	void SPTextureManager::Reload()
	{
		// Reload all texture.
		SPWStringMapIterator<SPTexturePtr> iterTex(&textures);
		for(iterTex.First(); !iterTex.IsDone(); iterTex.Next())
		{
			iterTex.CurrentItem()->Reload();
		}

		if (textures.IsSet(L"blank_white_tex"))
		{		
			SPTexturePtr newTexture = new SPTexture();
			newTexture->CreateBlank(2, 2);
			newTexture->Fill(SPColor::White);
			textures.Set(L"blank_white_tex", newTexture);
		}
	}

	SPEngine::SPVideoTexturePtr SPTextureManager::GetVideo( SPString path )
	{
		if (textures.IsSet(path))
		{
			return textures[path];
		}

		SPVideoTexturePtr newTexture = new SPVideoTexture(path);
		textures.Set(path, newTexture);

		return newTexture;
	}

	SPTexturePtr SPTextureManager::CreateBlankTexture(
		SPString path, int width, int height, D3DCOLOR color )
	{
		

		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateBlank(width, height);
		newTexture->Fill(color);
		textures.Set(path, newTexture);
		return newTexture;
	}

	SPEngine::SPTexturePtr SPTextureManager::CreateBlankTexture( int width, int height )
	{
		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateBlank(width, height);
		return newTexture;
	}

	SPTexturePtr SPTextureManager::CreateRenderTarget( int width, int height, D3DCOLOR color)
	{
		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateRenderTarget(width, height, color);
		return newTexture;
	}

	SPEngine::SPTexturePtr SPTextureManager::GetBlankWhiteTexture()
	{
		if (textures.IsSet(L"blank_white_tex"))
		{
			return textures[L"blank_white_tex"];
		}

		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateRenderTarget(2, 2, SPColor::White);
		newTexture->Fill(SPColor::White);
		textures.Set(L"blank_white_tex", newTexture);
		return newTexture;
	}

	SPParticleSystemTexturePtr SPTextureManager::GetParticleSystem( SPString path )
	{
		if (textures.IsSet(path))
		{
			return textures[path];
		}

		SPParticleSystemTexturePtr newTexture = new SPParticleSystemTexture(path);
		newTexture->CreateRenderTarget(1, 1, newTexture->GetBackgroundColor());
		textures.Set(path, newTexture);

		return newTexture;
	}

	SPParticleSystemTexturePtr SPTextureManager::CreateParticleSystemTexture( SPString name, int width, int height )
	{
		SPParticleSystemTexturePtr newTexture = new SPParticleSystemTexture(name);
		newTexture->CreateRenderTarget(width, height, newTexture->GetBackgroundColor());
		textures.Set(name, newTexture);

		return newTexture;
	}

}

