#pragma once
#include "SPSoundFile.h"

namespace SPEngine
{
	class SPWavFile : public SPSoundFile
	{
		bool isLoaded;
		long songLength;
		WAVEFORMATEX wfx;
		DWORD currentSoundPosition;
		DWORD soundDataOffset;
		DWORD soundDataLength;
		OVERLAPPED overlapped;

	public:
		SPWavFile(SPString path);
		SPWavFile(void);
		virtual ~SPWavFile(void);

		bool LoadWave();

		virtual bool GetWFX( WAVEFORMATEX& );

		virtual bool GetSoundLength( long& );

		virtual bool NextStreamData(BYTE* pData, DWORD length, DWORD &readBytes, bool &eof);

	private:
		
		bool FindChunk(DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
		bool ReadChunkData(void * buffer, DWORD buffersize, DWORD bufferoffset);

		virtual bool IsLoaded();

	};

	typedef SPPointer<SPWavFile> SPWavFilePtr;
}


