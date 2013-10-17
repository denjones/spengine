#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIVideoManager.h"

using namespace KScript;
class SSFVideo : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"name", args))
		{
			SPVideoPtr video;

			SPString name = args[L"name"].value;

			video = SUIVideoManager::GetSingleton().GetVideo(name);

			if (IsSet(L"src", args))
			{
				SUIVideoManager::GetSingleton().SetVideoPath(name, args[L"src"].value);

				SPVideoPtr newViedo = SUIVideoManager::GetSingleton().GetVideo(name);

				if (video != newViedo)
				{
					if (video)
					{
						video->Stop();
					}

					video = newViedo;
				}			

				args.erase(L"src");
			}

			if (!video)
			{
				return false;
			}

			if (IsSet(L"loop", args))
			{
				video->SetLoopTimes(SPStringHelper::StringToInt(args[L"loop"].value));

				args.erase(L"loop");
			}

			if (IsSet(L"flip", args))
			{
				SPString state = args[L"flip"].value;
				
				if(state == L"Vertical")
				{
					video->SetFlipVertical(true);
				}

				if (state == L"None")
				{
					video->SetFlipVertical(false);
				}

				args.erase(L"flip");
			}

			if (IsSet(L"control", args))
			{
				SPString state = args[L"control"].value;

				if (state == L"Play")
				{
					video->Play();
				}

				if (state == L"Stop")
				{
					video->Stop();
				}

				if (state == L"Pause")
				{
					video->Pause();
				}

				args.erase(L"control");
			}

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

