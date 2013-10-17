#include "StdAfx.h"
#include "SPSound.h"
#include "SPXAudio.h"
#include "SPLogHelper.h"
#include "SPFileManager.h"
#include "SPFile.h"
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <vector>
#include <algorithm>
#include "SPSoundFile.h"
#include "SPWavFile.h"
#include "SPOggFile.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT  ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#define SOUND_TYPE_OGG L"ogg"
#define SOUND_TYPE_WAV L"wav"

#pragma warning(disable:4244)


using namespace std;

namespace SPEngine
{
	SPSound::SPSound(void) 
	{
		InitSound(0, 0);
	}

	SPSound::SPSound(SPString filename)
	{
		InitSound(0, 0);
		Load(filename, XAUDIO2_LOOP_INFINITE, 0, 0, 0);
	}

	SPSound::~SPSound(void)
	{
		ShutDown();
	}

	bool SPSound::Load(SPString filename, int numRepeats, int repeatBegin)
	{	
		return Load(filename, numRepeats, repeatBegin, 0, 0);
	}

	bool SPSound::Load(SPString filename, int numRepeats, int repeatBegin, float gradualIn, float gradualOut)
	{
		//
		// Initialize state.
		// 

		state = Pausing;

		path = filename;

		InitSound(gradualIn, gradualOut);

		SetLoopTimes(numRepeats);

		return true;
	}

	bool SPSound::Update(float timeDelta)
	{
		//if (!sourceVoice)
		//{
		//	return false;
		//}

		//// Fade in / out when pauses.
		//if(state == TransitionOff)
		//{
		//	if(currentTime <= fadeOutBeginTime + fadeOutTime)
		//	{
		//		sourceVoice->SetVolume(settedVolume * 
		//			((fadeOutBeginTime + fadeOutTime - currentTime) / fadeOutTime));
		//	}
		//	else
		//	{
		//		//isPausing = false;
		//		state = Pausing;
		//		isPlaying = false;
		//		sourceVoice->Stop(0);
		//		if(isPausingStop)
		//		{
		//			sourceVoice->FlushSourceBuffers();

		//			LockStreamingThread();
		//			sourceVoice->SubmitSourceBuffer(&buffer);
		//			UnlockStreamingThread();

		//			currentTime = 0;
		//			isPausingStop = false;
		//		}
		//	}
		//}

		//if(state != TransitionOff)
		//{
		//	//float lastVolume;
		//	float songTime = currentTime;
		//	while(songTime >= songLength && songLength != 0) 
		//	{				
		//		songTime -= songLength;
		//	}

		//	if(songTime < gradualInTime)
		//	{
		//		// Fade in.
		//		sourceVoice->SetVolume(settedVolume * 
		//			(songTime / gradualInTime)); 
		//	}
		//	else if(songTime > songLength - gradualOutTime)
		//	{
		//		sourceVoice->SetVolume(settedVolume * ((songLength - songTime)	/ gradualOutTime));// Fadout
		//	}
		//	else 
		//	{
		//		sourceVoice->SetVolume(settedVolume);
		//	}
		//}


		//if(state == TransitionOn)
		//{
		//	if(currentTime <= fadeOutBeginTime + fadeOutTime)
		//	{
		//		sourceVoice->SetVolume((currentTime - fadeOutBeginTime) / fadeOutTime);
		//	}
		//	else
		//	{
		//		state = Playing;

		//	}
		//}

		//if(isPlaying)
		//{
		//	currentTime += timeDelta;
		//}

		return true;
	}

	bool SPSound::Play(float fadeTime)
	{
		if (!Play())
		{
			return false;
		}

		state = TransitionOn;
		isPlaying = true;
		FadeOut(fadeTime);
		return true;
	}

	bool SPSound::Play()
	{
		if(SoundError())
		{
			return false;
		}

		if(state != Pausing)
		{
			return false;
		}

		//
		// Run streaming thread.
		// 

		if (!isStreamingThreadRunning || isStoping)
		{
			while (isStoping)
			{
				Sleep(1);
			}

			isStreamingThreadRunning = CloseHandle(
				CreateThread(NULL, 0, StreamingThreadProc, (void*)this, 0, NULL)) == TRUE;
		}
		else
		{
			SetEvent( hPause );
		}

		state = Playing;
		//sourceVoice->SetVolume(settedVolume);
		isPlaying = true;

		return true;
	}

