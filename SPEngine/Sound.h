#pragma once
#include<dmusicc.h>
#include<dmusics.h>
#include<cguid.h>
#include <string>
#include <XAudio2.h>
//#include "VoiceCallback.h"

using namespace std;

namespace SPEngine
{
	class SoundManager;

	class Sound
	{
		enum SoundState
		{
			TransitionOn,
			Playing,
			TransitionOff,
			Pausing
		};

		WAVEFORMATEX wfx;
		XAUDIO2_BUFFER buffer;
		IXAudio2SourceVoice* sourceVoice;
		SoundManager* currentManager;
		float songLength;
		float currentTime;
		bool isPlaying;
		float settedVolume;
		float gradualInTime, gradualOutTime;
		//control the pausing fade out
		SoundState state;
		//bool isPausing;
		float fadeOutTime, fadeOutBeginTime;
		bool isPausingStop;
		float StopFadeOutTime;
		//VoiceCallback voiceCallback;

	public:
		Sound(void);
		Sound( SoundManager* manager, string filename, int numRepeats);
		~Sound(void);

		bool Load(SoundManager* manager, string filename, int numRepeats);
		bool Load(SoundManager* manager, string filename, int numRepeats, float gradualIn, float gradualOut);
		bool Play();
		bool Play(float fadeOut);
		void UpdateSoundPosition(float x, float y, float z);
		void Stop();
		void Stop(float fadeOutSecond);
		void Shutdown();
		void Pause();
		void Pause(float fateOutSecond);
		void GetVolume(float &volume);
		void SetVolume(float volume);
		bool SetRadio(float radio);
		float GetLength();
		bool IsPlaying();
		bool Update(float timeDelta);

		double TestUse();

	private:
		HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
		void InitSound(float gradualIn, float gradualOut);
		void FadeOut(float second);
		bool SoundError();
	};
};


