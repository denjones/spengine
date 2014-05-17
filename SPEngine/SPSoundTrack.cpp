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

	void SPSoundTrack::Unload()
	{
		sound = NULL;
	}

	void SPSoundTrack::Pause()
	{
		if (sound)
		{
			sound->Pause();
		}
	}

	void SPSoundTrack::Play()
	{
		if (sound)
		{
			sound->Play();
		}
	}

	void SPSoundTrack::Stop()
	{
		if (sound)
		{
			sound->Stop();
		}
	}

	void SPSoundTrack::Update( float timeDelta )
	{
		if (sound)
		{
			sound->Update(timeDelta);
		}
	}

	SPEngine::SPSoundPtr SPSoundTrack::GetSound()
	{
		return sound;
	}

	void SPSoundTrack::SetSound( SPSoundPtr setSound )
	{
		if (!setSound)
		{
			return;
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
	}

	void SPSoundTrack::SetSound( SPString setSound )
	{
		SPSoundPtr sound = SPSoundManager::GetSingleton()->GetSound(setSound);
		if (!sound)
		{
			sound = SPSoundManager::GetSingleton()->CreateSound(setSound, setSound);
		}

		if (sound)
		{
			soundName = setSound;
			SetSound(sound);
		}
	}

	void SPSoundTrack::SetVolume(float setVol)
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
	}

	float SPSoundTrack::GetVolume()
	{
		return volume;
	}

	bool SPSoundTrack::IsMute()
	{
		return isMute;
	}

	void SPSoundTrack::Mute()
	{
		SetMute(!isMute);	
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