	void SPSound::ShutDown()
	{
		if (isStreamingThreadRunning)
		{
			Stop();
		}
	}

	void SPSound::Stop()
	{
		if(SoundError())
		{
			return;
		}

		//
		// Stop streaming thread.
		// 
		
		if (!isStreamingThreadRunning)
		{
			return;
		}

		stopingLock.Lock();
		isStoping = true;
		stopingLock.Unlock();

		// Comment of waiting to stop, not sure if it is safe

		while(isStreamingThreadRunning)
		{
			Sleep(1);
		}

		stopingLock.Lock();
		isStoping = false;
		state = Pausing;
		stopingLock.Unlock();
	}

	void SPSound::Stop(float fadeOutSecond)
	{
		if(SoundError())
		{
			return;
		}

		if(state == Playing)
		{
			state = TransitionOff;
			isPausingStop = true;
			FadeOut(fadeOutSecond);
		}
	}

	void SPSound::Pause()
	{
		if(SoundError())
		{
			return;
		}

		if(state != Playing)
		{
			return;
		}

		if(state == Playing)
		{
			//sourceVoice->Stop( 0, XAUDIO2_COMMIT_NOW );

			pausingLock.Lock();
			isPausing = true;
			pausingLock.Unlock();

			state = Pausing;
		}
	}

	void SPSound::Pause(float fadeOutSecond)
	{
		if(SoundError())
		{
			return;
		}

		if(state == Playing)
		{
			//sourceVoice->Stop( 0, XAUDIO2_COMMIT_NOW );

			pausingLock.Lock();
			isPausing = true;
			pausingLock.Unlock();

			state = TransitionOff;
			FadeOut(fadeOutSecond);
		}
	}

	float SPSound::GetVolume()
	{
		if(SoundError())
		{
			return 0;
		}

		volumeLock.Lock();
		float result = volume;
		volumeLock.Unlock();

		//if(sourceVoice == NULL)
		//{
		//	return 0;
		//}

		return result;
	}

	void SPSound::SetVolume(float volume)
	{
		if(SoundError())
		{
			return;
		}

		//if(sourceVoice == NULL)
		//{
		//	return;
		//}


		volumeLock.Lock();
		if(volume >=0 && this->volume != volume)
		{
			this->volume = volume;
			isVolumeChanged = true;
		}
		volumeLock.Unlock();

		//settedVolume = volume;
		//sourceVoice->SetVolume(volume);
	}

	bool SPSound::SetRadio(float radio)
	{
		if(SoundError())
		{
			return false;
		}

		//if(FAILED(sourceVoice->SetFrequencyRatio(radio)))
		//{
		//	return false;
		//}
		
		return true;
	}

	float SPSound::GetLength()
	{
		//int stereo = wfx.nChannels;
		//int numberBytePerChannalSample = wfx.wBitsPerSample / 8;
		//int bytePerSample = stereo * numberBytePerChannalSample;
		//int sampleRate = wfx.nSamplesPerSec;
		//LockStreamingThread();
		//float seconds = buffer.AudioBytes / (float)(sampleRate * bytePerSample);
		//UnlockStreamingThread();
		//return seconds;
		return 0;
	}

	bool SPSound::IsPlaying()
	{
		return isPlaying;
	}

	void SPSound::InitSound(float gradualIn, float gradualOut)
	{
		isStreamingThreadRunning = false;
		volume = 1;
		leftLoopTimes = 0;
		isPausing = false;
		isStoping = false;
		isVolumeChanged = false;
		hPause = CreateEvent( NULL, FALSE, FALSE, NULL );
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
		typeName = path;
		typeName = typeName.substr(typeName.find_last_of(L".") + 1);
		transform(typeName.begin(), typeName.end(), typeName.begin(), tolower);
	}

	void SPSound::FadeOut(float second)
	{
		fadeOutBeginTime = currentTime;
		fadeOutTime = second;
	}

	bool SPSound::SoundError()
	{
		//if(!sourceVoice)
		//{
		//	return true;
		//}

		return false;
	}

	bool SPSound::SetLoop( int setTimes, int loopBegin = 0 )
	{
		SetLoopTimes(setTimes);
		return true;
	}

