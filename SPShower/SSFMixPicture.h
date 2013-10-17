#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIMixModeManager.h"

#pragma warning (disable:4244)

using namespace KScript;
class SSFMixPicture : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		SUIMixImage mixImage;
		SUIPictureListPtr target;

		mixImage.SetProperties(args);

		if (IsSet(L"target", args))
		{
			target = SUIPictureManager::GetSingleton().GetPicture(args[L"target"].value);

			args.erase(L"target");
		}
		else
		{
			target = SUIPictureManager::GetSingleton().GetCurrentPicture();
		}

		if (!target)
		{
			return true;
		}

		SUIPictureManager::GetSingleton().SetCurrentPicture(target);

		if (IsSet(L"layer", args))
		{
			mixImage.Layer = SPStringHelper::StringToFloat(args[L"layer"].value);

			args.erase(L"layer");
		}

		if (IsSet(L"src", args))
		{
			bool isAnime = false;
			int row = 1;
			int col = 1;
			int fps = 14;

			if (IsSet(L"row", args))
			{
				isAnime = true;

				row = SPStringHelper::StringToInt(args[L"row"].value);

				args.erase(L"row");
			}

			if (IsSet(L"col", args))
			{
				isAnime = true;

				col = SPStringHelper::StringToInt(args[L"col"].value);

				args.erase(L"col");
			}

			if (IsSet(L"fps", args))
			{
				isAnime = true;

				col = SPStringHelper::StringToInt(args[L"fps"].value);

				args.erase(L"fps");
			}

			SPTexturePtr tex;

			if (isAnime)
			{
				tex = SPTextureManager::GetSingleton().GetAnime(args[L"src"].value, row, col, fps);
			}
			else
			{
				tex = SPTextureManager::GetSingleton().GetTexture(args[L"src"].value);
			}

			mixImage.Image = tex;

			args.erase(L"src");
		}

		if (IsSet(L"mix_mode", args))
		{
			SPString modeName = args[L"mix_mode"].value;

			SUIMixModePtr mixMode = SUIMixModeManager::GetSingleton().GetMixMode(modeName);
			
			mixImage.MixMode = mixMode;

			args.erase(L"mix_mode");
		}

		if (IsSet(L"mix_mode_src", args))
		{
			SPString path = args[L"mix_mode_src"].value;

			SUIMixModePtr mixMode = SUIMixModeManager::GetSingleton().GetMixMode(path);

			if (!mixMode)
			{
				mixMode = SUIMixModeManager::GetSingleton().CreateMixMode(path);
			}

			mixImage.MixMode = mixMode;

			args.erase(L"mix_mode_src");
		}

		target->SetMixImage(mixImage);

		OutLogUnusedProperties(args);

		return true;
	}
};

