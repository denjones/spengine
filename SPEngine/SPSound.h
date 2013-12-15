//////////////////////////////////////////////////////////////////////////
/// @file		SPSound.h the header file of SPSound class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include<dmusicc.h>
#include<dmusics.h>
#include<cguid.h>
#include <XAudio2.h>
#include "SPPointer.h"
#include "SPFile.h"
#include "SPSoundStreamingContext.h"
#include "SPXAudio.h"

#define STREAMING_BUFFER_SIZE 65536//*10
#define MAX_BUFFER_COUNT 3

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSound class to represent a sound object.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSound
	{
		enum SoundState
		{
			TransitionOn,
			Playing,
			TransitionOff,
			Pausing,
			Stoping,
		};

		SPPointer<SPXAudio> xAudio;

		// ID
		SPString path;

		// Properties
		float songLength;
		float currentTime;
		bool isPlaying;
		float settedVolume;
		float gradualInTime;
		float gradualOutTime;
		SPString typeName;

		// Loop
		int leftLoopTimes;
		CCritSec loopTimesLock;

		// Volume
		float volume;
		bool isVolumeChanged;
		CCritSec volumeLock;

		// Pause
		bool isPausing;
		CCritSec pausingLock;
		HANDLE hPause;

		// Stop 
		bool isStoping;
		CCritSec stopingLock;

		//control the pausing fade out
		SoundState state;

		//bool isPausing;
		float fadeOutTime;
		float fadeOutBeginTime;
		bool isPausingStop;		
		float StopFadeOutTime;		

		// Streaming associated.
		bool isStreamingThreadRunning;
		CCritSec threadLock;

	public:
		SPSound(void);
		SPSound(SPString filename);
		virtual ~SPSound(void);

		bool Load(SPString filename, int numRepeats, int repeatBegin);
		bool Load(
			SPString filename,
			int numRepeats,
			int repeatBegin,
			float gradualIn,
			float gradualOut);
		void ShutDown();

		bool Play();
		bool Play(float fadeOut);
		void Stop();
		void Stop(float fadeOutSecond);
		
		void Pause();
		void Pause(float fateOutSecond);
		float GetVolume();
		void SetVolume(float volume);
		bool SetRadio(float radio);
		float GetLength();
		bool IsPlaying();
		bool Update(float timeDelta);

		bool SetLoop(int setTimes , int loopBegin);
		int GetLoop();
		int GetLoopBegin();

		bool LockStreamingThread();
		bool UnlockStreamingThread();

		SPString GetPath();

		// loop time get/setter
		bool SetLoopTimes(int setTimes);
		int GetLoopTimes();		

	private:
		static DWORD WINAPI StreamingThreadProc(void* context);		
		bool ReduceLoopTimesByOne();
		bool IsVolumeChanged();
		bool IsStoping();
		bool IsPausing();
		bool SetPaused();
		bool VolumeChanged();

		void InitSound(float gradualIn, float gradualOut);
		void FadeOut(float second);
		bool SoundError();
	};

	typedef SPPointer<SPSound> SPSoundPtr;
}


