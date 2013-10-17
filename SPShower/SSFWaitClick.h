#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIEventHandler.h"

using namespace KScript;

class SSFWaitClick;

class SUIWaitClickHandler : public SUIEventHandler
{
public:
	SSFWaitClick* ssf;

	SUIWaitClickHandler(SSFWaitClick* wc);
	virtual ~SUIWaitClickHandler(){}
	virtual bool Function( SUIEventPtr e );
};

class SSFWaitClick : public SScriptFunction
{
public:
	float totalTimeS;
	SUIComponentPtr waitComponent;
	SUIEventHandlerPtr originHandler;
	SUIEventHandlerPtr waitHandler;
	bool isClicked;


	SSFWaitClick()
	{
		 waitHandler = new SUIWaitClickHandler(this);
		 originHandler = NULL;
		 waitComponent = NULL;
		 isClicked = false;
		 totalTimeS = 0;
	}

	virtual ~SSFWaitClick(){}

	bool Function(VariableMap args, bool isRead)
	{
		//
		// If skip mode on and not auto mode, just skip waiting.
		// 

		if (SScriptManager::GetSingleton().IsSkipModeOn())
		{
			if (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAll
				|| (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipRead && isRead ))
			{
				if (waitComponent)
				{
					waitComponent->catchMouseLeftClick = originHandler;
					originHandler = NULL;
					waitComponent = NULL;
				}

				refreshScreen = true;
				waiting = false;
				return true;
			}
			else if (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAuto)
			{
				if (!waiting)
				{
					waiting = true;
					totalTimeS = 0;
				}

				totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

				refreshScreen = true;

				if (totalTimeS > SScriptManager::GetSingleton().GetAutoWaitTimeS())
				{
					if (waitComponent)
					{
						waitComponent->catchMouseLeftClick = originHandler;
						originHandler = NULL;
						waitComponent = NULL;
					}

					totalTimeS = 0;
					waiting = false;
					return true;
				}
			}			
		}

		if (IsSet(L"component", args))
		{
			SPString name = args[L"component"].value;

			args.erase(L"component");

			waitComponent = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (waitComponent)
			{
				if (!waiting || waitComponent->catchMouseLeftClick != waitHandler)
				{
					originHandler = waitComponent->catchMouseLeftClick;
					waitComponent->catchMouseLeftClick = waitHandler;
				}
				else if (isClicked)
				{
					isClicked = false;
					waitComponent->catchMouseLeftClick = originHandler;
					originHandler = NULL;
					waitComponent = NULL;
					refreshScreen = false;
					waiting = false;
					return true;
				}

				refreshScreen = true;
				waiting = true;
				return true;
			}
		}

		if (refreshScreen == false)
		{
			refreshScreen = true;
			waiting = true;
			return true;
		}
		
		if(SPInputManager::GetSingleton().GetMouse()->ButtonJustDown(0))
		{
			SUIManager::GetSingleton().InterceptMouseBotton(0);
			refreshScreen = false;
			waiting = false;
			return true;
		}

		waiting = true;
		return false;
	}
};

SUIWaitClickHandler::SUIWaitClickHandler(SSFWaitClick* wc)
{
	ssf = wc;
}

bool SUIWaitClickHandler::Function( SUIEventPtr e )
{
	ssf->isClicked = true;

	return true;
}
