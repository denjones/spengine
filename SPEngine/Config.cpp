#include "StdAfx.h"
#include "Config.h"
#include "LogHelper.h"

namespace SPEngine
{
	Config::Config(void)
	{
		windowWidth = 800;
		windowHeight = 600;
		backBufferWidth = 800;
		backBufferHeight = 600;
		multisampleType = 0;
		multisampleLevel = 0;
		refleshRate = 0;
		windowed = true;
		vSync = true;


		tag_windowWidth = "WindowWidth";
		tag_windowHeight = "WindowHeight";
		tag_backBufferWidth = "BackBufferWidth";
		tag_backBufferHeight = "BackBufferHeight";
		tag_multisampleType = "MultisampleType";
		tag_multisampleLevel = "MultisampleLevel";
		tag_refleshRate = "RefleshRate";
		tag_windowed = "Windowed";
		tag_vSync = "VSync";

		tag_own = "Config";

	}


	Config::~Config(void)
	{
	}

	SXP::Tag Config::GetClassTag()
	{
		 return tag_own; 
	}

	void Config::EndElement( SXP::IParser *pIn, SXP::IElement *pElement )
	{
		if( pElement->IsA(tag_windowWidth) )   pElement->Retrieve(windowWidth);
		if( pElement->IsA(tag_windowHeight) )   pElement->Retrieve(windowHeight);
		if( pElement->IsA(tag_backBufferWidth) )   pElement->Retrieve(backBufferWidth);
		if( pElement->IsA(tag_backBufferHeight) )   pElement->Retrieve(backBufferHeight);
		if( pElement->IsA(tag_multisampleType) )   pElement->Retrieve(multisampleType);
		if( pElement->IsA(tag_multisampleLevel) )   pElement->Retrieve(multisampleLevel);
		if( pElement->IsA(tag_refleshRate) )   pElement->Retrieve(refleshRate);
		if( pElement->IsA(tag_windowed) )   pElement->Retrieve(windowed);
		if( pElement->IsA(tag_vSync) )   pElement->Retrieve(vSync);
	}

	void Config::WriteElement( SXP::IOutStream *pOut, SXP::dict& attribs )
	{
		// no attributes, don't add anything to attribs
		pOut->BeginObject(tag_own, attribs);

		pOut->WriteElement(tag_windowWidth, windowWidth);
		pOut->WriteElement(tag_windowHeight, windowHeight);
		pOut->WriteElement(tag_backBufferWidth, backBufferWidth);
		pOut->WriteElement(tag_backBufferHeight, backBufferHeight);
		pOut->WriteElement(tag_multisampleType, multisampleType);
		pOut->WriteElement(tag_multisampleLevel, multisampleLevel);
		pOut->WriteElement(tag_refleshRate, refleshRate);
		pOut->WriteElement(tag_windowed, windowed);
		pOut->WriteElement(tag_vSync, vSync);

		pOut->EndObject(tag_own);
	}

	void Config::BeginElement( SXP::IParser *pIn, SXP::IElement *pElement )
	{

	}

	bool Config::LoadFromFile( string path )
	{
		SXP::CParser *parser = NULL;
		parser = new SXP::CParser(this);
		SXP::ErrCode error = parser->FeedFile((char*)path.c_str());

		if( error != SXP::err_no_error )
		{
			LogHelper::WriteLog("Oops, error \"%s\" at line %d, char %d",
				parser->GetErrorStr().c_str(),
				parser->GetErrorLine(),
				parser->GetErrorCol());
		}

		if (parser)
		{
			delete parser;
		}
		parser = NULL;
		
		return error == SXP::err_no_error;
	}

	bool Config::SaveAsFile( string path )
	{
		SXP::CFileOutStream *out = new SXP::CFileOutStream((char*)path.c_str());
		out->BeginXML();

		SXP::dict attribs;
		WriteElement(out, attribs);

		if (out)
		{
			delete out;
		}		

		return true;
	}

}

