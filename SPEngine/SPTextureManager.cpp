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
		if (nameToTexture.IsSet(path))
		{
			return textureHandleMgr.Dereference(nameToTexture[path]);
		}

		nameToTexture.Set(path, SPTextureHandle());

		SPTexturePtr newTexture = new SPTexture(path);
		textureHandleMgr.Acquire(nameToTexture[path]) = newTexture;

		return textureHandleMgr.Dereference(nameToTexture[path]);
	}

	void SPTextureManager::ReleaseTexture( SPString path )
	{
		if (nameToTexture.IsSet(path))
		{
			textureHandleMgr.Release(nameToTexture[path]);
			nameToTexture.Remove(path);
		}
	}

	SPEngine::SPAnimatedTexturePtr SPTextureManager::GetAnime( SPString path )
	{
		if (nameToUpdatable.IsSet(path))
		{
			return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
		}

		nameToUpdatable.Set(path, SPTextureHandle());

		SPAnimatedTexturePtr newTexture = new SPAnimatedTexture();
		updatableTextureHanldeMgr.Acquire(nameToUpdatable[path]) = newTexture;

		return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
	}

	SPEngine::SPAnimatedTexturePtr SPTextureManager::GetAnime( 
		SPString path, 
		int setRow, 
		int setColumn, 
		int setFPS )
	{
		if (nameToUpdatable.IsSet(path))
		{
			SPAnimatedTexturePtr anime = updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);

			anime->SetColumn(setColumn);
			anime->SetRow(setRow);
			anime->SetFPS(setFPS);

			return anime;
		}

		nameToUpdatable.Set(path, SPTextureHandle());

		SPAnimatedTexturePtr newTexture =
			new SPAnimatedTexture(path, setRow, setColumn, setFPS);
		updatableTextureHanldeMgr.Acquire(nameToUpdatable[path]) = newTexture;

		return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
	}

	void SPTextureManager::ReleaseUpdatable( SPString path )
	{
		if (nameToTexture.IsSet(path))
		{
			updatableTextureHanldeMgr.Release(nameToTexture[path]);
			nameToUpdatable.Remove(path);
		}
	}

	bool SPTextureManager::Update( float timeDelta )
	{
		// Update all animated texture.
		SPWStringMapIterator<SPTextureHandle> iter(&nameToUpdatable);
		for (iter.First(); !iter.IsDone(); iter.Next())
		{			
			if (iter.CurrentItem())
			{
				SPUpdatableTexturePtr upTex = updatableTextureHanldeMgr.Dereference(iter.CurrentItem());
				if (upTex)
				{
					upTex->Update(timeDelta);
				}				
			}
			
		}

		return true;
	}

	bool SPTextureManager::Unload()
	{
		// Unload all texture.
		SPWStringMapIterator<SPTextureHandle> iterTex(&nameToTexture);
		for(iterTex.First(); !iterTex.IsDone(); iterTex.Next())
		{
			if (iterTex.CurrentItem())
			{
				textureHandleMgr.Dereference(iterTex.CurrentItem())->Unload();
			}			
		}

		// Unload all animated texture.
		SPWStringMapIterator<SPTextureHandle> iterAnime(&nameToUpdatable);
		for (iterAnime.First(); !iterAnime.IsDone(); iterAnime.Next())
		{
			if (iterAnime.CurrentItem())
			{
				updatableTextureHanldeMgr.Dereference(iterAnime.CurrentItem())->Unload();
			}			
		}

		return true;
	}

	bool SPTextureManager::Reload()
	{
		

		// Reload all texture.
		SPWStringMapIterator<SPTextureHandle> iterTex(&nameToTexture);
		for(iterTex.First(); !iterTex.IsDone(); iterTex.Next())
		{
			textureHandleMgr.Dereference(iterTex.CurrentItem())->Reload();
		}

		// Reload all animated texture.
		SPWStringMapIterator<SPTextureHandle> iterAnime(&nameToUpdatable);
		for (iterAnime.First(); !iterAnime.IsDone(); iterAnime.Next())
		{
			updatableTextureHanldeMgr.Dereference(iterAnime.CurrentItem())->Reload();
		}

		if (nameToTexture.IsSet(L"blank_white_tex"))
		{
			
			nameToTexture.Set(L"blank_white_tex", SPTextureHandle());
			SPTexturePtr newTexture = new SPTexture();
			newTexture->CreateBlank(2, 2);
			newTexture->Fill(SPColor::White);
			textureHandleMgr.Acquire(nameToTexture[L"blank_white_tex"]) = newTexture;
		}		

		return true;
	}

	SPEngine::SPVideoTexturePtr SPTextureManager::GetVideo( SPString path )
	{
		if (nameToUpdatable.IsSet(path))
		{
			return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
		}

		nameToUpdatable.Set(path, SPTextureHandle());

		SPVideoTexturePtr newTexture = new SPVideoTexture(path);
		updatableTextureHanldeMgr.Acquire(nameToUpdatable[path]) = newTexture;

		return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
	}

	SPTexturePtr SPTextureManager::CreateBlankTexture(
		SPString path, int width, int height, D3DCOLOR color )
	{
		nameToTexture.Set(path, SPTextureHandle());

		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateBlank(width, height);
		newTexture->Fill(color);
		
		textureHandleMgr.Acquire(nameToTexture[path]) = newTexture;
		return textureHandleMgr.Dereference(nameToTexture[path]);
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
		if (nameToTexture.IsSet(L"blank_white_tex"))
		{
			return textureHandleMgr.Dereference(nameToTexture[L"blank_white_tex"]);
		}

		nameToTexture.Set(L"blank_white_tex", SPTextureHandle());
		SPTexturePtr newTexture = new SPTexture();
		newTexture->CreateRenderTarget(2, 2, SPColor::White);
		newTexture->Fill(SPColor::White);

		textureHandleMgr.Acquire(nameToTexture[L"blank_white_tex"]) = newTexture;
		return newTexture;
	}

	SPParticleSystemTexturePtr SPTextureManager::GetParticleSystem( SPString path )
	{
		if (nameToUpdatable.IsSet(path))
		{
			return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
		}

		nameToUpdatable.Set(path, SPTextureHandle());

		SPParticleSystemTexturePtr newTexture = new SPParticleSystemTexture(path);
		updatableTextureHanldeMgr.Acquire(nameToUpdatable[path]) = newTexture;

		return updatableTextureHanldeMgr.Dereference(nameToUpdatable[path]);
	}

	SPParticleSystemTexturePtr SPTextureManager::CreateParticleSystemTexture( SPString name, int width, int height )
	{
		nameToUpdatable.Set(name, SPTextureHandle());

		SPParticleSystemTexturePtr newTexture = new SPParticleSystemTexture(name);
		newTexture->CreateRenderTarget(width, height, newTexture->GetBackgroundColor());
		updatableTextureHanldeMgr.Acquire(nameToUpdatable[name]) = newTexture;

		return updatableTextureHanldeMgr.Dereference(nameToUpdatable[name]);
	}

}

