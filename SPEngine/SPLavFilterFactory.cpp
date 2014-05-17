#include "StdAfx.h"
#include "SPLavFilterFactory.h"
#include "SPLogHelper.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPLavFilterFactory::SPLavFilterFactory(void)
	{
		Load();
	}


	SPLavFilterFactory::~SPLavFilterFactory(void)
	{
	}

	void SPLavFilterFactory::Load()
	{
		//
		// Load Splitter Factory
		//

		hInstLibraryLAVSplitter = LoadLibrary(L"LAVSplitter.ax");

		if (hInstLibraryLAVSplitter)
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;	
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVSplitter, "DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				CLSIDFromString(L"{171252A0-8820-4AFE-9DF8-5C92B2D66B04}", &CLSID_LAVSplitter);
				g_PROC_DllGetClassObject(CLSID_LAVSplitter, IID_IClassFactory, (void**)&pSplitterClassFactory);
				if (!pSplitterClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Splitter filter class!");
				}			
			}
		}
		else
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to Load LAVSplitter.ax :" + SPStringHelper::ToString((int)GetLastError()));
		}

		//
		// Load LAV Video Filter Factory
		// 		

		hInstLibraryLAVVideo = LoadLibrary(L"LAVVideo.ax");

		if (hInstLibraryLAVVideo )
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVVideo, "DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				CLSIDFromString(L"{EE30215D-164F-4A92-A4EB-9D4C13390F9F}",&CLSID_LAVVideo);
				g_PROC_DllGetClassObject(CLSID_LAVVideo, IID_IClassFactory, (void**)&pVideoClassFactory);

				if (!pVideoClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Video filter class!");
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

		hInstLibraryLAVAudio = LoadLibrary(L"LAVAudio.ax");

		if (hInstLibraryLAVAudio )
		{
			PROC_DllGetClassObject g_PROC_DllGetClassObject = NULL;
			g_PROC_DllGetClassObject = (PROC_DllGetClassObject)GetProcAddress(hInstLibraryLAVAudio, "DllGetClassObject");

			if(g_PROC_DllGetClassObject)
			{
				CLSIDFromString(L"{E8E73B6B-4CB3-44A4-BE99-4F7BCB96E491}", &CLSID_LAVAudio);
				g_PROC_DllGetClassObject(CLSID_LAVAudio, IID_IClassFactory, (void**)&pAudioClassFactory);

				if (!pAudioClassFactory)
				{
					SPLogHelper::WriteLog("[DShow] WARNING: Failed to create LAV Audio filter class!");
				}
			}
		}
		else
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to Load LAVAudio.ax :" + SPStringHelper::ToString((int)GetLastError()));
		}
	}

	void SPLavFilterFactory::Unload()
	{
	}

	void SPLavFilterFactory::Reload()
	{
		Load();
	}

	HRESULT SPLavFilterFactory::CreateLAVSplitter( IBaseFilter* &pLAVSplitter )
	{
		return pSplitterClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVSplitter));
	}

	HRESULT SPLavFilterFactory::CreateLAVVideo( IBaseFilter* &pLAVVideo )
	{
		return pVideoClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVVideo));
	}

	HRESULT SPLavFilterFactory::CreateLAVAudio( IBaseFilter* &pLAVAudio )
	{
		return pAudioClassFactory->CreateInstance(0,IID_IBaseFilter, reinterpret_cast<void**>(&pLAVAudio));
	}

}