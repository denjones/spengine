#include "StdAfx.h"
#include "SPVideo.h"
#include <dshowutil.h>
#include "SPVideoRenderer.h"
#include "SPGame.h"
#include "SPDevice.h"
#include "SPStringHelper.h"
#include "SPWindow.h"

namespace SPEngine
{
	SPVideo::SPVideo(void) :
		state(STATE_CLOSED),
		leftTimes(0)
	{
		data = new SPDShowData();
		callBack = new SPVideoEventCallback(this);
		Load();
	}

	SPVideo::SPVideo( SPString path ) :
		state(STATE_CLOSED),
		leftTimes(0)
	{
		data = new SPDShowData();
		callBack = new SPVideoEventCallback(this);
		Load();
		OpenFile(path);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture destructor.
	//-----------------------------------------------------------------------------

	SPVideo::~SPVideo()
	{
		delete callBack;
		callBack = NULL;
		Unload();
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::OpenFile
	// Description: Open a new file for playback.
	//-----------------------------------------------------------------------------

	bool SPVideo::OpenFile(SPString sFileName)
	{
		videoPath = sFileName;

		if (data->AddSource(sFileName))
		{
			state = STATE_STOPPED;
			return true;
		}

		return false;
	}

	// state changes
	HRESULT SPVideo::Play()
	{
		if (state != STATE_PAUSED && state != STATE_STOPPED)
		{
			return VFW_E_WRONG_STATE;
		}

		assert(data->GetGraph()); // If state is correct, the graph should exist.

		data->LockControl();

		HRESULT hr = data->GetControl()->Run();

		data->UnlockControl();

		if (SUCCEEDED(hr))
		{
			state = STATE_RUNNING;
		}

		return hr;
	}

	HRESULT SPVideo::Pause()
	{
		if (state != STATE_RUNNING)
		{
			return VFW_E_WRONG_STATE;
		}

		assert(data->GetGraph()); // If state is correct, the graph should exist.

		data->LockControl();

		HRESULT hr = data->GetControl()->Pause();

		data->UnlockControl();

		if (SUCCEEDED(hr))
		{
			state = STATE_PAUSED;
		}

		return hr;
	}


	HRESULT SPVideo::Stop()
	{
		if (state != STATE_RUNNING && state != STATE_PAUSED)
		{
			return VFW_E_WRONG_STATE;
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

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::CanSeek
	// Description: Returns TRUE if the current file is seekable.
	//-----------------------------------------------------------------------------

	BOOL SPVideo::CanSeek() 
	{
		const DWORD caps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;
		return ((data->GetSeekCap() & caps) == caps);
	}


	//-----------------------------------------------------------------------------
	// VideoTexture::SetPosition
	// Description: Seeks to a new position.
	//-----------------------------------------------------------------------------

	HRESULT SPVideo::SetPosition(REFERENCE_TIME pos)
	{
		if (!data->GetControl()  || !data->GetSeek())
		{
			return E_UNEXPECTED;
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

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::GetDuration
	// Description: Gets the duration of the current file.
	//-----------------------------------------------------------------------------

	HRESULT SPVideo::GetDuration(LONGLONG *pDuration)
	{
		if (!data->GetSeek() || FAILED(data->GetSeek()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME)))
		{
			return E_UNEXPECTED;
		}
		
		return data->GetSeek()->GetDuration(pDuration);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::GetCurrentPosition
	// Description: Gets the current playback position.
	//-----------------------------------------------------------------------------

	HRESULT SPVideo::GetCurrentPosition(LONGLONG *pTimeNow)
	{
		if (!data->GetSeek() || FAILED(data->GetSeek()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME)))
		{
			return E_UNEXPECTED;
		}

		return data->GetSeek()->GetCurrentPosition(pTimeNow);
	}


	// Audio

	//-----------------------------------------------------------------------------
	// VideoTexture::Mute
	// Description: Mutes or unmutes the audio.
	//-----------------------------------------------------------------------------

	HRESULT	SPVideo::Mute(BOOL bMute)
	{
		return data->SetMute(bMute == TRUE);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::SetVolume
	// Description: Sets the volume. 
	//-----------------------------------------------------------------------------

	HRESULT	SPVideo::SetVolume(long lVolume)
	{
		return data->SetVolume(lVolume);
	}

	// Graph building
	float SPVideo::GetPlayingPosition()
	{
		LONGLONG position;
		GetCurrentPosition(&position);

		LONGLONG duration;
		GetDuration(&duration);

		float playingPosititon = (float)position / duration;

		return playingPosititon;
	}

	bool SPVideo::IsPlaying()
	{
		return state == STATE_RUNNING;
	}

	bool SPVideo::UpdateFrame()
	{
		data->HandleGraphEvent(callBack);

		if (state == STATE_RUNNING)
		{
			data->GetRenderer()->UpdateTexture();
		}

		return true;
	}

	bool SPVideo::SetTexture( SPVideoTexture* setTex )
	{
		data->GetRenderer()->SetTexture(setTex);

		return false;
	}

	bool SPVideo::ResizeTexture()
	{
		return data->GetRenderer()->ResizeTexture();
	}

	bool SPVideo::Load()
	{
		return data->Load();
	}

	bool SPVideo::Unload()
	{
		state = STATE_CLOSED;

		return data->Unload();
	}

	bool SPVideo::Reload()
	{
		data->Unload();

		data->Load();

		return OpenFile(videoPath);
	}

	HRESULT SPVideo::SetLoopTimes( int times )
	{
		leftTimes = times;

		return S_OK;
	}

	bool SPVideo::SetFlipVertical( bool setFlip )
	{
		return data->SetFlipVertical(setFlip);
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
