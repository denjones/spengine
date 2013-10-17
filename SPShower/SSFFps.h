#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"
#include <FPSDisplayer.h>
#include <SPComponentManager.h>

using namespace KScript;

class SSFFps : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		FPSDisplayerPtr displayer = SPComponentManager::GetSingleton().GetComponent(L"fps");

		if (IsSet(L"display", args))
		{
			if(SPStringHelper::StringToInt(args[L"display"].value) != 0)
			{
				displayer->Enable();
			}
			else
			{
				displayer->Disable();
			}

			args.erase(L"display");
		}

		if (IsSet(L"position", args))
		{
			SPString position = args[L"position"].value;

			if (position == L"LeftTop" ||
				position == L"TopLeft")
			{
				displayer->SetLocation(LeftTop);
			}
			else if (position == L"RightTop" ||
				position == L"TopRight")
			{
				displayer->SetLocation(RightTop);
			}
			else if (position == L"LeftBottom" ||
				position == L"BottomLeft")
			{
				displayer->SetLocation(LeftBottom);
			}
			else if (position == L"RightBottom" ||
				position == L"BottomRight")
			{
				displayer->SetLocation(RightBottom);
			}

			args.erase(L"position");
		}

		if (IsSet(L"lock", args))
		{
			int fps = SPStringHelper::StringToInt(args[L"lock"].value);

			if (fps == 0)
			{
				SPGameManager::GetSingleton().GetGame()->UnlockFPS();
			}
			else if (fps > 0)
			{
				SPGameManager::GetSingleton().GetGame()->LockFPSAt(fps);
			}
			
			args.erase(L"lock");
		}

		return false;
	}
};

