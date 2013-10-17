#include "StdAfx.h"
#include "SPGame.h"

namespace SPEngine
{
	VideoManager::VideoManager(void)
	{
		
	}

	VideoManager::~VideoManager(void)
	{
	}

	//bool VideoManager::Draw( float timeElapsed )
	//{
	//	return true;
	//}

	//bool VideoManager::Update( float timeElapsed )
	//{
	//	return true;
	//}

	//bool VideoManager::Load()
	//{
	//	return true;
	//}

	bool VideoManager::Initialize()
	{
		if(!VerifyVMR9())
		{
			MessageBoxA(NULL,"Verify VMR9 failed.",NULL,NULL);
			return false;
		}

		return true;
	}

	//bool VideoManager::Unload()
	//{
	//	return true;
	//}

	bool VideoManager::VerifyVMR9(void)
	{
		HRESULT hr;

		// Verify that the VMR exists on this system
		IBaseFilter* pBF = NULL;
		hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL,
			CLSCTX_INPROC,
			IID_IBaseFilter,
			(LPVOID *)&pBF);
		if(SUCCEEDED(hr))
		{
			pBF->Release();
			return true;
		}
		else
		{
			MessageBox(NULL,
				TEXT("This application requires the VMR-9.\r\n\r\n")

				TEXT("The VMR-9 is not enabled when viewing through a Remote\r\n")
				TEXT(" Desktop session. You can run VMR-enabled applications only\r\n") 
				TEXT("on your local computer.\r\n\r\n")

				TEXT("\r\nThis sample will now exit."),

				TEXT("Video Mixing Renderer (VMR9) capabilities are required"), MB_OK);

			return false;
		}
	}
}
