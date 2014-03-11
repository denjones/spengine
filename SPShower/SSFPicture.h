#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIVideoManager.h"

using namespace KScript;
class SSFPicture : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		//if (IsSet(L"name", args))
		//{
		//	SUIPictureListPtr picture;

		//	SPString name = args[L"name"].value;

		//	if (SUIPictureManager::GetSingleton().IsPictureVaild(name))
		//	{
		//		picture = SUIPictureManager::GetSingleton().GetPicture(name);
		//	}
		//	else
		//	{
		//		picture = new SUIPictureList();
		//		picture->SetName(name);
		//		SUIPictureManager::GetSingleton().SetPicture(name, picture);
		//	}

		//	picture->SetProperties(args);

		//	SUIPictureManager::GetSingleton().SetCurrentPicture(picture);

		//	if (IsSet(L"src", args))
		//	{
		//		bool isAnime = false;
		//		int row = 1;
		//		int col = 1;
		//		int fps = 14;

		//		if (IsSet(L"row", args))
		//		{
		//			isAnime = true;

		//			row = SPStringHelper::StringToInt(args[L"row"].value);

		//			args.erase(L"row");
		//		}

		//		if (IsSet(L"col", args))
		//		{
		//			isAnime = true;

		//			col = SPStringHelper::StringToInt(args[L"col"].value);

		//			args.erase(L"col");
		//		}

		//		if (IsSet(L"fps", args))
		//		{
		//			isAnime = true;

		//			fps = SPStringHelper::StringToInt(args[L"fps"].value);

		//			args.erase(L"fps");
		//		}

		//		SPTexturePtr tex;

		//		if (isAnime)
		//		{
		//			tex = SPTextureManager::GetSingleton().GetAnime(args[L"src"].value, row, col, fps);
		//		}
		//		else
		//		{
		//			tex = SPTextureManager::GetSingleton().GetTexture(args[L"src"].value);
		//		}

		//		picture->SetBaseImage(tex);

		//		args.erase(L"src");
		//	}

		//	if (IsSet(L"video", args))
		//	{
		//		SPVideoTexturePtr videoTex = SUIVideoManager::GetSingleton().GetVideoTexture(args[L"video"].value);

		//		if (videoTex)
		//		{
		//			picture->SetBaseImage(videoTex);
		//		}

		//		args.erase(L"video");
		//	}

		//	if (IsSet(L"particle_system", args))
		//	{
		//		SPParticleSystemTexturePtr particleSysTex = SPTextureManager::GetSingleton().GetParticleSystem(args[L"particle_system"].value);

		//		if (particleSysTex)
		//		{
		//			picture->SetBaseImage(particleSysTex);
		//		}

		//		args.erase(L"particle_system");
		//	}

		//	SUIPictureManager::GetSingleton().SetCurrentPicture(picture);

		//	args.erase(L"name");
		//}

		//OutLogUnusedProperties(args);

		return true;
	}
};

