#include "StdAfx.h"
#include "SPSoundTrack.h"
#include "SPSoundManager.h"

namespace SPEngine
{
	SPSoundTrack::SPSoundTrack(void)
	{
		isMute = false;
		volume = 1;
		Unload();
	}


	SPSoundTrack::~SPSoundTrack(void)
	{
		Unload();
	}

	bool SPSoundTrack::Unload()
	{
		sound = NULL;

		return true;
	}

	bool SPSoundTrack::Pause()
	{
		if (sound)
		{
			sound->Pause();
		}

		return true;
	}

	bool SPSoundTrack::Play()
	{
		if (sound)
		{
			sound->Play();
		}

		return true;
	}

	bool SPSoundTrack::Stop()
	{
		if (sound)
		{
			sound->Stop();
		}

		return true;
	}

	bool SPSoundTrack::Update( float timeDelta )
	{
		if (sound)
		{
			return sound->Update(timeDelta);
		}

		return true;
	}

	SPEngine::SPSoundPtr SPSoundTrack::GetSound()
	{
		return sound;
	}

	bool SPSoundTrack::SetSound( SPSoundPtr setSound )
	{
		if (!setSound)
		{
			return false;
		}

		if (sound)
		{
			sound->Stop();
		}

		sound = setSound;

		if (isMute)
		{
			sound->SetVolume(0);
		}
		else
		{
			sound->SetVolume(volume);
		}

		soundName = setSound->GetPath();

		return true;
	}

	bool SPSoundTrack::SetSound( SPString setSound )
	{
		bool result = SetSound(SPSoundManager::GetSingleton().GetSound(setSound));
		soundName = setSound;
		return result;
	}

	bool SPSoundTrack::SetVolume(float setVol)
	{
		volume = setVol;

		if(sound)
		{
			if (isMute)
			{
				sound->SetVolume(0);
			}
			else
			{
				sound->SetVolume(volume);
			}
		}		

		return true;
	}

	float SPSoundTrack::GetVolume()
	{
		return volume;
	}

	bool SPSoundTrack::IsMute()
	{
		return isMute;
	}

	bool SPSoundTrack::Mute()
	{
		isMute = !isMute;

		if (isMute)
		{
			sound->SetVolume(0);
		}
		else
		{
			sound->SetVolume(volume);
		}

		return true;
	}

	SPString SPSoundTrack::GetSoundName()
	{
		return soundName;
	}

}