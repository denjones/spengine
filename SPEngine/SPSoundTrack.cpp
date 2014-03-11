#include "StdAfx.h"
#include "SPSoundTrack.h"
#include "SPSoundManager.h"

namespace SPEngine
{
	SPSoundTrack::SPSoundTrack(void)
	{
		isMute = false;
		volume = 1;
		loopTimes = 0;
		soundName = L"";
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

		sound->SetLoopTimes(loopTimes);

		soundName = setSound->GetPath();

		return true;
	}

	bool SPSoundTrack::SetSound( SPString setSound )
	{
		SPSoundPtr sound = SPSoundManager::GetSingleton().GetSound(setSound);
		if (!sound)
		{
			sound = SPSoundManager::GetSingleton().CreateSound(setSound, setSound);
		}

		if (sound)
		{
			soundName = setSound;
			return SetSound(sound);
		}
		
		return false;
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
		SetMute(!isMute);	

		return true;
	}

	SPString SPSoundTrack::GetSoundName()
	{
		return soundName;
	}

	void SPSoundTrack::SetLoopTimes( int time )
	{
		loopTimes = time;
	}

	void SPSoundTrack::SetMute( bool mute )
	{
		isMute = mute;

		if (isMute)
		{
			sound->SetVolume(0);
		}
		else
		{
			sound->SetVolume(volume);
		}
	}

	int SPSoundTrack::GetLoopTimes()
	{
		return loopTimes;
	}

}