#include "StdAfx.h"
#include "SPDShowData.h"
#include "SPLogHelper.h"
#include <dshowutil.h>
#include "SPStringHelper.h"
#include <strmif.h>
#include "SPWindow.h"
//#include <GDCLWMV\filter.h>

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
		//m_pFile(NULL),
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

	typedef int (WINAPI *PROC_DllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);

	bool SPDShowData::Load()
	{
		Unload();

		HRESULT hr = S_OK;

		// Initialize COM.
		hr = S_OK;//CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to initialize com!");
			return false;
		}

		// Create filter graph.
		hr = CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC,IID_IFilterGraph,(void**)&m_pBase);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create filter graph!");
			return false;
		}

		// Create source filter.
		m_pSource = new SPFileSourceFilter(NULL, &hr);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create source filter!");
			return false;
		}

		// Add source filter.
		hr = m_pBase->AddFilter(m_pSource, NULL);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to add source filter to filter graph!");
			return false;
		}

		// Create the filter graph builder.
		hr = m_pBase->QueryInterface(IID_IGraphBuilder, (void**)&m_pGraph);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to query graph builder interface!");
			return false;
		}

		//
		// Add LAV splitter filter
		// 
				
		HMODULE hInstLibraryLAVSplitter = LoadLibrary(L"LAVSplitter.ax");

		if (hInstLibraryLAVSplitter )
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;	
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVSplitter,"DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				IClassFactory *pClassFactory = NULL;
				IBaseFilter *pLAVSplitter = NULL;	

				GUID CLSID_LAVSplitter;
				CLSIDFromString(L"{171252A0-8820-4AFE-9DF8-5C92B2D66B04}",&CLSID_LAVSplitter);
				g_PROC_DllGetClassObject(CLSID_LAVSplitter, IID_IClassFactory, (void**)&pClassFactory);
				if (!pClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Splitter filter class!");
				}
				else
				{
					pClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVSplitter));

					if (!pLAVSplitter)
					{
						SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Splitter filter to filter graph!");
					}
					else
					{
						hr = m_pBase->AddFilter(pLAVSplitter,L"LAV Splitter");

						if (FAILED(hr))
						{
							SPLogHelper::WriteLog("[DShow] WARNING: Failed to add LAV Splitter filter to filter graph!");
						}
					}								

					SAFE_RELEASE(pLAVSplitter);
				}				
			}
		}
		else
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to Load LAVSplitter.ax :" + SPStringHelper::ToString((int)GetLastError()));
		}

		//
		// Add LAV Video filter
		// 		
		
		HMODULE hInstLibraryLAVVideo = LoadLibrary(L"LAVVideo.ax");

		if (hInstLibraryLAVVideo )
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVVideo,"DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				IBaseFilter *pLAVVideo = NULL;
				IClassFactory *pClassFactory = NULL;

				GUID CLSID_LAVVideo;
				CLSIDFromString(L"{EE30215D-164F-4A92-A4EB-9D4C13390F9F}",&CLSID_LAVVideo);
				g_PROC_DllGetClassObject(CLSID_LAVVideo, IID_IClassFactory, (void**)&pClassFactory);
				if (!pClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Video filter class!");
				}
				else
				{
					pClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVVideo));

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

					SAFE_RELEASE(pLAVVideo);
				}				
			}
		}
		else
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to Load LAVVideo.ax :" + SPStringHelper::ToString((int)GetLastError()));
		}

		//
		// Add LAV Audio filter
		// 		

		HMODULE hInstLibraryLAVAudio = LoadLibrary(L"LAVAudio.ax");

		if (hInstLibraryLAVAudio )
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVAudio,"DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				IBaseFilter *pLAVAudio = NULL;
				IClassFactory *pClassFactory = NULL;

				GUID CLSID_LAVAudio;
				CLSIDFromString(L"{E8E73B6B-4CB3-44A4-BE99-4F7BCB96E491}",&CLSID_LAVAudio);
				g_PROC_DllGetClassObject(CLSID_LAVAudio, IID_IClassFactory, (void**)&pClassFactory);
				if (!pClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Audio filter class!");
				}
				else
				{
					pClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVAudio));

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

					SAFE_RELEASE(pLAVAudio);
				}				
			}
		}
		else
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to Load LAVAudio.ax :" + SPStringHelper::ToString((int)GetLastError()));
		}

		// Query for graph interfaces.
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

		// Set up event notification.
		if (SUCCEEDED(hr))
		{
			hr = m_pEvent->SetNotifyWindow((OAHWND)m_hwndEvent, m_EventMsg, NULL);
		}

		//CoUninitialize();

		return SUCCEEDED(hr);
	}

	bool SPDShowData::Unload()
	{
		// Stop sending event messages
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
		//m_pFile = NULL;

		m_seekCaps = 0;
		m_bAudioStream = FALSE;

		return true;
	}

	//HRESULT	SPDShowData::RenderStreams(SmartPtr<IBaseFilter> pSource)
	HRESULT	SPDShowData::RenderStreams(SmartPtr<SPFileSourceFilter> pSource)
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

		//hr = m_pGraph->Render(pSource->GetPin(0));

		if (SUCCEEDED(hr))
		{
			// Loop through all the pins
			IPin *pPin = NULL;

			while (S_OK == pEnum->Next(1, &pPin, NULL))
			{			
				// Try to render this pin. 
				// It's OK if we fail some pins, if at least one pin renders.
				HRESULT hr2 = pGraph2->RenderEx(pPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL);
				//HRESULT hr2 = pGraph2->Render(pPin);
				

				pPin->Release();

				if (SUCCEEDED(hr2))
				{
					bRenderedAnyPin = TRUE;
				}
			}
		}

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

	bool SPDShowData::AddSource( SPString name )
	{
		HRESULT hr = S_OK;

		//IBaseFilter *pSource = NULL;
		//IBaseFilter *pFileSourceFilter = NULL;
		//IFileSourceFilter *pIFileSourceFilter = NULL;

		// Load at first!

		// Create the Texture Renderer object
		SPVideoRenderer *pCTR = NULL;

		pCTR = new SPVideoRenderer(this, NULL, &hr);
		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to create video renderer!");
			return false;
		}	

		// Add the render filter to the graph.
		m_pRenderer = pCTR;
		hr = m_pBase->AddFilter(m_pRenderer, L"TEXTURERENDERER");
		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to add the video renderer!");
			return false;
		}			

		// Create and query source filter interface.
		//SPFileSourceFilter* m_pSource = new SPFileSourceFilter(NULL, &hr);
		//if (FAILED(hr))
		//{
		//	SPLogHelper::WriteLog("[DShow] ERROR: Failed to create source filter!");
		//	m_pSource = NULL;
		//	return false;
		//}	

		//SmartPtr<SPFileSourceFilter> sourceCopy = m_pSource;
		//m_pSource->AddRef();

		// Query source filter interface.
		//hr = m_pSource->QueryInterface(IID_IBaseFilter, (void**)&pFileSourceFilter);
		//if (FAILED(hr))
		//{
		//	SPLogHelper::WriteLog("[DShow] ERROR: Failed to get base filter interface form source filter!");
		//	return false;
		//}

		//// Add to graph
		//hr = m_pGraph->AddFilter(m_pSource, "File Source");
		//if (FAILED(hr))
		//{
		//	SPLogHelper::WriteLog("[DShow] ERROR: Failed to add file source filter to graph!");
		//	return false;
		//}

		// Query file source filter interface.
		//hr = pFileSourceFilter->QueryInterface(IID_IFileSourceFilter, (void**)&pIFileSourceFilter);
		//if (FAILED(hr))
		//{
		//	SPLogHelper::WriteLog("[DShow] ERROR: Failed to get file source filter interface form base filter!");
		//	return false;
		//}

		hr = m_pSource->Load(name.c_str(), NULL);
		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to load source file!");
			return false;
		}



		//// Add the source filter to the graph.
		//hr = m_pGraph->AddSourceFilter(
		//	SPStringHelper::MultiByteCStringToWideChar(name.c_str()),
		//	NULL, &pSource);
		//if (FAILED(hr))
		//{
		//	SPLogHelper::WriteLog("[DShow] ERROR: Failed to add source filter! No such file or directory: \"%s\"", name.c_str());
		//	return false;
		//}	

		// Try to render the streams.
		//hr = RenderStreams(pSource);
		hr = RenderStreams(m_pSource);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to render source stream!");
			return false;
		}	

		// Get the seeking capabilities.
		hr = m_pSeek->GetCapabilities(&m_seekCaps);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to get seek capability!");
			return false;
		}	

		// Set the volume.
		hr = UpdateVolume();

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog("[DShow] ERROR: Failed to update volume!");
			return false;
		}	

		//SAFE_RELEASE(pSource);

		return true;
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