//////////////////////////////////////////////////////////////////////////
/// @file		SPXAudio.cpp the implement file of SPXAudio class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-31
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPXAudio.h"
#include "SPLogHelper.h"
#include "SPMessageHelper.h"
#include "SPString.h"
#include <shlwapi.h>
#include "SPStringHelper.h"

#pragma comment(lib,"Shlwapi.lib")

namespace SPEngine
{
	SPXAudio::SPXAudio(void)
	{
		xAudio = NULL;
		masterVoice = NULL;
		Load();
	}


	SPXAudio::~SPXAudio(void)
	{
		Unload();
	}

	void SPXAudio::Load()
	{
		TCHAR Buffer[MAX_PATH]; 
		GetSystemDirectory(Buffer, MAX_PATH);
		SPString path = SPString(Buffer) + L"\\XAudio2_7.dll";

		if(PathFileExists( path.c_str()) == FALSE) 
		{
			// Register xaudio			
			SPLogHelper::WriteLog(L"[XAudio] Copying XAudio " + path );
			CopyFile(L"XAudio2_7.dll", path.c_str(), TRUE);
			SPLogHelper::WriteLog("[XAudio] Registering XAudio ..." );
			UINT result = WinExec("regsvr32.exe XAudio2_7.dll ", SW_HIDE);
		}

		// Registration failed.
		if(PathFileExists( path.c_str()) == FALSE) 
		{
			SPMessageHelper::Msg("Missing XAudio2! Please run this program again as administrator.");
			SPLogHelper::WriteLog("[XAudio] ERROR: Registration Failed!" );
		}

		//void* fnc = GetProcAddress(module, "XAudio2Create");

		SPLogHelper::WriteLog("[XAudio] Initializing XAudio ...");

		HRESULT hr = S_OK;//CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (FAILED(hr) && hr != -2147417850)
		{
			SPLogHelper::WriteLog("[XAudio] ERROR: Failed to initialize XAudio2!");
			SPMessageHelper::Msg("Failed to initialize XAudio2!");
			return;
		}	

		IXAudio2* pXAudio2;

		hr = CoCreateInstance((0 & XAUDIO2_DEBUG_ENGINE) ? __uuidof(XAudio2_Debug) : __uuidof(XAudio2),
			NULL, CLSCTX_INPROC_SERVER, __uuidof(IXAudio2), (void**)&pXAudio2);

		if (SUCCEEDED(hr))
		{
			hr = pXAudio2->Initialize(0, XAUDIO2_DEFAULT_PROCESSOR);

			if (SUCCEEDED(hr))
			{
				xAudio = pXAudio2;
			}
			else
			{
				pXAudio2->Release();
			}
		}
		else
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[XAudio] ERROR: Failed to create XAudio2! %d %d", __uuidof(IXAudio2), __uuidof(XAudio2_Debug)));
		}

		//hr = XAudio2Create( &xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR );

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[XAudio] ERROR: Failed to create XAudio2! %d %d", hr, GetLastError()));
			
			SPMessageHelper::Msg("Failed to create XAudio2!");
			return;
		}

		// Enumerate and select devices
		UINT32 deviceCount;
		xAudio->GetDeviceCount(&deviceCount);

		XAUDIO2_DEVICE_DETAILS deviceDetails;
		int preferredDevice = 0;
		for (unsigned int i = 0; i < deviceCount; i++)
		{
			xAudio->GetDeviceDetails(i,&deviceDetails);
			if (deviceDetails.OutputFormat.Format.nChannels > 2)
			{
				preferredDevice = i;
				break;
			}
		}

		// Create mastering voice device
		if ( FAILED(xAudio->CreateMasteringVoice( &masterVoice, XAUDIO2_DEFAULT_CHANNELS,
			XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL ) ) )
		{
			SPLogHelper::WriteLog("[XAudio] WARNING: Failed to create Mastering Voice!");
			//MessageBoxA(NULL, "Failed to create mastering voice!", NULL, NULL);
			Unload();
			return;
		}

		return;
	}

	void SPXAudio::Unload()
	{
		// Destroy Master Voice.
		if(masterVoice)
		{
			masterVoice->DestroyVoice();
			masterVoice = NULL;
		}

		//Unload the xAudio2
		if(xAudio)
		{
			xAudio->Release();
			xAudio = NULL;
		}
	}

	void SPXAudio::Reload()
	{
		Load();
	}
}

