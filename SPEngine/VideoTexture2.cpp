#include "StdAfx.h"
#include "VideoTexture2.h"
#include <dshowutil.h>
#include "VideoRenderer2.h"
#include "VideoManager.h"
#include "SPGame.h"

namespace SPEngine
{
	VideoTexture2::VideoTexture2(void)
	{
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2 constructor.
	//-----------------------------------------------------------------------------

	VideoTexture2::VideoTexture2(HWND hwndVideo) :
		m_state(STATE_CLOSED),
		m_hwndVideo(hwndVideo),
		m_hwndEvent(NULL),
		m_EventMsg(0),
		m_pGraph(NULL),
		m_pControl(NULL),
		m_pEvent(NULL),
		m_pSeek(NULL),
		m_pAudio(NULL),
		m_pVideo(NULL),
		m_pRenderer(NULL),
		m_seekCaps(0),
		m_bMute(FALSE),
		m_lVolume(MAX_VOLUME)
	{


	}

	//-----------------------------------------------------------------------------
	// VideoTexture2 destructor.
	//-----------------------------------------------------------------------------

	VideoTexture2::~VideoTexture2()
	{
		TearDownGraph();
	}



	//-----------------------------------------------------------------------------
	// VideoTexture2::SetEventWindow
	// Description: Set the window to receive graph events.
	//
	// hwnd: Window to receive the events.
	// msg: Private window message that window will receive whenever a 
	//      graph event occurs. (Must be in the range WM_APP through 0xBFFF.)
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::SetEventWindow(HWND hwnd, UINT msg)
	{
		m_hwndEvent = hwnd;
		m_EventMsg = msg;
		return S_OK;
	}


	//-----------------------------------------------------------------------------
	// VideoTexture2::OpenFile
	// Description: Open a new file for playback.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::OpenFile(VideoManager* manager, const WCHAR* sFileName)
	{
		spriteManager3D = manager;
		g_pd3dDevice = manager->CurrentGame()->GetDevice();

		HRESULT hr = S_OK;

		IBaseFilter *pSource = NULL;

		// Create a new filter graph. (This also closes the old one, if any.)
		hr = InitializeGraph();

		// Create the Texture Renderer object
		VideoRenderer2 *pCTR = NULL;
		if (SUCCEEDED(hr))
		{
			pCTR = new VideoRenderer2(this, NULL, &hr);
		}	

		// Add the render filter to the graph.
		if (SUCCEEDED(hr))
		{
			m_pRenderer = pCTR;
			hr = m_pGraph->AddFilter(m_pRenderer, L"TEXTURERENDERER");
		}
	
		// Add the source filter to the graph.
		if (SUCCEEDED(hr))
		{
			hr = m_pGraph->AddSourceFilter(sFileName, NULL, &pSource);
		}

		// Try to render the streams.
		if (SUCCEEDED(hr))
		{
			hr = RenderStreams(pSource);
		}

		// Get the seeking capabilities.
		if (SUCCEEDED(hr))
		{
			hr = m_pSeek->GetCapabilities(&m_seekCaps);
		}

		// Set the volume.
		if (SUCCEEDED(hr))
		{
			hr = UpdateVolume();
		}

		// Update our state.
		if (SUCCEEDED(hr))
		{
			m_state = STATE_STOPPED;
		}

		SAFE_RELEASE(pSource);

		return hr;
	}



	//-----------------------------------------------------------------------------
	// VideoTexture2::HandleGraphEvent
	// Description: Respond to a graph event.
	//
	// The owning window should call this method when it receives the window
	// message that the application specified when it called SetEventWindow.
	//
	// pCB: Pointer to the GraphEventCallback callback, implemented by 
	//      the application. This callback is invoked once for each event
	//      in the queue. 
	//
	// Caution: Do not tear down the graph from inside the callback.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::HandleGraphEvent(GraphEventCallback *pCB)
	{
		if (pCB == NULL)
		{
			return E_POINTER;
		}

		if (!m_pEvent)
		{
			return E_UNEXPECTED;
		}

		long evCode = 0;
		LONG_PTR param1 = 0, param2 = 0;

		HRESULT hr = S_OK;

		// Get the events from the queue.
		while (SUCCEEDED(m_pEvent->GetEvent(&evCode, &param1, &param2, 0)))
		{
			// Invoke the callback.
			pCB->OnGraphEvent(evCode, param1, param2);

			// Free the event data.
			hr = m_pEvent->FreeEventParams(evCode, param1, param2);
			if (FAILED(hr))
			{
				break;
			}
		}

		return hr;
	}


	// state changes

	HRESULT VideoTexture2::Play()
	{
		if (m_state != STATE_PAUSED && m_state != STATE_STOPPED)
		{
			return VFW_E_WRONG_STATE;
		}

		assert(m_pGraph); // If state is correct, the graph should exist.

		HRESULT hr = m_pControl->Run();

		if (SUCCEEDED(hr))
		{
			m_state = STATE_RUNNING;
		}

		return hr;
	}

	HRESULT VideoTexture2::Pause()
	{
		if (m_state != STATE_RUNNING)
		{
			return VFW_E_WRONG_STATE;
		}

		assert(m_pGraph); // If state is correct, the graph should exist.

		HRESULT hr = m_pControl->Pause();

		if (SUCCEEDED(hr))
		{
			m_state = STATE_PAUSED;
		}

		return hr;
	}


	HRESULT VideoTexture2::Stop()
	{
		if (m_state != STATE_RUNNING && m_state != STATE_PAUSED)
		{
			return VFW_E_WRONG_STATE;
		}

		assert(m_pGraph); // If state is correct, the graph should exist.

		HRESULT hr = m_pControl->Stop();

		if (SUCCEEDED(hr))
		{
			m_state = STATE_STOPPED;
		}

		return hr;
	}


	// EVR/VMR functionality


	BOOL VideoTexture2::HasVideo() const
	{
		return (m_pVideo && m_pVideo->HasVideo());
	}


	//-----------------------------------------------------------------------------
	// VideoTexture2::UpdateVideoWindow
	// Description: Sets the destination rectangle for the video.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::UpdateVideoWindow(const LPRECT prc)
	{
		HRESULT hr = S_OK;

		if (m_pVideo)
		{
			hr = m_pVideo->UpdateVideoWindow(m_hwndVideo, prc);
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::Repaint
	// Description: Repaints the video.
	//
	// Call this method when the application receives WM_PAINT.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::Repaint(HDC hdc)
	{
		HRESULT hr = S_OK;

		if (m_pVideo)
		{
			hr = m_pVideo->Repaint(m_hwndVideo, hdc);
		}

		return hr;
	}


	//-----------------------------------------------------------------------------
	// VideoTexture2::DisplayModeChanged
	// Description: Notifies the VMR that the display mode changed.
	//
	// Call this method when the application receives WM_DISPLAYCHANGE.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::DisplayModeChanged()
	{
		HRESULT hr = S_OK;

		if (m_pVideo)
		{
			hr = m_pVideo->DisplayModeChanged();
		}

		return hr;
	}

	// Seeking


	//-----------------------------------------------------------------------------
	// VideoTexture2::CanSeek
	// Description: Returns TRUE if the current file is seekable.
	//-----------------------------------------------------------------------------

	BOOL VideoTexture2::CanSeek() const
	{
		const DWORD caps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;
		return ((m_seekCaps & caps) == caps);
	}


	//-----------------------------------------------------------------------------
	// VideoTexture2::SetPosition
	// Description: Seeks to a new position.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::SetPosition(REFERENCE_TIME pos)
	{
		if (m_pControl == NULL || m_pSeek == NULL)
		{
			return E_UNEXPECTED;
		}

		HRESULT hr = S_OK;

		hr = m_pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
			NULL, AM_SEEKING_NoPositioning);

		if (SUCCEEDED(hr))
		{
			// If playback is stopped, we need to put the graph into the paused
			// state to update the video renderer with the new frame, and then stop 
			// the graph again. The IMediaControl::StopWhenReady does this.
			if (m_state == STATE_STOPPED)
			{
				hr = m_pControl->StopWhenReady();
			}
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::GetDuration
	// Description: Gets the duration of the current file.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::GetDuration(LONGLONG *pDuration)
	{
		if (m_pSeek == NULL)
		{
			return E_UNEXPECTED;
		}

		return m_pSeek->GetDuration(pDuration);
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::GetCurrentPosition
	// Description: Gets the current playback position.
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::GetCurrentPosition(LONGLONG *pTimeNow)
	{
		if (m_pSeek == NULL)
		{
			return E_UNEXPECTED;
		}

		return m_pSeek->GetCurrentPosition(pTimeNow);
	}


	// Audio

	//-----------------------------------------------------------------------------
	// VideoTexture2::Mute
	// Description: Mutes or unmutes the audio.
	//-----------------------------------------------------------------------------

	HRESULT	VideoTexture2::Mute(BOOL bMute)
	{
		m_bMute = bMute;
		return UpdateVolume();
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::SetVolume
	// Description: Sets the volume. 
	//-----------------------------------------------------------------------------

	HRESULT	VideoTexture2::SetVolume(long lVolume)
	{
		m_lVolume = lVolume;
		return UpdateVolume();
	}


	//-----------------------------------------------------------------------------
	// VideoTexture2::UpdateVolume
	// Description: Update the volume after a call to Mute() or SetVolume().
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::UpdateVolume()
	{
		HRESULT hr = S_OK;

		if (m_bAudioStream && m_pAudio)
		{
			// If the audio is muted, set the minimum volume. 
			if (m_bMute)
			{
				hr = m_pAudio->put_Volume(MIN_VOLUME);
			}
			else
			{
				// Restore previous volume setting
				hr = m_pAudio->put_Volume(m_lVolume);
			}
		}

		return hr;
	}




	// Graph building


	//-----------------------------------------------------------------------------
	// VideoTexture2::InitializeGraph
	// Description: Create a new filter graph. (Tears down the old graph.) 
	//-----------------------------------------------------------------------------

	HRESULT VideoTexture2::InitializeGraph()
	{
		HRESULT hr = S_OK;

		TearDownGraph();

		// Create the Filter Graph Manager.
		hr = CoCreateInstance(
			CLSID_FilterGraph, 
			NULL, 
			CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder,
			(void**)&m_pGraph
			);

		// Query for graph interfaces.
		if (SUCCEEDED(hr))
		{
			hr = m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pControl);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pGraph->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);
		}

		// Set up event notification.
		if (SUCCEEDED(hr))
		{
			hr = m_pEvent->SetNotifyWindow((OAHWND)m_hwndEvent, m_EventMsg, NULL);
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::TearDownGraph
	// Description: Tear down the filter graph and release resources. 
	//-----------------------------------------------------------------------------

	void VideoTexture2::TearDownGraph()
	{
		// Stop sending event messages
		if (m_pEvent)
		{
			m_pEvent->SetNotifyWindow((OAHWND)NULL, NULL, NULL);
		}

		SAFE_RELEASE(m_pGraph);
		SAFE_RELEASE(m_pControl);
		SAFE_RELEASE(m_pEvent);
		SAFE_RELEASE(m_pSeek);
		SAFE_RELEASE(m_pAudio);
		SAFE_DELETE(m_pRenderer);
		SAFE_DELETE(m_pVideo);

		m_state = STATE_CLOSED;
		m_seekCaps = 0;

		m_bAudioStream = FALSE;
	}


	HRESULT VideoTexture2::CreateVideoRenderer()
	{
		HRESULT hr = E_FAIL;

		enum { Try_EVR, Try_VMR9, Try_VMR7 };

		for (DWORD i = Try_EVR; i <= Try_VMR7; i++)
		{
			switch (i)
			{
			case Try_EVR:
				m_pVideo = new EVR();
				break;

			case Try_VMR9:
				m_pVideo = new VMR9();
				break;

			case Try_VMR7:
				m_pVideo = new VMR7();
				break;
			}

			if (m_pVideo == NULL)
			{
				hr = E_OUTOFMEMORY;
				break;
			}

			hr = m_pVideo->AddToGraph(m_pGraph, m_hwndVideo);
			if (SUCCEEDED(hr))
			{
				break;
			}

			SAFE_DELETE(m_pVideo);
		}

		if (FAILED(hr))
		{
			SAFE_DELETE(m_pVideo);
		}
		return hr;
	}



	//-----------------------------------------------------------------------------
	// VideoTexture2::RenderStreams
	// Description: Render the streams from a source filter. 
	//-----------------------------------------------------------------------------

	HRESULT	VideoTexture2::RenderStreams(IBaseFilter *pSource)
	{
		HRESULT hr = S_OK;

		BOOL bRenderedAnyPin = FALSE;

		IFilterGraph2 *pGraph2 = NULL;
		IEnumPins *pEnum = NULL;
		IBaseFilter *pAudioRenderer = NULL;

		hr = m_pGraph->QueryInterface(IID_IFilterGraph2, (void**)&pGraph2);

		// Add the video renderer to the graph
		if (SUCCEEDED(hr))
		{
			//hr = CreateVideoRenderer();
		}

		// Add the DSound Renderer to the graph.
		if (SUCCEEDED(hr))
		{
			hr = AddFilterByCLSID(m_pGraph, CLSID_DSoundRender, &pAudioRenderer, L"Audio Renderer");
		}

		// Enumerate the pins on the source filter.
		if (SUCCEEDED(hr))
		{
			hr = pSource->EnumPins(&pEnum);
		}

		if (SUCCEEDED(hr))
		{
			// Loop through all the pins
			IPin *pPin = NULL;

			while (S_OK == pEnum->Next(1, &pPin, NULL))
			{			
				// Try to render this pin. 
				// It's OK if we fail some pins, if at least one pin renders.
				HRESULT hr2 = pGraph2->RenderEx(pPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL);

				pPin->Release();

				if (SUCCEEDED(hr2))
				{
					bRenderedAnyPin = TRUE;
				}
			}
		}


		// Remove un-used renderers.

		// Try to remove the VMR.
		//if (SUCCEEDED(hr))
		//{
		//	hr = m_pVideo->FinalizeGraph(m_pGraph);
		//}

		// Try to remove the audio renderer.
		if (SUCCEEDED(hr))
		{
    		BOOL bRemoved = FALSE;
			hr = RemoveUnconnectedRenderer(m_pGraph, pAudioRenderer, &bRemoved);

			if (bRemoved)
			{
				m_bAudioStream = FALSE;
			}
			else
			{
				m_bAudioStream = TRUE;
			}
		}

		SAFE_RELEASE(pEnum);
		//SAFE_RELEASE(pVMR);
		SAFE_RELEASE(pAudioRenderer);
		SAFE_RELEASE(pGraph2);

		// If we succeeded to this point, make sure we rendered at least one 
		// stream.
		if (SUCCEEDED(hr))
		{
			if (!bRenderedAnyPin)
			{
				hr = VFW_E_CANNOT_RENDER;
			}
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture2::RemoveUnconnectedRenderer
	// Description: Remove a renderer filter from the graph if the filter is
	//              not connected. 
	//-----------------------------------------------------------------------------

	HRESULT RemoveUnconnectedRenderer(IGraphBuilder *pGraph, IBaseFilter *pRenderer, BOOL *pbRemoved)
	{
		IPin *pPin = NULL;

		BOOL bRemoved = FALSE;

		// Look for a connected input pin on the renderer.

		HRESULT hr = FindConnectedPin(pRenderer, PINDIR_INPUT, &pPin);
		SAFE_RELEASE(pPin);

		// If this function succeeds, the renderer is connected, so we don't remove it.
		// If it fails, it means the renderer is not connected to anything, so
		// we remove it.

		if (FAILED(hr))
		{
			hr = pGraph->RemoveFilter(pRenderer);
			bRemoved = TRUE;
		}

		if (SUCCEEDED(hr))
		{
			*pbRemoved = bRemoved;
		}

		return hr;
	}
}
