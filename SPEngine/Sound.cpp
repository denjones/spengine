#include "StdAfx.h"
#include "Sound.h"
#include "SoundManager.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

using namespace SPEngine;
using namespace std;

Sound::Sound(void) 
{
	ZeroMemory(&wfx, sizeof(wfx));
	ZeroMemory(&buffer, sizeof(buffer));
	sourceVoice = NULL;
}

Sound::~Sound(void)
{
	Shutdown();
}

bool Sound::Load(SoundManager* manager, string filename, int numRepeats)
{
	Load(manager, filename, numRepeats, 0, 0);
	return true;
}

bool Sound::Load(SoundManager* manager, string filename, int numRepeats, float gradualIn, float gradualOut)
{
	currentManager = manager;
	state = Pausing;

	// Open the file
	HANDLE hFile = CreateFileA(
		filename.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL );

	if( INVALID_HANDLE_VALUE == hFile )
		return false;//HRESULT_FROM_WIN32( GetLastError() );

	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return false;//HRESULT_FROM_WIN32( GetLastError() );

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile,fourccRIFF,dwChunkSize, dwChunkPosition );
	DWORD filetype;
	ReadChunkData(hFile,&filetype,sizeof(DWORD),dwChunkPosition);

	if (filetype != fourccWAVE)
		return false;//S_FALSE;

	// Locate the 'fmt ' chunk, and copy its contents into a WAVEFORMATEXTENSIBLE structure.
	FindChunk(hFile,fourccFMT, dwChunkSize, dwChunkPosition );
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition );

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile,fourccDATA,dwChunkSize, dwChunkPosition );
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	buffer.LoopCount = numRepeats; // control the repeat time
	//if LoopCount == XAUDIO2_MAX_LOOP_COUNT then it will loop never end

	HRESULT hr;

	if( FAILED(hr = currentManager->XAudio()->CreateSourceVoice( &sourceVoice, (WAVEFORMATEX*)&wfx,
		0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL ) ) ) //&voiceCallback
		return false;//hr;

	if( FAILED(hr = sourceVoice->SubmitSourceBuffer( &buffer ) ) )
		return false;//hr;

	InitSound(gradualIn, gradualOut);

	manager->AddSound(this);

	return true;
}

SPEngine::Sound::Sound(SoundManager* manager, string filename, int numRepeats )
{
	Load(manager, filename, numRepeats, 0, 0);
}

bool SPEngine::Sound::Update(float timeDelta)
{
	//控制暂停时的渐入渐出
	if(state == TransitionOff)
	{
		if(currentTime <= fadeOutBeginTime + fadeOutTime)
		{
			sourceVoice->SetVolume(settedVolume * 
				((fadeOutBeginTime + fadeOutTime - currentTime) / fadeOutTime));
		}else{
			//isPausing = false;
			state = Pausing;
			isPlaying = false;
			sourceVoice->Stop(0);
			if(isPausingStop)
			{
				sourceVoice->FlushSourceBuffers();
				sourceVoice->SubmitSourceBuffer(&buffer);
				currentTime = 0;
				isPausingStop = false;
			}
		}
	}
	//控制渐进渐出

	if(state != TransitionOff)
	{
		//float lastVolume;//最终的声音大小
		float songTime = currentTime;//对当前循环的歌曲的播放进度
		while(songTime >= songLength) 
			songTime -= songLength;
		if(songTime < gradualInTime)
		{
			sourceVoice->SetVolume(settedVolume * 
				(songTime / gradualInTime));//渐进
		}
		else if(songTime > songLength - gradualOutTime)
		{
			sourceVoice->SetVolume(settedVolume * ((songLength - songTime)	/ gradualOutTime));//渐出
		}
		else 
		{
			sourceVoice->SetVolume(settedVolume);
		}
	}


	if(state == TransitionOn)
	{
		if(currentTime <= fadeOutBeginTime + fadeOutTime)
		{
			sourceVoice->SetVolume((currentTime - fadeOutBeginTime) / fadeOutTime);
		}else{
			state = Playing;

		}
	}

	if(isPlaying)
	{
		currentTime += timeDelta;
	}

	return true;
}

bool SPEngine::Sound::Play(float fadeTime)
{
	if(SoundError())
	{
		return false;
	}

	if(state != Pausing)
	{
		return false;
	}

	if ( FAILED(sourceVoice->Start( 0, XAUDIO2_COMMIT_NOW ) ) )
	{
		return false;
	}
	state = TransitionOn;
	isPlaying = true;
	FadeOut(fadeTime);
	return true;
}

bool SPEngine::Sound::Play()
{
	if(SoundError())return false;
	if(state != Pausing)return false;
	if ( FAILED(sourceVoice->Start( 0, XAUDIO2_COMMIT_NOW ) ) )
	{
		return false;
	}

	state = Playing;
	sourceVoice->SetVolume(settedVolume);
	isPlaying = true;
	return true;
}

