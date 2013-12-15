//////////////////////////////////////////////////////////////////////////
/// @file		SPDShowData.cpp SPDShowData class.
/// @author		Ken.J
/// @version	Beta 0.9
/// @date		2013-12-14
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPDShowData.h"
#include "SPLogHelper.h"
#include <dshowutil.h>
#include "SPStringHelper.h"
#include <strmif.h>
#include "SPWindow.h"
#include "SPLavFilterFactory.h"

namespace SPEngine
{
	SPDShowData::SPDShowData() :
		m_hwndVideo(SPWindow::GetSingleton().GetHWnd()),
		m_hwndEvent(NULL),
		m_EventMsg(0),
		m_pGraph(NULL),
		m_pControl(NULL),
		m_pEvent(NULL),
		m_pSeek(NULL),
		m_pAudio(NULL),
		m_pRenderer(NULL),
		m_pSource(NULL),
		m_seekCaps(0),
		m_bMute(FALSE),
		m_lVolume(MAX_VOLUME),
		m_bControlling(false),
		m_bFilpVertical(false)
	{}

	SPDShowData::~SPDShowData()
	{
		Unload();
	}

	/// @brief Get an unconnected pin of a filter
	IPin* GetPin(IBaseFilter *pFilter, PIN_DIRECTION dir)
	{
		IEnumPins* pEnumPins;
		IPin* pOutpin;
		PIN_DIRECTION pDir;
		pFilter->EnumPins(&pEnumPins);
		while (pEnumPins->Next(1,&pOutpin,NULL) == S_OK)
		{
			pOutpin->QueryDirection(&pDir);
			if (pDir == dir)
			{
				IPin *pTmp=0;
				HRESULT hr=pOutpin->ConnectedTo(&pTmp);
				if (SUCCEEDED(hr))
				{
					;
				}
				else    
				{
					pEnumPins->Release();
					return pOutpin;
				}
			}
			pOutpin->Release();
		}
		pEnumPins->Release();
		return 0;
	}


	bool SPDShowData::Load(SPString fileName)
	{
		Unload();

		IBaseFilter *pLAVSplitter = NULL;
		IBaseFilter *pLAVVideo = NULL;
		IBaseFilter *pLAVAudio = NULL;
		IBaseFilter *pAudioRenderer = NULL;
		SPVideoRenderer *pVideoRenderer = NULL;

		HRESULT hr = S_OK;

		// Initialize COM.
		hr = S_OK;//CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to initialize com!");
			return false;
		}

		//
		// Create filter graph.
		//