	SPString SPSound::GetPath()
	{
		return path;
	}

	int SPSound::GetLoop()
	{
		return leftLoopTimes;//buffer.LoopCount;
	}

	int SPSound::GetLoopBegin()
	{
		return 0;//buffer.LoopBegin;
	}

	DWORD WINAPI SPSound::StreamingThreadProc( void* context )
	{
		//
		// Required by XAudio2
		// 

		CoInitializeEx( NULL, COINIT_MULTITHREADED );

		if (context == NULL)
		{
			CoUninitialize();
			return -1;
		}

		//SPLogHelper::WriteLog(L"[SPSound] Streaming thread running");

		//
		// Convert context.
		// 

		SPSound* sound = (SPSound*)context;

		// 
		// Set running flag.
		// 

		sound->LockStreamingThread();
		sound->isStreamingThreadRunning = true;
		sound->UnlockStreamingThread();		

		// 
		// Instantiate the callback class
		// 

		SPSoundStreamingContext callback;

		//
		// Open the sound file.
		// 

		SPSoundFilePtr soundFile = NULL;

		if (sound->typeName == SOUND_TYPE_OGG)
		{
			soundFile = new SPOggFile(sound->path);
		}
		else if (sound->typeName == SOUND_TYPE_WAV)
		{
			soundFile = new SPWavFile(sound->path);
		}

		if (!soundFile || !soundFile->IsLoaded())
		{
			CoUninitialize();
			sound->LockStreamingThread();
			sound->isStreamingThreadRunning = false;
			sound->UnlockStreamingThread();

			SPLogHelper::WriteLog(L"[SPSound] Failed to load sound file! Streaming thread exited.");

			return -1;
		}

		//
		// Load wfm
		// 

		WAVEFORMATEX wfx;
		soundFile->GetWFX(wfx);

		//
		// Create the voice
		// 

		IXAudio2SourceVoice* sourceVoice = NULL;

		HRESULT hr;

		if(!SPXAudio::GetSingleton().GetXAudio() 
			|| FAILED(hr = SPXAudio::GetSingleton().GetXAudio()->CreateSourceVoice(
			&sourceVoice, (WAVEFORMATEX*)&wfx, 0, 
			XAUDIO2_DEFAULT_FREQ_RATIO, &callback) ) ) 
		{
			SPLogHelper::WriteLog(L"[XAudio] ERROR: Failed to create source voice!");
			CoUninitialize();
			sound->LockStreamingThread();
			sound->isStreamingThreadRunning = false;
			sound->UnlockStreamingThread();
			return -1;
		}

		sourceVoice->Start(0,0);

		// 
		// Create streaming buffer.
		// 

		BYTE buffers [MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];
		LONG currentDiskReadBuffer = 0;
		LONG currentPosition = 0;

		//
		// Loop and stream.
		// 

		bool continueStreaming = true;

		while ( continueStreaming )
		{
			//
			// Check for stop and pause signal.
			// 

			if (sound->IsPausing())
			{
				sourceVoice->Stop();
				sound->SetPaused();
				WaitForSingleObject(sound->hPause, INFINITE);
				CloseHandle(sound->hPause);
				sourceVoice->Start();
			}

			if (sound->IsStoping())
			{
				sourceVoice->Stop();
				sourceVoice->FlushSourceBuffers();
				break;
			}

			if (sound->IsVolumeChanged())
			{
				sourceVoice->SetVolume(sound->volume);
				sound->VolumeChanged();
			}

			//
			// Read stream data.
			// 

			DWORD cbValid = 0;
			bool eof;
			soundFile->NextStreamData(buffers[currentDiskReadBuffer], 
				STREAMING_BUFFER_SIZE, cbValid, eof);

			//
			// Keep one buffer always free for disk I/O.
			//

			XAUDIO2_VOICE_STATE state;
			while(true)
			{
				// Get voice state.
				sourceVoice->GetState( &state );

				// If there is free buffer, just skip.
				if( state.BuffersQueued < MAX_BUFFER_COUNT - 1 )
				{
					break;
				}

				// Else wait for current playing buffer to be free.
				WaitForSingleObject( callback.hBufferEndEvent, INFINITE );

			}

			//
			// Check for stop and pause signal.
			// 

			if (sound->IsPausing())
			{
				sourceVoice->Stop();
				sound->SetPaused();
				WaitForSingleObject(sound->hPause, INFINITE);
				CloseHandle(sound->hPause);
				sourceVoice->Start();
			}

			if (sound->IsStoping())
			{
				sourceVoice->Stop();
				sourceVoice->FlushSourceBuffers();
				break;
			}

			if (sound->IsVolumeChanged())
			{
				sourceVoice->SetVolume(sound->volume);
				sound->VolumeChanged();
			}

			//
			// At this point we have a buffer full of audio and enough room to submit it, so
			// let's submit it and get another read request going.
			//

			XAUDIO2_BUFFER buf = {0};
			buf.AudioBytes = cbValid;
			buf.pAudioData = (BYTE*)buffers[currentDiskReadBuffer];

			if( eof )
			{
				// 
				// End of file means the whole sound has been buffered 
				// and to be finished playing.
				// 

				buf.Flags = XAUDIO2_END_OF_STREAM;
				sound->ReduceLoopTimesByOne();

				if (sound->GetLoopTimes() == 0)
				{
					//
					// loop end and exit streaming.
					// 

					continueStreaming = false;
				}

			}

			//
			// Submit the buffer to be played.
			// 

			HRESULT hr =sourceVoice->SubmitSourceBuffer( &buf );

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog("[XAudio] ERROR: Failed to summit source buffer");
				CoUninitialize();
				sound->LockStreamingThread();
				sound->isStreamingThreadRunning = false;
				sound->UnlockStreamingThread();
				return false;
			}

			//
			// Move to next buffer.
			// 

			currentDiskReadBuffer++;
			currentDiskReadBuffer %= MAX_BUFFER_COUNT;
		}

