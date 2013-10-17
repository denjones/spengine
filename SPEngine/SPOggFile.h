#pragma once
#include "SPSoundFile.h"
#include <vorbis\vorbisfile.h>

namespace SPEngine
{
	class SPOggFile : public SPSoundFile
	{
		bool isLoaded;
		long songLength;
		WAVEFORMATEX wfx;
		OggVorbis_File vf;
		DWORD currentSoundPosition;
		DWORD fileLength;
		DWORD dataRead;

	public:
		SPOggFile(SPString path);
		SPOggFile(void);
		virtual ~SPOggFile(void);

		virtual bool GetWFX( WAVEFORMATEX& wfx);

		virtual bool GetSoundLength( long& length);

		virtual bool NextStreamData( BYTE* pData, DWORD length, DWORD &readBytes, bool &eof );

		bool LoadVorbis();

	private:

		// Vorbis callback functions.

		static size_t VorbisRead(void *ptr, 	size_t byteSize, size_t sizeToRead, void *datasource);

		static int VorbisSeek(void *datasource, ogg_int64_t offset, int whence);

		static int VorbisClose(void *datasource);

		static long VorbisTell(void *datasource);

		virtual bool IsLoaded();

	};

	typedef SPPointer<SPOggFile> SPOggFilePtr;
}


