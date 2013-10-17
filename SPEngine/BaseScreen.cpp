#include "StdAfx.h"
#include "BaseScreen.h"
#include "screenManager.h"
#include "SPGame.h"

namespace SPEngine
{
	BaseScreen::BaseScreen(void)
	{
		screenManager = NULL;
		isExiting = false;
		isInputValid = true;
		isPopup = false;
	}

	BaseScreen::BaseScreen(ScreenManager* manager)
	{
		screenManager = manager;
	}

	BaseScreen::~BaseScreen(void)
	{
	}

	bool BaseScreen::UpdateScreen( float timeDelta, 
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

		return true;
	}

	bool BaseScreen::ExitScreen()
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

	bool BaseScreen::IsPopup()
	{
		return isPopup;
	}

	bool BaseScreen::IsExiting()
	{
		return isExiting;
	}

	bool BaseScreen::IsInputValid()
	{
		return isInputValid;
	}

	bool BaseScreen::Register( ScreenManager* manager)
	{
		screenManager = manager;
		d3dDevice = manager->CurrentGame()->GetDevice();
		spriteManager = manager->CurrentGame()->GetSprite();
		fontManager = manager->CurrentGame()->GetFont();
		camera = manager->CurrentGame()->GetCamera();
		inputManager = manager->CurrentGame()->GetInput();
		window = manager->CurrentGame()->GetWindow();
		soundManager = manager->CurrentGame()->GetSound();
		videoManager = manager->CurrentGame()->GetVideo();
		configManager = manager->CurrentGame()->GetConfig();

		return true;
	}

	LPDIRECT3DDEVICE9 BaseScreen::GetDevice()
	{
		return d3dDevice;
	}

	InputManager* BaseScreen::GetInput()
	{
		return inputManager;
	}

	SpriteManager* BaseScreen::GetSprite()
	{
		return spriteManager;
	}

	SoundManager* BaseScreen::GetSound()
	{
		return soundManager;
	}

	FontManager* BaseScreen::GetFont()
	{
		return fontManager;
	}

	Camera* BaseScreen::GetCamera()
	{
		return camera;
	}

	SPWindow* BaseScreen::GetWindow()
	{
		return window;
	}

	int BaseScreen::GetWidth()
	{
		return screenManager->CurrentGame()->GetWidth();
	}

	int BaseScreen::GetHeight()
	{
		return screenManager->CurrentGame()->GetHeight();
	}

	VideoManager* BaseScreen::GetVideo()
	{
		return videoManager;
	}

	ConfigManager* BaseScreen::GetConfig()
	{
		return configManager;
	}

	bool BaseScreen::Initialize()
	{
		return true;
	}

	bool BaseScreen::HandleInput( float timeDelta )
	{
		return true;
	}

	bool BaseScreen::Update( float timeDelta )
	{
		return true;
	}

	bool BaseScreen::Draw( float timeDelta )
	{
		return true;
	}

	bool BaseScreen::Unload()
	{
		return true;
	}

	bool BaseScreen::Load()
	{
		return true;
	}

}