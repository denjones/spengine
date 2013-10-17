#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"

using namespace KScript;
class SSFSound : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"name", args))
		{
			SUIPictureListPtr picture;

			SPString name = args[L"name"].value;

			SPSoundPtr sound = SPSoundManager::GetSingleton().GetSound(name);

			if (IsSet(L"src", args))
			{
				SPString path = args[L"src"].value;
				SPSoundPtr newSound = new SPSound();

				int loopTime = 0;
				int loopBegin = 0;

				if (IsSet(L"loop", args))
				{
					if (IsSet(L"loop_begin", args))
					{
						loopBegin = SPStringHelper::StringToInt(args[L"loop_begin"].value);

						args.erase(L"loop_begin");
					}							

					loopTime = SPStringHelper::StringToInt(args[L"loop"].value);

					args.erase(L"loop");
				}

				if(newSound->Load(path, loopTime, loopBegin, 0, 0))
				{
					if (sound)
					{
						sound->Stop();
					}

					SPSoundManager::GetSingleton().AddSound(name, newSound);

					sound = newSound;
				}

				args.erase(L"src");
			}

			if (!sound)
			{
				return false;
			}

			if (IsSet(L"loop", args))
			{
				int loopBegin = 0;

				if (IsSet(L"loop_begin", args))
				{
					loopBegin = SPStringHelper::StringToInt(args[L"loop_begin"].value);

					args.erase(L"loop_begin");
				}							

				sound->SetLoop(SPStringHelper::StringToInt(args[L"loop"].value), loopBegin);

				args.erase(L"loop");
			}

			if (IsSet(L"control", args))
			{
				SPString state = args[L"control"].value;

				if (state == L"Play")
				{
					sound->Play();
				}

				if (state == L"Stop")
				{
					sound->Stop();
				}

				if (state == L"Pause")
				{
					sound->Pause();
				}

				args.erase(L"control");
			}

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

