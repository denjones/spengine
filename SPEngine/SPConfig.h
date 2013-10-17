//////////////////////////////////////////////////////////////////////////
/// @file		SPConfig.h the header file of SPConfig class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <sxp.h>

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPConfig class to represent a set of configuration.
	///
	//////////////////////////////////////////////////////////////////////
	class SPConfig : public SXP::IPersistObj
	{
	public:
		int windowWidth;
		int windowHeight;
		int workingWidth;
		int workingHeight;
		int multisampleType;
		int multisampleLevel;
		float refreshRate;
		bool windowed;
		bool vSync;
		int deviceType;
	
		SPConfig(void);
		~SPConfig(void);

	private:
		SXP::Tag tag_windowWidth;
		SXP::Tag tag_windowHeight;
		SXP::Tag tag_workingWidth;
		SXP::Tag tag_workingHeight;
		SXP::Tag tag_multisampleType;
		SXP::Tag tag_multisampleLevel;
		SXP::Tag tag_refreshRate;
		SXP::Tag tag_windowed;
		SXP::Tag tag_vSync;
		SXP::Tag tag_deviceType;

		SXP::Tag tag_own;

		SXP::Tag GetClassTag();

		// here you can handle "complex" subtags - see below in CConfig
		// we don't need it here
		void BeginElement(SXP::IParser *pIn, SXP::IElement *pElement);
		// here you handle the "simple" subtags to init the member vars
		void EndElement(SXP::IParser *pIn, SXP::IElement *pElement);
		// here you describe how to write out the state of the object
		void WriteElement(SXP::IOutStream *pOut, SXP::dict& attribs);		

	public:
		bool LoadFromFile(string path);
		bool SaveAsFile(string path);
		D3DPRESENT_PARAMETERS ToD3DParameters();
	};
}


