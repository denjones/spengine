#pragma once
#include "SPComponent.h"
#include "Sound.h"
#include <vector>

using namespace std;

namespace SPEngine
{
	class SPGame;

	class SoundManager :
		public SPComponent
	{
		IXAudio2*	xAudio;
		IXAudio2MasteringVoice* masterVoice;

	public:
		SoundManager(void);
		SoundManager(SPGame* game);
		~SoundManager(void);

		bool Initialize();
		bool Load();
		bool Unload();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);

		//bool AddSound(string soundfile, int numRepeats, int *id);
		bool AddSound(Sound* sound);

		void Play(int id);
		void UpdateSoundPosition(int id, float x,
			float y, float z);
		void Stop(int id);
		void Pause(int id);
		void GetVolume(float &volume);
		void SetVolume(float volume);

		IXAudio2* XAudio();

	private:
		vector<Sound*> sounds;
	};
}


