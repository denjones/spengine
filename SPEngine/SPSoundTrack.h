//////////////////////////////////////////////////////////////////////////
/// @file		SPSoundTrack.h the header file of SPSoundTrack class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPPointer.h"
#include "SPSound.h"
#include "ISPUpdatable.h"
#include <list>

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPSoundTrack class to represent a sound track which can hold
	/// and play a sound.
	///
	//////////////////////////////////////////////////////////////////////
	class SPSoundTrack :
		public ISPUpdatable
	{
		SPSoundPtr	sound;
		SPString	soundName;
		float		volume;
		bool	isMute;
		int		loopTimes;

	public:
		SPSoundPtr GetSound();
		void SetSound(SPSoundPtr setSound);
		void SetSound(SPString setSound);
		void SetVolume(float setVol);
		float GetVolume();
		void SetSoundName();
		void SetLoopTimes(int time);
		int GetLoopTimes();
		SPString GetSoundName();
		bool IsMute();
		void Mute();
		void SetMute(bool mute);

	public:
		SPSoundTrack(void);
		virtual ~SPSoundTrack(void);

		void Unload();
		void Pause();
		void Play();
		void Stop();
		void Update(float timeDelta);

	};

	typedef SPPointer<SPSoundTrack> SPSoundTrackPtr;
}