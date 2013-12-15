//////////////////////////////////////////////////////////////////////////
/// @file		SPSoundFile.h the header file of SPSoundFile class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-01-25
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPString.h"
#include "SPFile.h"


namespace SPEngine
{
	class SPSoundFile : public SPFile
	{
	public:
		virtual ~SPSoundFile(){};
		virtual bool GetWFX(WAVEFORMATEX&) = 0;
		virtual bool GetSoundLength(long&) = 0;
		virtual bool NextStreamData(BYTE* pData, DWORD length, DWORD &readBytes, bool &eof) = 0;
		virtual bool IsLoaded() = 0;
	};

	typedef SPPointer<SPSoundFile> SPSoundFilePtr;

}

