#include "StdAfx.h"
#include "SPSoundStreamingContext.h"

namespace SPEngine{

	SPSoundStreamingContext::SPSoundStreamingContext(void)
	{
		hBufferEndEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	}

	SPSoundStreamingContext::~SPSoundStreamingContext(void)
	{
		CloseHandle( hBufferEndEvent ); 
	}

	void SPSoundStreamingContext::OnVoiceError( THIS_ void* pBufferContext, HRESULT Error )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	void SPSoundStreamingContext::OnLoopEnd( THIS_ void* pBufferContext )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	void SPSoundStreamingContext::OnBufferEnd( THIS_ void* pBufferContext )
	{
		SetEvent( hBufferEndEvent ); 
	}

	void SPSoundStreamingContext::OnBufferStart( THIS_ void* pBufferContext )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	void SPSoundStreamingContext::OnStreamEnd( THIS )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	void SPSoundStreamingContext::OnVoiceProcessingPassEnd( THIS )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	void SPSoundStreamingContext::OnVoiceProcessingPassStart( THIS_ UINT32 BytesRequired )
	{
		//throw std::exception("The method or operation is not implemented.");
	}

}

