#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIDialogBox.h"

using namespace KScript;

class SSFWaitDialog : public SScriptFunction
{
	float totalTimeS;
	bool isDisplayingFinished;
	bool isWaitingAuto;

public:
	SSFWaitDialog()
	{
		totalTimeS = 0;
		isDisplayingFinished = false;
		isWaitingAuto = false;
	}

	virtual ~SSFWaitDialog(){}

	bool Function(VariableMap args, bool isRead)
	{
		SUIDialogBoxPtr dialogBox;

		if (IsSet(L"box", args))
		{
			SPString name = args[L"box"].value;
			dialogBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);
		}
		
		if (!dialogBox)
		{
			return false;
		}

		if (IsSet(L"has_text_to_add", args))
		{
			if (SPStringHelper::StringToInt(args[L"has_text_to_add"].value))
			{
				dialogBox->MarkTextToAdd();
			}

			args.erase(L"has_text_to_add");
		}

		if (IsSet(L"has_text_to_clear", args))
		{
			if (SPStringHelper::StringToInt(args[L"has_text_to_clear"].value))
			{
				dialogBox->MarkTextToClear();
			}

			args.erase(L"has_text_to_clear");
		}

		//
		// If skip mode on and not auto mode, just skip waiting.
		// 

		if (SScriptManager::GetSingleton().IsSkipModeOn())
		{
			if (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAll
				|| (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipRead && isRead ))
			{
				dialogBox->Skip();
				refreshScreen = true;
				waiting = false;
				return true;
			}
			else if (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAuto)
			{
				//
				// Auto mode
				// 

				//
				// Reset waiting flag.
				// 

				if (!waiting)
				{
					isDisplayingFinished = false;
					isWaitingAuto = false;
				}

				waiting = true;
				refreshScreen = true;

				//
				// If displaying completed.
				// 

				if (!isWaitingAuto && (!dialogBox || !dialogBox->IsDisplaying()))
				{
					isDisplayingFinished = true;
					isWaitingAuto = true;
					waiting = true;
					return true;
				}				

				//
				// Wait till completed.
				// 

				if (isWaitingAuto && (!dialogBox || !dialogBox->IsDisplaying()))
				{
					//
					// If is displaying finished, reset displaying state.
					// 

					if (isDisplayingFinished)
					{
						isDisplayingFinished = false;
						waiting = true;
						totalTimeS = 0;
					}					

					totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

					refreshScreen = true;

					if (totalTimeS > SScriptManager::GetSingleton().GetAutoWaitTimeS())
					{
						totalTimeS = 0;

						if (dialogBox->IsDisplayAllDone())
						{
							waiting = false;
							isWaitingAuto = false;
						}
						
						dialogBox->Next();
						return true;
					}

					return false;
				}				
			}			
		}

		waiting = true;
		refreshScreen = true;

		if (!dialogBox || dialogBox->IsDisplayAllDone())
		{
			waiting = false;
			return true;
		}

		return false;
	}
};

