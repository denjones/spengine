//////////////////////////////////////////////////////////////////////////
/// @file		SPSoundManager.h the header file of SPSoundManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-31
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPComponent.h"
#include "SPSound.h"
#include <vector>
#include "SPSingleton.h"
#include "SPSoundTrack.h"
#include "SPStringMap.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSoundManager class to hold and manage sound and sound track.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSoundManager :
		public SPComponent,
		public SPSingleton<SPSoundManager>
	{
		SPWStringMap<SPSoundPtr>		sounds;
		SPWStringMap<SPSoundTrackPtr>	tracks;
		SPComponentPtr					xAudio;

	public:
		SPSoundManager(void);
		virtual ~SPSoundManager(void);

		bool ReleaseAll();
		bool Release(SPString name);
		bool Update(float timeElapsed);

		SPSoundPtr GetSound(SPString name);
		SPSoundTrackPtr GetTrack(SPString trackName);

		SPSoundPtr CreateSound(SPString name, SPString path);
		SPSoundPtr AddSound(SPString name, SPSoundPtr sound);
		SPSoundTrackPtr CreateSoundTrack(SPString track);
		bool RemoveSoundTrack(SPString track);
		
		void PlaySoundInTrack(SPString name, SPString track);
		void PlayTrack(SPString track);
		void StopTrack(SPString track);
		void PauseTrack(SPString track);

		float GetVolume();
		void SetVolume(float volume);

		virtual bool LoadFromString(SPString stringStream);
		virtual SPString SaveAsString();
	};
}