void SPEngine::Sound::Shutdown()
{
	if(sourceVoice)
	{
		sourceVoice->Stop(0);
		sourceVoice->DestroyVoice();
		sourceVoice = NULL;
	}

	delete buffer.pAudioData;
}

void SPEngine::Sound::Stop()
{
	if(SoundError())return;
	if(state != Pausing)return;
	//need to reload buffer
	if(FAILED(sourceVoice->Stop( 0, XAUDIO2_COMMIT_NOW )))
		return;
	sourceVoice->FlushSourceBuffers();
	sourceVoice->SubmitSourceBuffer( &buffer );

	currentTime = 0;
	isPlaying = false;
}

void SPEngine::Sound::Stop(float fadeOutSecond)
{
	if(SoundError())return;
	if(state == Playing)
	{
		state = TransitionOff;
		isPausingStop = true;
		FadeOut(fadeOutSecond);
	}
}

void SPEngine::Sound::Pause()
{
	if(SoundError())return;
	if(state != Playing)return;
	Pause(0.01f);
}

void SPEngine::Sound::Pause(float fadeOutSecond)
{
	if(SoundError())return;
	if(state == Playing)
	{
		//sourceVoice->Stop( 0, XAUDIO2_COMMIT_NOW );
		state = TransitionOff;
		FadeOut(fadeOutSecond);
	}
}

void SPEngine::Sound::GetVolume(float &volume)
{
	if(SoundError())return;
	if(sourceVoice == NULL) return;
	volume = settedVolume;
	//sourceVoice->GetVolume(&volume);
}

void SPEngine::Sound::SetVolume(float volume)
{
	if(SoundError())return;
	if(sourceVoice == NULL) return;
	settedVolume = volume;
	//sourceVoice->SetVolume(volume);
}

bool SPEngine::Sound::SetRadio(float radio)
{
	if(SoundError())return false;
	if(FAILED(sourceVoice->SetFrequencyRatio(radio)))
		return false;
	else return true;
}

float SPEngine::Sound::GetLength()
{
	int stereo = 2;
	int numberBytePerChannalSample = 2;
	int bytePerSample = stereo * numberBytePerChannalSample;
	int sampleRate = 44100;
	float seconds = buffer.AudioBytes / (float)(sampleRate * bytePerSample);
	return seconds;
}

bool SPEngine::Sound::IsPlaying()
{
	//if(sourceVoice == NULL) return;
	//XAUDIO2_VOICE_STATE voiceState;
	//XAUDIO2_BUFFER bufferTemp;
	//sourceVoice->GetState(&voiceState);
	//((XAUDIO2_BUFFER*)(voiceState.pCurrentBufferContext))->PlayBegin;
	return isPlaying;
}

double SPEngine::Sound::TestUse()
{
	XAUDIO2_VOICE_STATE voiceState;
	//XAUDIO2_BUFFER bufferTemp;
	sourceVoice->GetState(&voiceState);
	return (double)((XAUDIO2_BUFFER*)(&voiceState.pCurrentBufferContext))->LoopBegin;
}

void SPEngine::Sound::UpdateSoundPosition( float x, float y, float z )
{

}

HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if( 0 == ReadFile( hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if( 0 == ReadFile( hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL ) )
			hr = HRESULT_FROM_WIN32( GetLastError() );

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if( 0 == ReadFile( hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL ) )
				hr = HRESULT_FROM_WIN32( GetLastError() );
			break;

		default:
			if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, dwChunkDataSize, NULL, FILE_CURRENT ) )
				return HRESULT_FROM_WIN32( GetLastError() );            
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}


	return S_OK;

}

HRESULT Sound::ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if( INVALID_SET_FILE_POINTER == SetFilePointer( hFile, bufferoffset, NULL, FILE_BEGIN ) )
		return HRESULT_FROM_WIN32( GetLastError() );
	DWORD dwRead;
	if( 0 == ReadFile( hFile, buffer, buffersize, &dwRead, NULL ) )
		hr = HRESULT_FROM_WIN32( GetLastError() );
	return hr;
}

void Sound::InitSound(float gradualIn, float gradualOut)
{
	songLength = GetLength();
	currentTime = 0;
	isPlaying = false;
	settedVolume = 1;
	gradualInTime = gradualIn;
	gradualOutTime = gradualOut;
	state = Pausing;
	fadeOutTime = 0;
	fadeOutBeginTime = 0;
	isPausingStop = false;
}

void Sound::FadeOut(float second)
{
	fadeOutBeginTime = currentTime;
	fadeOutTime = second;
}

bool Sound::SoundError()
{
	if(!sourceVoice) return true;
	return false;
}