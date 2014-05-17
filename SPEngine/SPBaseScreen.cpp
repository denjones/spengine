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

	void SPBaseScreen::UpdateScreen( float timeDelta, 
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

		Update(timeDelta);
	}

	void SPBaseScreen::ExitScreen()
	{
		if (transitionOffTime == 0)
		{
			Unload();
		}
		else
		{
			isExiting = true;
		}
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

	void SPBaseScreen::Initialize()
	{
	}

	void SPBaseScreen::HandleInput( float timeDelta )
	{
	}

	void SPBaseScreen::Update( float timeDelta )
	{
	}

	void SPBaseScreen::Draw( float timeDelta )
	{
	}

	void SPBaseScreen::Unload()
	{
	}

	void SPBaseScreen::Load()
	{
	}

	void SPBaseScreen::Reload()
	{
		Load();
	}
}