		//
		// Wait till finished playing the last buffer.
		// 

		XAUDIO2_VOICE_STATE state;
		while( sourceVoice->GetState( &state ), state.BuffersQueued > 0 )
		{
			WaitForSingleObject( callback.hBufferEndEvent, INFINITE );
		}

		//
		// Shutdown.
		// 

		sourceVoice->Stop();
		sourceVoice->FlushSourceBuffers();
		sourceVoice->DestroyVoice();
		sourceVoice = NULL;

		soundFile->Close();

		// 
		// Reset running flag.
		// 

		sound->LockStreamingThread();
		sound->isStreamingThreadRunning = false;
		sound->UnlockStreamingThread();

		CoUninitialize();

		return 0;
		
	}

	bool SPSound::LockStreamingThread()
	{
		threadLock.Lock();

		return true;
	}

	bool SPSound::UnlockStreamingThread()
	{
		threadLock.Unlock();

		return true;
	}

	bool SPSound::SetLoopTimes( int setTimes )
	{
		if (setTimes < 0)
		{
			setTimes = -1;
		}

		loopTimesLock.Lock();
		leftLoopTimes = setTimes;
		loopTimesLock.Unlock();

		return true;
	}

	int SPSound::GetLoopTimes()
	{
		int times = 0;

		loopTimesLock.Lock();
		times = leftLoopTimes;
		loopTimesLock.Unlock();

		return times;
	}

	bool SPSound::ReduceLoopTimesByOne()
	{
		loopTimesLock.Lock();
		if(leftLoopTimes > 0)
		{
			leftLoopTimes--;
		}
		loopTimesLock.Unlock();

		return true;
	}

	bool SPSound::IsStoping()
	{
		bool result = false;
		stopingLock.Lock();
		result = isStoping;
		stopingLock.Unlock();

		return result;
	}

	bool SPSound::IsPausing()
	{
		bool result = false;
		pausingLock.Lock();
		result = isPausing;
		pausingLock.Unlock();

		return result;
	}

	bool SPSound::SetPaused()
	{
		pausingLock.Lock();
		isPausing = false;
		pausingLock.Unlock();

		return true;
	}

	bool SPSound::IsVolumeChanged()
	{
		bool result = false;
		volumeLock.Lock();
		result = isVolumeChanged;
		volumeLock.Unlock();

		return result;
	}

	bool SPSound::VolumeChanged()
	{
		volumeLock.Lock();
		isVolumeChanged = false;
		volumeLock.Unlock();

		return true;
	}

}