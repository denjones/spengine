#include "StdAfx.h"
#include "SPBaseScreen.h"
#include "SPGame.h"
#include "SPGameManager.h"

namespace SPEngine
{
	SPBaseScreen::SPBaseScreen(void)
	{
		isExiting = false;
		isInputValid = true;
		isPopup = false;
	}

	SPBaseScreen::~SPBaseScreen(void)
	{
	}

	bool SPBaseScreen::UpdateScreen( float timeDelta, 
		bool inputValid, bool visible )
	{
		isInputValid = inputValid;
		isDisplay = visible;

		if (isExiting)
		{
			state = TransitionOff;

			if (UpdateTransition(timeDelta, -1))
			{
				Unload();
			}
		}
		else if (!visible)
		{
			if (!UpdateTransition(timeDelta, -1))
			{
				state = TransitionOff;
			}
			else
			{
				state = Hidden;
			}
		}
		else
		{
			if (!UpdateTransition(timeDelta, 1))
			{
				state = TransitionOn;
			}
			else
			{
				state = Active;
			}
		}		

		return Update(timeDelta);
	}

	bool SPBaseScreen::ExitScreen()
	{
		if (transitionOffTime == 0)
		{
			Unload();
		}
		else
		{
			isExiting = true;
		}

		return true;
	}

	bool SPBaseScreen::IsPopup()
	{
		return isPopup;
	}

	bool SPBaseScreen::IsExiting()
	{
		return isExiting;
	}

	bool SPBaseScreen::IsInputValid()
	{
		return isInputValid;
	}

	bool SPBaseScreen::Initialize()
	{
		return true;
	}

	bool SPBaseScreen::HandleInput( float timeDelta )
	{
		return true;
	}

	bool SPBaseScreen::Update( float timeDelta )
	{
		return true;
	}

	bool SPBaseScreen::Draw( float timeDelta )
	{
		return true;
	}

	bool SPBaseScreen::Unload()
	{
		return true;
	}

	bool SPBaseScreen::Load()
	{
		return true;
	}

	bool SPBaseScreen::Reload()
	{
		return Load();
	}
}