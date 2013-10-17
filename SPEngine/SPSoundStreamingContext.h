//////////////////////////////////////////////////////////////////////////
/// @file		SPSoundStreamingContext.h the header file of 
/// SPSoundStreamingContext class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.8
/// @date		2013-1-23
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "XAudio2.h"



namespace SPEngine
{
	class SPSoundStreamingContext :
		public IXAudio2VoiceCallback
	{
	public:
		HANDLE hBufferEndEvent;

	public:
		SPSoundStreamingContext(void);
		virtual ~SPSoundStreamingContext(void);

		STDMETHOD_(void, OnVoiceProcessingPassStart)( THIS_ UINT32 BytesRequired );

		STDMETHOD_(void, OnVoiceProcessingPassEnd)( THIS );

		STDMETHOD_(void, OnStreamEnd)( THIS );

		STDMETHOD_(void, OnBufferStart)( THIS_ void* pBufferContext );

		STDMETHOD_(void, OnBufferEnd)( THIS_ void* pBufferContext );

		STDMETHOD_(void, OnLoopEnd)( THIS_ void* pBufferContext );

		STDMETHOD_(void, OnVoiceError)( THIS_ void* pBufferContext, HRESULT Error );

	};
}

