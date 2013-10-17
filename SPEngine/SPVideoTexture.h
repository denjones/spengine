//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoTexture.h the header file of SPVideoTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-21
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPVideo.h"
#include "SPUpdatableTexture.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPVideoTexture class to extend SPTexture class, so that 
	/// it can display a video.
	//////////////////////////////////////////////////////////////////////
	class SPVideoTexture : public SPUpdatableTexture
	{
		friend class SPVideoRenderer;

		SPVideoPtr	video;
		SPString	videoName;
		D3DFORMAT	texture_format;

	public:
		void SetVideo(SPString setName);

	public:
		SPVideoTexture(void);
		SPVideoTexture(SPString setName);
		virtual ~SPVideoTexture(void);

		bool Update(float timeDelta);
		bool Unload();
		bool Reload();

		virtual bool Play();

		virtual bool Pause();

		virtual bool Stop();

	};

	typedef SPPointer<SPVideoTexture> SPVideoTexturePtr;
}


