#pragma once
#include <sxp.h>

using namespace std;

namespace SPEngine
{
	class Config : public SXP::IPersistObj
	{
	public:
		int windowWidth;
		int windowHeight;
		int backBufferWidth;
		int backBufferHeight;
		int multisampleType;
		int multisampleLevel;
		float refleshRate;
		bool windowed;
		bool vSync;
	
		Config(void);
		~Config(void);

	private:
		SXP::Tag tag_windowWidth;
		SXP::Tag tag_windowHeight;
		SXP::Tag tag_backBufferWidth;
		SXP::Tag tag_backBufferHeight;
		SXP::Tag tag_multisampleType;
		SXP::Tag tag_multisampleLevel;
		SXP::Tag tag_refleshRate;
		SXP::Tag tag_windowed;
		SXP::Tag tag_vSync;

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
	};
}


