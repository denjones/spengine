//////////////////////////////////////////////////////////////////////////
/// @file		SPVideo.h the header file of SPVideo class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <smartptr.h>
#include "SPPointer.h"
#include "SPDShowData.h"
#include "ISPLoadable.h"
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	class SPVideoTexture;

	enum PlaybackState
	{
		STATE_RUNNING,
		STATE_PAUSED,
		STATE_STOPPED,
		STATE_CLOSED
	};

	class SPVideo;

	class SPVideoEventCallback : public GraphEventCallback
	{
		SPVideo* currentVideo;
	public:

		SPVideoEventCallback(SPVideo* setVideo);
		virtual bool OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2);
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief SPVideo to represent a video object.
	/// Can be used with a SPVideoTexturePtr to present video frame.
	/// Audio is also supported.
	///
	//////////////////////////////////////////////////////////////////////
	class SPVideo : public ISPLoadable
	{
		friend class SPVideoEventCallback;

		PlaybackState	state;
		SPDShowDataPtr  data;
		SPVideoEventCallback* callBack;
		SPString		videoPath;
		int				leftTimes;

	public:
		PlaybackState State() const { return state; }

	public:
		SPVideo(void);
		SPVideo(SPString path);
		virtual ~SPVideo(void);			

		void OpenFile(SPString sFileName);
		void Load();
		void Unload();
		void Reload();
	
		// Streaming
		void Play();		
		void Pause();
		void Stop();
		void SetLoopTimes(int times);
		int GetLeftTime() { return leftTimes; }

		// seeking
		bool	CanSeek();
		void SetPosition(REFERENCE_TIME pos);
		long long GetDuration();
		long long GetCurrentPosition();

		// Audio
		void	Mute(bool bMute);
		bool	IsMuted();
		void	SetVolume(float fVolume);
		float	GetVolume();

		float	GetPlayingPosition();
		bool	IsPlaying();
		void	UpdateFrame();
		void	SetTexture(SPVideoTexture* setTex);
		void	ResizeTexture();

		void	SetFlipVertical(bool setFlip);
		bool	IsFilpVertical() { return data->IsFilpVertical(); }

		SPString GetPath() { return videoPath; }
	};

	typedef SPPointer<SPVideo> SPVideoPtr;
}

