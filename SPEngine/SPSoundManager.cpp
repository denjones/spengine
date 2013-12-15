#include "StdAfx.h"
#include "SPSoundManager.h"
#include "SPGame.h"
#include "SPXAudio.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPSoundManager::SPSoundManager(void)
	{
		sounds.Clear();
		tracks.Clear();
		SPXAudio::GetSingleton();
		xAudio = SPXAudio::GetSingletonPtr();
	}

	SPSoundManager::~SPSoundManager(void)
	{
		ReleaseAll();
		xAudio = NULL;
	}

	bool SPEngine::SPSoundManager::ReleaseAll()
	{
		sounds.Clear();
		tracks.Clear();

		return true;
	}

	bool SPEngine::SPSoundManager::Update( float timeElapsed )
	{
		SPWStringMapIterator<SPSoundTrackPtr> iter(&tracks);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			if (iter.CurrentItem())
			{
				iter.CurrentItem()->Update(timeElapsed);
			}			
		}

		return true;
	}

	SPSoundPtr SPEngine::SPSoundManager::AddSound(SPString name, SPSoundPtr sound)
	{
		if (sounds.IsSet(name) && sound->GetPath() != sounds.Get(name)->GetPath())
		{
			sounds.Remove(name);
			sounds.Set(name, sound);
		}
		else if (!sounds.IsSet(name))
		{
			sounds.Set(name, sound);
		}
		
		return sound;
	}

	void SPEngine::SPSoundManager::PlayTrack(SPString track)
	{
		if (tracks.IsSet(track))
		{
			tracks[track]->Play();
		}
	}

	void SPEngine::SPSoundManager::StopTrack(SPString track)
	{
		if (tracks.IsSet(track))
		{
			tracks[track]->Stop();
		}	
	}

	void SPEngine::SPSoundManager::PauseTrack(SPString track)
	{
		if (tracks.IsSet(track))
		{
			tracks[track]->Pause();
		}		
	}

	float SPSoundManager::GetVolume()
	{
		float volume;
		SPXAudio::GetSingleton().GetMasterVoice()->GetVolume(&volume);

		return volume;
	}

	void SPSoundManager::SetVolume(float volume)
	{
		SPXAudio::GetSingleton().GetMasterVoice()->SetVolume(volume);
	}

	bool SPSoundManager::Release( SPString name )
	{
		SPSoundPtr sound = sounds[name];

		SPWStringMapIterator<SPSoundTrackPtr> iter(&tracks);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			if(iter.CurrentItem()->GetSound() == sound)
			{
				iter.CurrentItem()->Unload();
			}
		}

		sounds.Remove(name);
		sound = NULL;

		return true;
	}

	SPSoundPtr SPSoundManager::CreateSound( SPString name, SPString path )
	{
		SPSoundPtr newSound = new SPSound();		

		if (newSound->Load(path, 0, 0))
		{
			return AddSound(name, newSound);
		}

		return NULL;		
	}

	SPSoundTrackPtr SPSoundManager::CreateSoundTrack( SPString track )
	{
		if (!tracks.IsSet(track))
		{
			tracks.Set(track, new SPSoundTrack());
		}	

		return tracks[track];
	}

	void SPSoundManager::PlaySoundInTrack( SPString name, SPString track )
	{
		if (!tracks.IsSet(track))
		{
			SPLogHelper::WriteLog(L"[SPSound] WARNING: Track name invalid! No such track: " + track);
			return;
		}

		if (!sounds.IsSet(name))
		{
			SPLogHelper::WriteLog(L"[SPSound] WARNING: Sound name invalid! No such sound: " + name);
			return;
		}

		tracks[track]->SetSound(name);
	}

	SPSoundPtr SPSoundManager::GetSound( SPString name )
	{
		if (sounds.IsSet(name))
		{
			return sounds[name];
		}		

		return NULL;
	}

	SPEngine::SPSoundTrackPtr SPSoundManager::GetTrack( SPString trackName )
	{
		if (tracks.IsSet(trackName))
		{
			return tracks[trackName];
		}

		return NULL;
	}

	bool SPSoundManager::LoadFromString( SPString stringStream )
	{
		SPString soundsString = SPStringHelper::XMLExcludeFrom(stringStream, L"Sounds");

		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Sounds");

		while(soundsString.size() > 0)
		{
			SPString soundString = SPStringHelper::XMLExcludeFrom(soundsString, L"S");
			soundsString = SPStringHelper::XMLRemoveFirst(soundsString, L"S");

			SPString soundName = SPStringHelper::XMLExcludeFrom(soundString, L"N");
			SPString soundPath = SPStringHelper::XMLExcludeFrom(soundString, L"P");
			SPString soundLoop = SPStringHelper::XMLExcludeFrom(soundString, L"L");
			SPString soundLoopBegin = SPStringHelper::XMLExcludeFrom(soundString, L"LB");

			SPSoundPtr sound = new SPSound();
			sound->Load(soundPath, SPStringHelper::StringToInt(soundLoop), SPStringHelper::StringToInt(soundLoopBegin));

			AddSound(soundName, sound);
		}

		SPString tracksString = SPStringHelper::XMLExcludeFrom(stringStream, L"Tracks");

		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Tracks");

		while(tracksString.size() > 0)
		{
			SPString trackString = SPStringHelper::XMLExcludeFrom(tracksString, L"T");
			tracksString = SPStringHelper::XMLRemoveFirst(tracksString, L"T");

			SPString trackName = SPStringHelper::XMLExcludeFrom(trackString, L"N");
			SPString trackVolume = SPStringHelper::XMLExcludeFrom(trackString, L"V");
			SPString trackSound = SPStringHelper::XMLExcludeFrom(trackString, L"S");
			SPString trackState = SPStringHelper::XMLExcludeFrom(trackString, L"ST");

			SPSoundTrackPtr track = CreateSoundTrack(trackName);
			track->SetVolume(SPStringHelper::StringToFloat(trackVolume));
			track->SetSound(trackSound);

			if (SPStringHelper::StringToInt(trackState))
			{
				track->Play();
			}
		}

		return true;
	}

	SPString SPSoundManager::SaveAsString()
	{
		SPString result;

		result += L"<Sounds>";

		SPWStringMapIterator<SPSoundPtr> iter(&sounds);

		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			result += L"<S>";

			result += L"<N>";
			result += iter.CurrentIndex();
			result += L"</N>";

			result += L"<P>";
			result += iter.CurrentItem()->GetPath();
			result += L"</P>";

			result += L"<L>";
			result += SPStringHelper::ToWString(iter.CurrentItem()->GetLoop());
			result += L"</L>";

			result += L"<LB>";
			result += SPStringHelper::ToWString(iter.CurrentItem()->GetLoopBegin());
			result += L"</LB>";

			result += L"</S>";
		}

		result += L"</Sounds>";

		result += L"<Tracks>";

		SPWStringMapIterator<SPSoundTrackPtr> tIter(&tracks);

		for(tIter.First(); !tIter.IsDone(); tIter.Next())
		{
			result += L"<T>";

			result += L"<N>";
			result += tIter.CurrentIndex();
			result += L"</N>";

			result += L"<V>";
			result += SPStringHelper::ToWString(tIter.CurrentItem()->GetVolume());
			result += L"</V>";

			result += L"<S>";
			result += tIter.CurrentItem()->GetSoundName();
			result += L"</S>";

			result += L"<ST>";
			result += SPStringHelper::ToWString(tIter.CurrentItem()->GetSound()->IsPlaying());
			result += L"</ST>";

			result += L"</T>";
		}

		result += L"</Tracks>";

		result = SPStringHelper::XMLSurroundWith(result, L"SPSoundManager");

		return result;
	}

}