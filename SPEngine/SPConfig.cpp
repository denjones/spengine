//////////////////////////////////////////////////////////////////////////
/// @file		SPConfig.cpp the implement file of SPConfig class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPConfig.h"
#include "SPLogHelper.h"
#include "SPDevice.h"
#include "SPWindow.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPConfig::SPConfig(void)
	{
		windowWidth = 800;
		windowHeight = 600;
		workingWidth = 800;
		workingHeight = 600;
		multisampleType = 0;
		multisampleLevel = 0;
		refreshRate = 0;
		windowed = true;
		vSync = true;
		deviceType = D3DDEVTYPE_HAL;


		tag_windowWidth = "WindowWidth";
		tag_windowHeight = "WindowHeight";
		tag_workingWidth = "WorkingWidth";
		tag_workingHeight = "WorkingHeight";
		tag_multisampleType = "MultisampleType";
		tag_multisampleLevel = "MultisampleLevel";
		tag_refreshRate = "RefreshRate";
		tag_windowed = "Windowed";
		tag_vSync = "VSync";
		tag_deviceType = "DeviceType";

		tag_own = "Config";

	}


	SPConfig::~SPConfig(void)
	{
	}

	SXP::Tag SPConfig::GetClassTag()
	{
		 return tag_own; 
	}

	void SPConfig::EndElement( SXP::IParser *pIn, SXP::IElement *pElement )
	{
		if( pElement->IsA(tag_windowWidth) )   pElement->Retrieve(windowWidth);
		if( pElement->IsA(tag_windowHeight) )   pElement->Retrieve(windowHeight);
		if( pElement->IsA(tag_workingWidth) )   pElement->Retrieve(workingWidth);
		if( pElement->IsA(tag_workingHeight) )   pElement->Retrieve(workingHeight);
		if( pElement->IsA(tag_multisampleType) )   pElement->Retrieve(multisampleType);
		if( pElement->IsA(tag_multisampleLevel) )   pElement->Retrieve(multisampleLevel);
		if( pElement->IsA(tag_refreshRate) )   pElement->Retrieve(refreshRate);
		if( pElement->IsA(tag_windowed) )   pElement->Retrieve(windowed);
		if( pElement->IsA(tag_vSync) )   pElement->Retrieve(vSync);
		if( pElement->IsA(tag_deviceType) )  pElement->Retrieve(deviceType);
	}

	void SPConfig::WriteElement( SXP::IOutStream *pOut, SXP::dict& attribs )
	{
		// no attributes, don't add anything to attribs
		pOut->BeginObject(tag_own, attribs);

		pOut->WriteElement(tag_windowWidth, windowWidth);
		pOut->WriteElement(tag_windowHeight, windowHeight);
		pOut->WriteElement(tag_workingWidth, workingWidth);
		pOut->WriteElement(tag_workingHeight, workingHeight);
		pOut->WriteElement(tag_multisampleType, multisampleType);
		pOut->WriteElement(tag_multisampleLevel, multisampleLevel);
		pOut->WriteElement(tag_refreshRate, refreshRate);
		pOut->WriteElement(tag_windowed, windowed);
		pOut->WriteElement(tag_vSync, vSync);
		pOut->WriteElement(tag_deviceType, deviceType);

		pOut->EndObject(tag_own);
	}

	void SPConfig::BeginElement( SXP::IParser *pIn, SXP::IElement *pElement )
	{

	}

	bool SPConfig::LoadFromFile( string path )
	{
		SXP::CParser *parser = NULL;
		parser = new SXP::CParser(this);
		SXP::ErrCode error = parser->FeedFile((char*)path.c_str());

		if( error != SXP::err_no_error )
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[Config] ERROR: Oops, error \"%s\" at line %d, char %d",
				parser->GetErrorStr().c_str(),
				parser->GetErrorLine(),
				parser->GetErrorCol()));
		}

		if (parser)
		{
			delete parser;
		}
		parser = NULL;
		
		return error == SXP::err_no_error;
	}

	bool SPConfig::SaveAsFile( string path )
	{
		SXP::CFileOutStream *out = new SXP::CFileOutStream((char*)path.c_str());
		out->BeginXML();

		SXP::dict attribs;
		WriteElement(out, attribs);

		if (out)
		{
			delete out;
		}		

		out = NULL;

		return true;
	}

	D3DPRESENT_PARAMETERS SPConfig::ToD3DParameters()
	{
		D3DPRESENT_PARAMETERS d3dpp;

		// Set back buffer type.
		d3dpp.BackBufferHeight = this->windowHeight;
		d3dpp.BackBufferWidth = this->windowWidth;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;

		// Set multi sample type.
		DWORD qualityLevels;

		while(
			this->multisampleType > 0 ||
			D3D_OK != SPDevice::GetSingleton().GetD3DObject()->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, 
			D3DFMT_A8R8G8B8, 
			this->windowed, 
			(D3DMULTISAMPLE_TYPE)this->multisampleType,
			&qualityLevels))
		{
			// Cannot perform the multisample type.

			// Reduce the multisample type.
			this->multisampleType--;	
		}

		if (this->multisampleLevel > (int)qualityLevels)
		{
			this->multisampleLevel = (int)qualityLevels;
		}

		d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)this->multisampleType;
		d3dpp.MultiSampleQuality = this->multisampleLevel;

		// Window related.

		d3dpp.hDeviceWindow = SPWindow::GetSingleton().GetHWnd();
		d3dpp.Windowed = this->windowed;

		// Other

		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	

		return d3dpp;
	}

}

