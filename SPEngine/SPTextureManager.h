//////////////////////////////////////////////////////////////////////////
/// @file		SPTextureManager.h the header file of SPTextureManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPHandleManager.h"
#include "SPTexture.h"
#include "SPHandle.h"
#include "SPSingleton.h"
#include "SPAnimatedTexture.h"
#include "SPComponent.h"
#include "SPStringMap.h"
#include "SPUpdatableTexture.h"
#include "SPVideoTexture.h"
#include "SPParticleSystemTexture.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPTextureManager class to hold and manage textures.
	///
	//////////////////////////////////////////////////////////////////////
	class SPTextureManager : 
		public SPComponent,
		public SPSingleton<SPTextureManager>
	{
		/// @name Inner Type
		/// @{
		//typedef SPHandle<SPTextureTag> SPTextureHandle;
		//typedef SPHandleManager<SPTexture, SPTextureHandle> SPTextureHandleManager;
		//typedef SPHandleManager<SPUpdatableTexture, SPTextureHandle> SPUpdatableTextureHandleManager;
		typedef SPWStringMap<SPTexturePtr> SPTextureMap;
		/// @}

		//SPTextureHandleManager textureHandleMgr;	///< Inner handle manager.
		//SPUpdatableTextureHandleManager updatableTextureHanldeMgr; ///< Inner anime handle manager.
		SPTextureMap textures;					///< String to handle mapping.
		SPTextureMap updatableTextures;				///< String to updatable handle mapping.
			
	public:
		SPTextureManager(void);
		virtual ~SPTextureManager(void);

		/// @name Get texture methods
		/// @{
		SPTexturePtr CreateBlankTexture(SPString path, int width, int height, D3DCOLOR color);
		SPTexturePtr CreateBlankTexture(int width, int height);
		SPTexturePtr GetBlankWhiteTexture();
		SPTexturePtr CreateRenderTarget(int width, int height, D3DCOLOR color);
		SPParticleSystemTexturePtr CreateParticleSystemTexture(SPString name, int width, int height);
		SPTexturePtr GetTexture(SPString path);
		SPAnimatedTexturePtr GetAnime(SPString path);
		SPVideoTexturePtr GetVideo(SPString path);
		SPParticleSystemTexturePtr GetParticleSystem(SPString path);
		SPAnimatedTexturePtr GetAnime(SPString path, int setRow, int setColumn, int setFPS);
		/// @}

		/// @name Release methods
		/// @{
		void ReleaseTexture(SPString path);
		void ReleaseUpdatable(SPString path);
		/// @}

		/// @name Component methods
		/// @{
		bool Update(float timeDelta);
		bool Unload();
		//bool Load();
		bool Reload();
		/// @}
	};
}


