#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIEventHandler.h"

using namespace KScript;

class SSFWait;

class SUIWaitHandler : public SUIEventHandler
{
public:
	SSFWait* ssf;

	SUIWaitHandler(SSFWait* wc);
	virtual ~SUIWaitHandler(){}
	virtual bool Function( SUIEventPtr e );
};

class SSFWait : public SScriptFunction
{
public:
	float totalTimeS;
	SUIComponentPtr waitComponent;
	SUIEventHandlerPtr originClickHandler;
	SUIEventHandlerPtr originKeyHandler;
	SUIEventHandlerPtr waitHandler;
	UINT key;
	bool isClicked;
	bool isWaitClick;
	bool isWaitKey;

public:
	SSFWait()
	{
		waitHandler = new SUIWaitHandler(this);
		originClickHandler = NULL;
		originKeyHandler = NULL;
		waitComponent = NULL;
		isClicked = false;
		totalTimeS = 0;
		key = 0;
		isWaitKey = false;
		isWaitClick = false;
	}

	virtual ~SSFWait(){}

	bool Function(VariableMap args, bool isRead)
	{
		float waitTimeS = 0;

		//
		// If skip mode on and not auto mode, just skip waiting.
		// 

		if (SScriptManager::GetSingleton().IsSkipModeOn())
		{
			if(SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAll
				|| (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipRead && isRead ))
			{
				if (waitComponent)
				{
					if (isWaitClick)
					{
						waitComponent->catchMouseLeftClick = originClickHandler;
						isWaitClick = false;
					}

					if (isWaitKey)
					{
						waitComponent->onKeyDown[key] = originKeyHandler;
						isWaitKey = false;
					}					

					originClickHandler = NULL;
					originKeyHandler = NULL;
					waitComponent = NULL;
					key = 0;
				}

				refreshScreen = true;
				waiting = false;
				return true;
			}
		}

		//
		// else if time set, wait until time out.
		// 

		if (IsSet(L"time", args)
			|| (SScriptManager::GetSingleton().IsSkipModeOn() 
			&& SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAuto))
		{
			waitTimeS = IsSet(L"time", args)?SPStringHelper::StringToFloat(args[L"time"].value):0;

			if (SScriptManager::GetSingleton().IsSkipModeOn() 
				&& SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAuto)
			{
				waitTimeS += SScriptManager::GetSingleton().GetAutoWaitTimeS();
			}

			if (!waiting)
			{
				waiting = true;
				totalTimeS = 0;
			}

			totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

			refreshScreen = true;

			if (totalTimeS > waitTimeS)
			{
				if (waitComponent)
				{
					if (isWaitClick)
					{
						waitComponent->catchMouseLeftClick = originClickHandler;
						isWaitClick = false;
					}

					if (isWaitKey)
					{
						waitComponent->onKeyDown[key] = originKeyHandler;
						isWaitKey = false;
					}		

					originClickHandler = NULL;
					originKeyHandler = NULL;
					waitComponent = NULL;
					key = 0;
				}

				totalTimeS = 0;
				waiting = false;
				return true;
			}

			args.erase(L"time");
		}

		if (IsSet(L"component", args))
		{
			SPString name = args[L"component"].value;

			waitComponent = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			args.erase(L"component");
		}

		//
		// Wait click
		// 

		if (IsSet(L"click",args))
		{			
			isWaitClick = true;

			if (SPStringHelper::StringToInt(args[L"click"].value) != 0)
			{
				if (waitComponent)
				{
					if (!waiting || waitComponent->catchMouseLeftClick != waitHandler)
					{
						originClickHandler = waitComponent->catchMouseLeftClick;
						waitComponent->catchMouseLeftClick = waitHandler;
					}
					else if (isClicked)
					{
						isClicked = false;

						if (isWaitClick)
						{
							waitComponent->catchMouseLeftClick = originClickHandler;
							isWaitClick = false;
						}

						if (isWaitKey)
						{
							waitComponent->onKeyDown[key] = originKeyHandler;
							isWaitKey = false;
						}		

						originClickHandler = NULL;
						originKeyHandler = NULL;
						waitComponent = NULL;
						key = 0;

						refreshScreen = false;
						waiting = false;
						return true;
					}

				}
				else if (SPInputManager::GetSingleton().GetMouse()->ButtonJustDown(0))
				{
					SUIManager::GetSingleton().InterceptMouseBotton(0);
					refreshScreen = true;
					waiting = false;
					return true;
				}
			}		

			args.erase(L"click");
		}

		if (IsSet(L"key",args))
		{
			isWaitKey = true;

			key = SPInputManager::GetSingleton().GetKeyboard()->KeyNameToKey(args[L"key"].value);

			if (key != 0)
			{
				if (waitComponent)
				{
					if (!waiting || waitComponent->onKeyDown[key] != waitHandler)
					{
						originKeyHandler = waitComponent->onKeyDown[key];
						waitComponent->onKeyDown[key] = waitHandler;
					}
					else if (isClicked)
					{
						isClicked = false;

						if (isWaitClick)
						{
							waitComponent->catchMouseLeftClick = originClickHandler;
							isWaitClick = false;
						}

						if (isWaitKey)
						{
							waitComponent->onKeyDown[key] = originKeyHandler;
							isWaitKey = false;
						}		

						originClickHandler = NULL;
						originKeyHandler = NULL;
						waitComponent = NULL;
						key = 0;

						refreshScreen = false;
						waiting = false;
						return true;
					}
				}
				else if (SPInputManager::GetSingleton().GetKeyboard()->ButtonJustDown(key))
				{
					SUIManager::GetSingleton().InterceptKeyboardKey(key);
					refreshScreen = true;
					waiting = false;
					return true;
				}				
			}		

			args.erase(L"key");
		}

		//if (refreshScreen == false)
		//{
		//	refreshScreen = true;
		//	waiting = true;
		//	return true;
		//}

		waiting = true;
		return false;
	}
};

SUIWaitHandler::SUIWaitHandler(SSFWait* wc)
{
	ssf = wc;
}

bool SUIWaitHandler::Function( SUIEventPtr e )
{
	ssf->isClicked = true;

	return true;
}