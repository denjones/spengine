//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoTexture.h the header file of SPVideoTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-21
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPVideo.h"
#include "SPTexture.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPVideoTexture class to extend SPTexture class, so that 
	/// it can display a video.
	//////////////////////////////////////////////////////////////////////
	class SPVideoTexture : public SPTexture
	{
		friend class SPVideoRenderer;

		SPVideoPtr	video;
		SPString	videoName;
		D3DFORMAT	texture_format;

	public:
		void SetVideo(SPString setName);
		SPVideoPtr GetVideo();

	public:
		SPVideoTexture(void);
		SPVideoTexture(SPString setName);
		virtual ~SPVideoTexture(void);

		void Update(float timeDelta);
		void Unload();
		void Reload();

		virtual void Play();
		virtual void Pause();
		virtual void Stop();

		virtual SPString GetTextureType();

	};

	typedef SPPointer<SPVideoTexture> SPVideoTexturePtr;
}


