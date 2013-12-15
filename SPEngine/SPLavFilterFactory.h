#pragma once
#include "SPSingleton.h"
#include "ISPLoadable.h"

namespace SPEngine
{
	typedef int (WINAPI *PROC_DllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);

	class SPLavFilterFactory : public ISPLoadable,
		public SPSingleton<SPLavFilterFactory>
	{
	private:
		HMODULE hInstLibraryLAVSplitter;
		HMODULE hInstLibraryLAVVideo;
		HMODULE hInstLibraryLAVAudio;
		GUID CLSID_LAVSplitter;
		GUID CLSID_LAVVideo;
		GUID CLSID_LAVAudio;
		IClassFactory *pSplitterClassFactory;
		IClassFactory *pVideoClassFactory;
		IClassFactory *pAudioClassFactory;

	public:
		SPLavFilterFactory(void);
		~SPLavFilterFactory(void);

		HRESULT CreateLAVSplitter(IBaseFilter* &pLAVSplitter);
		HRESULT CreateLAVVideo(IBaseFilter* &pLAVVideo);
		HRESULT CreateLAVAudio(IBaseFilter* &pLAVAudio);

		virtual bool Load();

		virtual bool Unload();

		virtual bool Reload();

	};
}
