#include "StdAfx.h"
#include "SPWavFile.h"
#include "SPLogHelper.h"
#include "SPStringHelper.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT  ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

namespace SPEngine
{
	SPWavFile::SPWavFile(void)
	{
		isLoaded = false;
		songLength = 0;
		ZeroMemory(&overlapped, sizeof(overlapped));
		overlapped.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
	}

	SPWavFile::SPWavFile( SPString path )
	{
		isLoaded = false;
		songLength = 0;
		ZeroMemory(&overlapped, sizeof(overlapped));
		overlapped.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
		this->path = path;
		Open(path);
		LoadWave();
	}

	SPWavFile::~SPWavFile(void)
	{
	}

	bool SPWavFile::GetWFX( WAVEFORMATEX& wfx)
	{
		if (!isLoaded)
		{
			return false;
		}

		wfx = this->wfx;

		return true;
	}

	bool SPWavFile::GetSoundLength( long& length)
	{
		if(!isLoaded)
		{
			return false;
		}

		length = songLength;

		return true;
	}

	bool SPWavFile::NextStreamData(BYTE* pData, DWORD length, DWORD &readBytes, bool &eof)
	{
		//
		// Reset current position.
		// 

		if (currentSoundPosition >= soundDataLength)
		{
			currentSoundPosition = 0;
		}

		//
		// Read next chunk data into buffer.
		// 

		DWORD cbValid = min( length, soundDataLength - currentSoundPosition );
		overlapped.Offset = soundDataOffset + currentSoundPosition;

		if(!SetPosition(overlapped.Offset) || !Read(pData, length, &overlapped))
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[XAudio] ERROR: Couldn't start async read: error %#X", HRESULT_FROM_WIN32( GetLastError() ) ));
			return false;
		}

		//
		// Update current position.
		// 

		currentSoundPosition += cbValid;
		readBytes = cbValid;

		//
		// At this point the read is progressing in the background and we are free to do
		// other processing while we wait for it to finish.
		//

		DWORD cb;
		GetOverlappedResult( GetFileHandle(), &overlapped, &cb, TRUE );

		eof = currentSoundPosition >= soundDataLength;

		return true;

	}

	bool SPWavFile::FindChunk( DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition )
	{
		bool notEnd = true;

		if(!SetPosition(FILE_BEGIN))
		{
			return false;
		}

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (notEnd)
		{
			//DWORD dwRead;

			if (!Read(&dwChunkType, sizeof(DWORD)))
			{
				notEnd =  false;
			}

			if (!Read(&dwChunkDataSize, sizeof(DWORD)))
			{
				notEnd =  false;
			}

			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;

				if (!Read(&dwFileType, sizeof(DWORD)))
				{
					notEnd =  false;
				}

				break;

			default:
				if(!SetOffset(dwChunkDataSize))
				{
					return false;
				}
				break;
			}

			dwOffset += sizeof(DWORD) * 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPosition = dwOffset;
				return true;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize)
			{
				return false;
			}
		}

		return true;
	}

	bool SPWavFile::ReadChunkData( void * buffer, DWORD buffersize, DWORD bufferoffset )
	{
		if(!SetPosition(bufferoffset))
		{
			return false;
		}

		//DWORD dwRead;

		if (!Read(buffer, buffersize))
		{
			return false;
		}

		return true;
	}

	bool SPWavFile::LoadWave()
	{
		if (path == L"")
		{
			return false;
		}

		DWORD dwChunkSize;
		DWORD dwChunkPosition;
		DWORD filetype;

		// Check the file type, should be fourccWAVE or 'XWMA'

		FindChunk(fourccRIFF, dwChunkSize, dwChunkPosition );		
		ReadChunkData(&filetype, sizeof(DWORD), dwChunkPosition);

		if (filetype != fourccWAVE)
		{
			return false;
		}

		// Locate the 'fmt ' chunk, and copy its contents into a
		// WAVEFORMATEXTENSIBLE structure.

		FindChunk(fourccFMT, dwChunkSize, dwChunkPosition );
		ReadChunkData(&wfx, dwChunkSize, dwChunkPosition );

		// 
		// Find the beginning position and the size of stream data.
		// 

		FindChunk(fourccDATA, soundDataLength, soundDataOffset);
		SetPosition(soundDataOffset);

		//
		// Calculate sound length.
		// 

		int stereo = wfx.nChannels;
		int numberBytePerChannalSample = wfx.wBitsPerSample / 8;
		int bytePerSample = stereo * numberBytePerChannalSample;
		int sampleRate = wfx.nSamplesPerSec;
		float seconds = soundDataLength / (float)(sampleRate * bytePerSample);
		songLength = seconds;

		// 
		// Set loaded flag.
		// 

		isLoaded = true;

		return true;
	}

	bool SPWavFile::IsLoaded()
	{
		return isLoaded;
	}


}

