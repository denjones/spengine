#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;
class SSFTrack : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = true;

		if (IsSet(L"name", args))
		{
			SPString name = args[L"name"].value;
			SPString soundName;

			SPSoundTrackPtr track = SPSoundManager::GetSingleton().GetTrack(name);

			if (!track)
			{
				track = SPSoundManager::GetSingleton().CreateSoundTrack(name);
			}

			if (IsSet(L"mute", args))
			{
				SPString isMute = args[L"mute"].value;

				if ((isMute == L"1" && !track->IsMute()) 
					|| (isMute == L"0" && track->IsMute())
					|| (isMute != L"1" && isMute != L"0"))
				{
					track->Mute();
				}

				args.erase(L"mute");
			}

			if (IsSet(L"volume", args))
			{
				float volume = SPStringHelper::StringToFloat(args[L"volume"].value);

				track->SetVolume(volume);

				args.erase(L"volume");
			}

			if (IsSet(L"sound", args))
			{
				soundName = args[L"sound"].value;

				track->SetSound(soundName);

				args.erase(L"sound");
			}
			else if (IsSet(L"src", args))
			{
				SPString path = args[L"src"].value;

				track->SetSound(SPSoundManager::GetSingleton().CreateSound(path, path));

				args.erase(L"src");
			}

			if (IsSet(L"loop", args))
			{
				int loopBegin = 0;

				if (IsSet(L"loop_begin", args))
				{
					loopBegin = SPStringHelper::StringToInt(args[L"loop_begin"].value);

					args.erase(L"loop_begin");
				}

				if (track->GetSound())
				{
					track->GetSound()->SetLoop(SPStringHelper::StringToInt(args[L"loop"].value), loopBegin);
				}

				args.erase(L"loop");
			}			

			if (IsSet(L"control", args))
			{
				SPString state = args[L"control"].value;

				if (state == L"Play")
				{
					track->Play();
				}

				if (state == L"Stop")
				{
					track->Stop();
				}

				if (state == L"Pause")
				{
					track->Pause();
				}

				args.erase(L"control");
			}

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		//SScriptManager::GetSingleton().SetInsertPosFront(1);

		//SScriptManager::GetSingleton().ExecuteInnerScript(L"@wait{time:0}");

		//SScriptManager::GetSingleton().SetInsertPosBack();

		return true;
	}
};

