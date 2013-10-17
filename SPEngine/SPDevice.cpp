#include "StdAfx.h"
#include "SPDevice.h"
#include "SPMessageHelper.h"
#include "SPWindow.h"
#include "SPTextureManager.h"

namespace SPEngine
{
	SPDevice::SPDevice(void)
	{
		d3dObject = NULL;
		d3dDevice = NULL;
	}

	SPDevice::~SPDevice(void)
	{
		ReleaseDevice();
	}

	bool SPDevice::InitializeD3D( SPConfig config )
	{
		SPLogHelper::WriteLog("[DirectX] Initializing D3D ...");

		if( !CreateD3DObject() )
		{
			return false;
		}

		if ( !CreateD3DDevice(config) )
		{
			return false;
		}

		return true;
	}

	const D3DCAPS9 SPDevice::GetDeviceCap()
	{
		assert(d3dObject);

		D3DCAPS9 caps;
		d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

		return caps; 
	}

	bool SPDevice::CreateD3DObject()
	{
		SPLogHelper::WriteLog("[DirectX] Creating D3D Object ...");

		// Create D3D object.
		d3dObject = Direct3DCreate9( D3D_SDK_VERSION );

		// Check
		if ( !d3dObject )
		{
			SPMessageHelper::Msg( "Failed to create D3D object !" );
			SPLogHelper::WriteLog("[DirectX] ERROR: Failed to create D3D object!");

			return false;
		}

		return true;
	}

	bool SPDevice::CreateD3DDevice( SPConfig config )
	{
		SPLogHelper::WriteLog("[DirectX] Creating D3D Device ...");

		// Get device's capabilities
		D3DCAPS9 caps = GetDeviceCap();

		// Support hardware vertex processing?
		int vp = 0;
		if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			// Yes
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		}
		else
		{
			// No. Use software instead
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		}

		// Set up the structure to create the D3DDevice.
		D3DPRESENT_PARAMETERS d3dpp = config.ToD3DParameters();

		HWND hWnd = SPWindow::GetSingleton().GetHWnd();

		ReleaseDevice();

		// Create the D3DDevice
		HRESULT hr = d3dObject->CreateDevice(D3DADAPTER_DEFAULT,
			(D3DDEVTYPE)config.deviceType, 
			hWnd, vp, &d3dpp, &d3dDevice);
		
		if (hr != S_OK)
		{
			//SPMessageHelper::Msg( "Failed to create D3D device!");
			SPLogHelper::WriteLog("[DirectX] ERROR: Failed to create D3D device!");
			return false;
		}

		return true;
	}

	bool SPDevice::ResetDevice( SPConfig config )
	{
		//SPTextureManager::GetSingleton().Unload();

		// Try to reset.
		if (d3dDevice)
		{
			if (D3D_OK == d3dDevice->Reset(&config.ToD3DParameters()))
			{
				return true;
			}
		}		

		// Force reload.
		SPLogHelper::WriteLog("[DirectX] WARNING: Force reseting D3D device!");

		ReleaseDevice();

		if( !CreateD3DDevice(config) )
		{
			return false;
		}

		return true;
	}

	bool SPDevice::ReleaseDevice()
	{
		if (d3dDevice)
		{
			d3dDevice->Release();
			d3dDevice = NULL;
			return true;
		}

		SPLogHelper::WriteLog("[DirectX] WARNING: No device to be released!");
		return false;
	}

	bool SPDevice::ReleaseObject()
	{
		if (d3dObject)
		{
			d3dObject->Release();
			d3dObject = NULL;
			return true;
		}

		SPLogHelper::WriteLog("[DirectX] WARNING: No D3D object to be released!");
		return false;
	}

}

