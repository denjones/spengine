//////////////////////////////////////////////////////////////////////////
/// @file		SPDevice.h the header file of SPDevice class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPSingleton.h"
#include "SPConfig.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPDevice class to encapsulate D3D object and device.
	//////////////////////////////////////////////////////////////////////
	class SPDevice : public SPSingleton<SPDevice>
	{
		LPDIRECT3D9			d3dObject;		///< D3D object
		LPDIRECT3DDEVICE9	d3dDevice;		///< D3D device

	public:
		const LPDIRECT3D9 GetD3DObject() const { return d3dObject; }
		const LPDIRECT3DDEVICE9 GetD3DDevice() const { return d3dDevice; }
		const D3DCAPS9 GetDeviceCap();

	public:
		SPDevice(void);
		virtual ~SPDevice(void);

		bool InitializeD3D( SPConfigPtr config );
		bool CreateD3DObject();
		bool CreateD3DDevice( SPConfigPtr config );
		bool ReleaseDevice();
		bool ReleaseObject();

		bool ResetDevice( SPConfigPtr config );
	};
}


