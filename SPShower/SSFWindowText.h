#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"

using namespace KScript;

class SSFWindowText : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		if (IsSet(L"content", args))
		{
			// Prevent window with same name.

			HWND hWnd = NULL;
			hWnd = FindWindow(NULL, args[L"content"].value.c_str());

			if (hWnd && hWnd != SPWindow::GetSingleton().GetHWnd())
			{
				// Sleeping is just a temp solution.

				SetForegroundWindow(hWnd);
				Sleep(100);
				SPGameManager::GetSingleton().Exit();
				return false;
			}

			SetWindowText(SPWindow::GetSingleton().GetHWnd(), args[L"content"].value.c_str());

			args.erase(L"content");
		}	

		return false;
	}
};

