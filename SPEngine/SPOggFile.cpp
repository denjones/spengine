#include "StdAfx.h"
#include "SPOggFile.h"
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include "SPLogHelper.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPOggFile::SPOggFile(void)
	{
		isLoaded = false;
		songLength = 0;
	}

	SPOggFile::SPOggFile( SPString path )
	{
		isLoaded = false;
		songLength = 0;
		this->path = path;
		Open(path);
		LoadVorbis();
	}


	SPOggFile::~SPOggFile(void)
	{
		ov_clear(&vf);
	}

	bool SPOggFile::GetWFX( WAVEFORMATEX& wfx)
	{
		if (!isLoaded)
		{
			return false;
		}

		wfx = this->wfx;

		return true;
	}

	bool SPOggFile::GetSoundLength( long& length)
	{
		if(!isLoaded)
		{
			return false;
		}

		length = songLength;

		return true;
	}

	bool SPOggFile::NextStreamData( BYTE* pData, DWORD length, DWORD &readBytes, bool &eof )
	{
		if (!isLoaded)
		{
			return false;
		}

		DWORD pos = 0;
		int sec = 0;
		int ret = 1;

		while(ret && pos < length)
		{
			ret = ov_read(&vf, (char*)pData + pos, length - pos, 0, 2, 1, &sec);
			pos += ret;
		}

		readBytes = pos;

		if (!ret)
		{
			eof = true;
			ov_pcm_seek(&vf, 0);
		}
		else
		{
			eof = false;
		}

		return true;
	}

	bool SPOggFile::LoadVorbis()
	{
		//
		// Initialize.
		// 

		fileLength = GetFileLength();
		dataRead = 0;

		//
		// Set vorbis callback.
		// 

		ov_callbacks vorbisCallbacks;
		vorbisCallbacks.read_func = VorbisRead;
		vorbisCallbacks.seek_func = VorbisSeek;
		vorbisCallbacks.close_func = VorbisClose;
		vorbisCallbacks.tell_func = VorbisTell;
		
		//
		// Open vorbis file.
		// 
		// 
		int ret = ov_open_callbacks(this, &vf, NULL, 0, vorbisCallbacks);
		if (ret < 0)
		{
			SPLogHelper::WriteLog(L"[SPSound] Failed to open ogg file: " + path);
			SPLogHelper::WriteLog(L"[SPSound] Ogg Vorbis Error: " + SPStringHelper::ToWString(ret));
			return false;
		}		

		//
		// The vorbis_info struct keeps the most of the interesting format info.
		// 

		vorbis_info *vi = ov_info(&vf, -1);

		//
		// Set the wave format.
		// 

		WAVEFORMATEX wfm;
		memset(&wfm, 0, sizeof(wfm));

		wfm.cbSize          = sizeof(wfm);
		wfm.nChannels       = vi->channels;
		wfm.wBitsPerSample  = 16; // Ogg vorbis is always 16 bit
		wfm.nSamplesPerSec  = vi->rate;
		wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nChannels * 2;
		wfm.nBlockAlign     = 2 * wfm.nChannels;
		wfm.wFormatTag      = 1;

		wfx = wfm;

		songLength = ov_time_total(&vf, -1) * 1000;


		//
		// Set loaded flag.
		// 

		isLoaded = true;

		return true;
	}

	size_t SPOggFile::VorbisRead( void *ptr, size_t byteSize, size_t sizeToRead, void *datasource )
	{
		size_t	spaceToEOF;		// How much more we can read till we hit the EOF marker
		size_t	actualSizeToRead;	// How much data we are actually going to read from memory
		SPOggFile*	vorbisFile;	// Our vorbis data, for the typecast

		//
		// Get the data in the right format
		// 

		vorbisFile = (SPOggFile*)datasource;

		//
		// Calculate how much we need to read.  This can be sizeToRead*byteSize or less depending on how near the EOF marker we are
		// 

		spaceToEOF = vorbisFile->fileLength - vorbisFile->dataRead;

		if ((sizeToRead * byteSize) < spaceToEOF)
		{
			actualSizeToRead = (sizeToRead * byteSize);
		}
		else
		{
			actualSizeToRead = spaceToEOF;	
		}

		//
		// A simple copy of the data from memory to the data struct that the vorbis libs will use
		// 

		if (actualSizeToRead)
		{
			//
			// Copy the data from the start of the file PLUS how much we have already read in
			// 

			vorbisFile->Read(ptr, actualSizeToRead);
			//memcpy(ptr, (char*)vorbisFile->dataPtr + vorbisFile->dataRead, actualSizeToRead);

			//
			// Increase by how much we have read by
			// 

			vorbisFile->dataRead += (actualSizeToRead);
		}

		//
		// Return how much we read (in the same way fread would)
		// 

		return actualSizeToRead;
	}

	int SPOggFile::VorbisSeek( void *datasource, ogg_int64_t offset, int whence )
	{
		size_t				spaceToEOF;	// How much more we can read till we hit the EOF marker
		ogg_int64_t			actualOffset;	// How much we can actually offset it by
		SPOggFile*			vorbisFile;	// The data we passed in (for the typecast)

		//
		// Get the data in the right format
		// 

		vorbisFile = (SPOggFile*)datasource;

		//
		// Goto where we wish to seek to
		// 

		switch (whence)
		{
		case SEEK_SET: // Seek to the start of the data file

			//
			// Make sure we are not going to the end of the file
			// 

			if (vorbisFile->fileLength >= offset)
			{
				actualOffset = offset;
			}
			else
			{
				actualOffset = vorbisFile->fileLength;
			}

			//
			// Set where we now are
			// 

			vorbisFile->SetPosition((int)actualOffset);
			vorbisFile->dataRead = actualOffset;

			break;

		case SEEK_CUR: // Seek from where we are

			//
			// Make sure we don't go past the end
			// 

			spaceToEOF = vorbisFile->fileLength - vorbisFile->dataRead;
			if (offset < spaceToEOF)
			{
				actualOffset = (offset);
			}
			else
			{
				actualOffset = spaceToEOF;	
			}

			//
			// Seek from our current location.
			// 

			vorbisFile->SetOffset(actualOffset);
			vorbisFile->dataRead += actualOffset;

			break;

		case SEEK_END: // Seek from the end of the file

			vorbisFile->SetPosition(vorbisFile->fileLength + 1);
			vorbisFile->dataRead = vorbisFile->fileLength + 1;

			break;

		default:
			//printf("*** ERROR *** Unknown seek command in VorbisSeek\n");
			break;
		};

		return 0;
	}

	int SPOggFile::VorbisClose( void *datasource )
	{
		//
		// This file is called when we call ov_close.  
		// If we wanted, we could free our memory here, but
		// in this case, we will free the memory in the main body 
		// of the program, so don't do anything.
		//
		
		return 1;
	}

	long SPOggFile::VorbisTell( void *datasource )
	{
		SPOggFile*	vorbisData;

		//
		// Get the data in the right format
		// 

		vorbisData = (SPOggFile*)datasource;

		//
		// We just want to tell the vorbis libs how much we have read so far
		// 

		return vorbisData->dataRead;
	}

	bool SPOggFile::IsLoaded()
	{
		return isLoaded;
	}

}