		hr = CoCreateInstance(CLSID_FilterGraph, NULL,CLSCTX_INPROC, IID_IFilterGraph, (void**)&m_pBase);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create filter graph!");
			return false;
		}

		//
		// Create source filter.
		//

		m_pSource = new SPFileSourceFilter(NULL, &hr);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create source filter!");
			return false;
		}

		//
		// Add source filter.
		//

		hr = m_pBase->AddFilter(m_pSource, NULL);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to add source filter to filter graph!");
			return false;
		}

		hr = m_pSource->Load(fileName.c_str(), NULL);
		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to load source file!");
			return false;
		}

		//
		// Create the filter graph builder.
		//

		hr = m_pBase->QueryInterface(IID_IGraphBuilder, (void**)&m_pGraph);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to query graph builder interface!");
			return false;
		}

		//
		// Add LAV splitter filter
		// 
				
		SPLavFilterFactory::GetSingleton().CreateLAVSplitter(pLAVSplitter);

		if (!pLAVSplitter)
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Splitter filter to filter graph!");
		}
		else
		{
			hr = m_pBase->AddFilter(pLAVSplitter, L"LAV Splitter");

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Splitter filter to filter graph!");
			}
		}								

		//
		// Add LAV Video filter
		// 		
		
		SPLavFilterFactory::GetSingleton().CreateLAVVideo(pLAVVideo);

		if (!pLAVVideo)
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Video filter to filter graph!");
		}
		else
		{
			hr = m_pBase->AddFilter(pLAVVideo,L"LAV Splitter");

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Video filter to filter graph!");
			}
		}

		//
		// Add LAV Audio filter
		// 

		SPLavFilterFactory::GetSingleton().CreateLAVAudio(pLAVAudio);

		if (!pLAVAudio)
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Audio filter to filter graph!");
		}
		else
		{
			hr = m_pBase->AddFilter(pLAVAudio,L"LAV Splitter");

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Audio filter to filter graph!");
			}
		}

		//
		// Add the DSound Renderer to the graph.
		//

		if (SUCCEEDED(hr))
		{
			hr = AddFilterByCLSID(m_pGraph, CLSID_DSoundRender, &pAudioRenderer, L"Audio Renderer");

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[DShow] WARNING: Failed to add DSound Renderer to filter graph!");
			}
		}

		//
		// Create the Texture Renderer object
		//

		pVideoRenderer = new SPVideoRenderer(this, NULL, &hr);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create video renderer!");
		}
		else
		{
			// Add the render filter to the graph.

			m_pRenderer = pVideoRenderer;
			hr = m_pBase->AddFilter(m_pRenderer, L"TEXTURERENDERER");
			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[DShow] ERROR: Failed to add the video renderer!");
			}
		}

		//
		// Query for graph interfaces.
		//

		if (SUCCEEDED(hr))
		{
			hr = m_pBase->QueryInterface(IID_IMediaControl, (void**)&m_pControl);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pBase->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pBase->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pBase->QueryInterface(IID_IBasicAudio, (void**)&m_pAudio);
		}

		//
		// Set up event notification.
		//

		if (SUCCEEDED(hr))
		{
			hr = m_pEvent->SetNotifyWindow((OAHWND)m_hwndEvent, m_EventMsg, NULL);
		}

		//
		// Try to connect filters automatically.
		//

		if (SUCCEEDED(hr))
		{
			hr = RenderStreams(m_pSource);

			if (FAILED(hr))
			{
				//
				// If failed to auto connect, try to connect pins manually.
				//

				SPLogHelper::WriteLog("[DShow] ERROR: Failed to render source stream! Trying to connect pins manually...");

				//
				// Connect source filter and splitter filter.
				//

				IPin* pFileOut = GetPin(m_pSource, PINDIR_OUTPUT);
				if (pFileOut!= NULL)
				{
					// Is the pin unconnected? Obtain the input pin of the Splitter.

					IPin* pSplitterIn = GetPin(pLAVSplitter, PINDIR_INPUT);
					if (pSplitterIn!= NULL)
					{
						// Is the pin good? Connect the pins.

						hr = m_pGraph->ConnectDirect(pFileOut, pSplitterIn, NULL);
					}
				}

				//
				// Connect splitter filter and video decoder filter.
				//

				if (SUCCEEDED(hr))
				{
					IPin* pSplitterOut1= GetPin(pLAVSplitter,PINDIR_OUTPUT);
					if (pSplitterOut1!= NULL)
					{
						IPin* pVideoDecIn = GetPin(pLAVVideo, PINDIR_INPUT);
						if (pVideoDecIn!= NULL)
						{ 
							hr = m_pGraph->ConnectDirect(pSplitterOut1, pVideoDecIn, NULL);
						}
					}
				}

				//
				// Connect splitter filter and audio decoder filter.
				//

				if (SUCCEEDED(hr))
				{
					IPin* pSplitterOut2 = GetPin(pLAVSplitter, PINDIR_OUTPUT);
					if (pSplitterOut2!= NULL)
					{ 
						IPin* pAudioDecIn = GetPin(pLAVAudio, PINDIR_INPUT);
						if (pAudioDecIn!= NULL)
						{
							hr = m_pGraph->ConnectDirect(pSplitterOut2, pAudioDecIn, NULL);
						}
					}
				}

				//
				// Connect audio decoder filter and audio renderer filter.
				//

				if (SUCCEEDED(hr))
				{
					IPin* pAudioDecOut = GetPin(pLAVAudio, PINDIR_OUTPUT);
					if (pAudioDecOut!= NULL)
					{ 
						IPin* pAudioRenIn = GetPin(pAudioRenderer, PINDIR_INPUT);
						if (pAudioRenIn!= NULL)
						{ 
							hr = m_pGraph->ConnectDirect(pAudioDecOut, pAudioRenIn, NULL);
						}
					}
				}

				//
				// Connect video decoder filter and video renderer filter.
				//

				if (SUCCEEDED(hr))
				{
					IPin* pVideoColOut = GetPin(pLAVVideo, PINDIR_OUTPUT);
					if (pVideoColOut!= NULL)
					{ 
						IPin* pVideoRenIn=GetPin(pVideoRenderer, PINDIR_INPUT);
						if (pVideoRenIn!= NULL)
						{ 
							hr = m_pGraph->ConnectDirect(pVideoColOut,pVideoRenIn,NULL);
						}
					}
				}

				if(FAILED(hr))
				{
					SAFE_RELEASE(pLAVSplitter);
					SAFE_RELEASE(pLAVVideo);
					SAFE_RELEASE(pLAVAudio);
					SPLogHelper::WriteLog("[DShow] ERROR: Manual connection failed.");
					return false;
				}
			}	
		}

		SAFE_RELEASE(pLAVSplitter);
		SAFE_RELEASE(pLAVVideo);
		SAFE_RELEASE(pLAVAudio);
		SAFE_RELEASE(pAudioRenderer);
		//SAFE_RELEASE(pVideoRenderer);

		//
		// Get the seeking capabilities.
		//

		hr = m_pSeek->GetCapabilities(&m_seekCaps);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to get seek capability!");
			return false;
		}

		//
		// Set the volume.
		//

		hr = UpdateVolume();

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to update volume!");
			return false;
		}	

		return SUCCEEDED(hr);
	}

	bool SPDShowData::Unload()
	{
		//
		// Stop sending event messages
		//

		if (m_pEvent)
		{
			m_pEvent->SetNotifyWindow((OAHWND)NULL, NULL, NULL);
		}

		m_pGraph = NULL;
		m_pControl = NULL;
		m_pEvent = NULL;
		m_pSeek = NULL;
		m_pAudio = NULL;
		m_pSource = NULL;

		m_seekCaps = 0;
		//m_bAudioStream = FALSE;

		return true;
	}

	HRESULT	SPDShowData::RenderStreams(SmartPtr<SPFileSourceFilter> pSource)
	{
		HRESULT hr = S_OK;

		BOOL bRenderedAnyPin = FALSE;

		IFilterGraph2 *pGraph2 = NULL;
		IEnumPins *pEnum = NULL;

		hr = m_pGraph->QueryInterface(IID_IFilterGraph2, (void**)&pGraph2);

		//
		// Enumerate the pins on the source filter.
		//

		if (SUCCEEDED(hr))
		{
			hr = pSource->EnumPins(&pEnum);
		}

		if (SUCCEEDED(hr))
		{
			//
			// Loop through all the pins
			//

			IPin *pPin = NULL;

			while (S_OK == pEnum->Next(1, &pPin, NULL))
			{			
				// Try to render this pin. 
				// It's OK if we fail some pins, if at least one pin rendered.

				HRESULT hr2 = pGraph2->RenderEx(pPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL);				

				pPin->Release();

				if (SUCCEEDED(hr2))
				{
					bRenderedAnyPin = TRUE;
					break;
				}
			}
		}

		SAFE_RELEASE(pEnum);
		SAFE_RELEASE(pGraph2);

		//
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
	// VideoTexture::HandleGraphEvent
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

	HRESULT SPDShowData::HandleGraphEvent(GraphEventCallback *pCB)
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
			// Free the event data.
			hr = m_pEvent->FreeEventParams(evCode, param1, param2);

			// Invoke the callback.
			if(!pCB->OnGraphEvent(evCode, param1, param2))
			{
				break;
			}
			
			if (FAILED(hr))
			{
				break;
			}
		}

		return hr;
	}


	//-----------------------------------------------------------------------------
	// VideoTexture::SetEventWindow
	// Description: Set the window to receive graph events.
	//
	// hwnd: Window to receive the events.
	// msg: Private window message that window will receive whenever a 
	//      graph event occurs. (Must be in the range WM_APP through 0xBFFF.)
	//-----------------------------------------------------------------------------

	HRESULT SPDShowData::SetEventWindow(HWND hwnd, UINT msg)
	{
		m_hwndEvent = hwnd;
		m_EventMsg = msg;
		return S_OK;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::UpdateVolume
	// Description: Update the volume after a call to Mute() or SetVolume().
	//-----------------------------------------------------------------------------

	HRESULT SPDShowData::UpdateVolume()
	{
		HRESULT hr = S_OK;

		if (m_pAudio)
		{
			//
			// If the audio is muted, set the minimum volume. 
			//

			if (m_bMute)
			{
				hr = m_pAudio->put_Volume(MIN_VOLUME);
			}
			else
			{
				//
				// Restore previous volume setting
				//

				hr = m_pAudio->put_Volume(m_lVolume);
			}
		}

		return hr;
	}

	void SPDShowData::LockControl()
	{
		controlLock.Lock();

		m_bControlling = true;
	}

	void SPDShowData::UnlockControl()
	{
		m_bControlling = false;

		controlLock.Unlock();
	}

	float SPDShowData::GetPlayingPosition()
	{
		// Very slow, do not call it every frame.

		if (!GetSeek())
		{
			return 1;
		}

		LONGLONG timeNow, duration;

		GetSeek()->GetCurrentPosition(&timeNow);
		GetSeek()->GetDuration(&duration);

		return (float)timeNow / duration;
	}

	bool SPDShowData::IsControlling()
	{
		return m_bControlling;
	}

	bool SPDShowData::SetFlipVertical( bool setFlip )
	{
		m_bFilpVertical = setFlip;

		return true;
	}

	bool SPDShowData::IsFlipVertical()
	{
		return m_bFilpVertical;
	}

	//-----------------------------------------------------------------------------
	// VideoTexture::RemoveUnconnectedRenderer
	// Description: Remove a renderer filter from the graph if the filter is
	//              not connected. 
	//-----------------------------------------------------------------------------

	HRESULT RemoveUnconnectedRenderer(
		SmartPtr<IGraphBuilder> pGraph, 
		SmartPtr<IBaseFilter> pRenderer, 
		BOOL *pbRemoved)
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