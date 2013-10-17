//////////////////////////////////////////////////////////////////////////
/// @file		SPXAudio.h the header file of SPXAudio class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-31
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SPSingleton.h"
#include "XAudio2.h"
#include "ISPLoadable.h"
#include "SPComponent.h"

//#pragma comment(lib, "xaudio2.lib")

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPXAudio class to represent a XAudio2 object and the master voice.
	///
	//////////////////////////////////////////////////////////////////////
	class SPXAudio :
		public SPComponent,
		public SPSingleton<SPXAudio>
	{
		IXAudio2*	xAudio;
		IXAudio2MasteringVoice* masterVoice;

	public:
		IXAudio2* GetXAudio() { return xAudio; }
		IXAudio2MasteringVoice* GetMasterVoice() { return masterVoice; }	

	public:
		SPXAudio(void);
		virtual ~SPXAudio(void);

		bool Load();
		bool Unload();
		bool Reload();
	
	};
}


