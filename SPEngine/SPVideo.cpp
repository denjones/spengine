#include "StdAfx.h"
#include "SPVideo.h"
#include <dshowutil.h>
#include "SPVideoRenderer.h"
#include "SPGame.h"
#include "SPDevice.h"
#include "SPStringHelper.h"
#include "SPWindow.h"
#include <exception>

namespace SPEngine
{
	SPVideo::SPVideo(void) :
		state(STATE_CLOSED),
		leftTimes(0)
	{
		data = new SPDShowData();
		callBack = new SPVideoEventCallback(this);
	}

	SPVideo::SPVideo( SPString path ) :
		state(STATE_CLOSED),
		leftTimes(0)
	{
		data = new SPDShowData();
		callBack = new SPVideoEventCallback(this);
		OpenFile(path);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture destructor.
	//-----------------------------------------------------------------------------

	SPVideo::~SPVideo()
	{
		Stop();
		delete callBack;
		callBack = NULL;
		Unload();
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::OpenFile
	// Description: Open a new file for playback.
	//-----------------------------------------------------------------------------

	void SPVideo::OpenFile(SPString sFileName)
	{
		//Load();

		videoPath = sFileName;

		if (data->Load(sFileName))
		{
			state = STATE_STOPPED;
		}
	}

	// state changes
	void SPVideo::Play()
	{
		if (state != STATE_PAUSED && state != STATE_STOPPED)
		{
			//throw exception("VFW_E_WRONG_STATE");
			return;
		}

		assert(data->GetGraph()); // If state is correct, the graph should exist.

		data->LockControl();

		HRESULT hr = data->GetControl()->Run();

		data->UnlockControl();

		if (SUCCEEDED(hr))
		{
			state = STATE_RUNNING;
		}
	}

	void SPVideo::Pause()
	{
		if (state != STATE_RUNNING)
		{
			//throw exception("VFW_E_WRONG_STATE");
			return;
		}

		assert(data->GetGraph()); // If state is correct, the graph should exist.

		data->LockControl();

		HRESULT hr = data->GetControl()->Pause();

		data->UnlockControl();

		if (SUCCEEDED(hr))
		{
			state = STATE_PAUSED;
		}
	}


	void SPVideo::Stop()
	{
		if (state != STATE_RUNNING && state != STATE_PAUSED)
		{
			//throw exception("VFW_E_WRONG_STATE");
			return;
		}

		assert(data->GetGraph()); // If state is correct, the graph should exist.

		data->LockControl();

		HRESULT hr = data->GetControl()->Stop();
		//hr = data->GetControl()->StopWhenReady();

		data->UnlockControl();

		SetPosition(0);

		if (SUCCEEDED(hr))
		{
			state = STATE_STOPPED;
		}
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::CanSeek
	// Description: Returns TRUE if the current file is seekable.
	//-----------------------------------------------------------------------------

	bool SPVideo::CanSeek() 
	{
		const DWORD caps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;
		return ((data->GetSeekCap() & caps) == caps);
	}


	//-----------------------------------------------------------------------------
	// VideoTexture::SetPosition
	// Description: Seeks to a new position.
	//-----------------------------------------------------------------------------

	void SPVideo::SetPosition(REFERENCE_TIME pos)
	{
		if (!data->GetControl()  || !data->GetSeek())
		{
			//throw exception("E_UNEXPECTED");
			return;
		}

		HRESULT hr = S_OK;

		LONGLONG lFrame = 0;

		if(SUCCEEDED(data->GetSeek()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME)))
		{
			data->GetSeek()->GetDuration(&lFrame);
			hr = data->GetSeek()->SetPositions(&pos,
				AM_SEEKING_AbsolutePositioning | AM_SEEKING_Segment ,
				&lFrame, AM_SEEKING_AbsolutePositioning);
		}


		if (SUCCEEDED(hr))
		{
			// If playback is stopped, we need to put the graph into the paused
			// state to update the video renderer with the new frame, and then stop 
			// the graph again. The IMediaControl::StopWhenReady does this.
			if (state == STATE_STOPPED)
			{
				data->LockControl();

				hr = data->GetControl()->StopWhenReady();

				data->UnlockControl();
			}
		}
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::GetDuration
	// Description: Gets the duration of the current file.
	//-----------------------------------------------------------------------------

	long long SPVideo::GetDuration()
	{
		long long duration;
		if (!data->GetSeek() || FAILED(data->GetSeek()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME)))
		{
			throw exception("E_UNEXPECTED");
		}
		data->GetSeek()->GetDuration(&duration);
		return duration;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::GetCurrentPosition
	// Description: Gets the current playback position.
	//-----------------------------------------------------------------------------

	long long SPVideo::GetCurrentPosition()
	{
		long long timeNow;
		if (!data->GetSeek() || FAILED(data->GetSeek()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME)))
		{
			throw exception("E_UNEXPECTED");
		}
		data->GetSeek()->GetCurrentPosition(&timeNow);
		return timeNow;
	}


	// Audio

	//-----------------------------------------------------------------------------
	// VideoTexture::Mute
	// Description: Mutes or unmutes the audio.
	//-----------------------------------------------------------------------------

	void SPVideo::Mute(bool bMute)
	{
		data->SetMute(bMute);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::SetVolume
	// Description: Sets the volume. 
	//-----------------------------------------------------------------------------

	void SPVideo::SetVolume(float fVolume)
	{
		data->SetVolume(fVolume);
	}

	// Graph building
	float SPVideo::GetPlayingPosition()
	{
		long long position = GetCurrentPosition();
		long long duration = GetDuration();
		float playingPosititon = (float)position / duration;
		return playingPosititon;
	}

	bool SPVideo::IsPlaying()
	{
		return state == STATE_RUNNING;
	}

	void SPVideo::UpdateFrame()
	{
		data->HandleGraphEvent(callBack);

		if (state == STATE_RUNNING)
		{
			data->GetRenderer()->UpdateTexture();
		}
	}

	void SPVideo::SetTexture( SPVideoTexture* setTex )
	{
		if(data->GetRenderer())
		{
			data->GetRenderer()->SetTexture(setTex);
		}
	}

	void SPVideo::ResizeTexture()
	{
		data->GetRenderer()->ResizeTexture();
	}

	void SPVideo::Load()
	{
		//data->Load();
	}

	void SPVideo::Unload()
	{
		state = STATE_CLOSED;
		data->Unload();
	}

	void SPVideo::Reload()
	{
		data->Unload();
		//data->Load();
		OpenFile(videoPath);
	}

	void SPVideo::SetLoopTimes( int times )
	{
		leftTimes = times;
	}

	void SPVideo::SetFlipVertical( bool setFlip )
	{
		data->SetFlipVertical(setFlip);
	}

	bool SPVideo::IsMuted()
	{
		return data->IsMuted();
	}

	float SPVideo::GetVolume()
	{
		return data->GetVolume();
	}

	bool SPVideoEventCallback::OnGraphEvent( long eventCode, LONG_PTR param1, LONG_PTR param2 )
	{
		switch(eventCode)
		{
			case EC_COMPLETE:
			{
				currentVideo->Stop();
				if (currentVideo->leftTimes > 0)
				{
					currentVideo->leftTimes--;
					currentVideo->Play();
					return false;
				}
				else if (currentVideo->leftTimes < 0)
				{
					currentVideo->Play();
					return false;
				}
			}
			//case EC_END_OF_SEGMENT:
			//{
			//	currentVideo->Play();				
			//}
		}

		return true;
	}

	SPVideoEventCallback::SPVideoEventCallback( SPVideo* setVideo )
	{
		currentVideo = setVideo;
	}

}
