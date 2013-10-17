#pragma once
#include "SPComponent.h"
#include "UIComponent.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "SoundManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include <d3d9.h>
#include "SPWindow.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "ConfigManager.h"

namespace SPEngine
{
	class ScreenManager;

	class BaseScreen : public UIComponent
	{
	protected:
		bool isPopup;
		bool isExiting;
		bool isInputValid;

		SPWindow*		window;
		ScreenManager*	screenManager;
		SpriteManager*	spriteManager;
		InputManager*	inputManager;
		FontManager*	fontManager;
		Camera*			camera;
		SoundManager*	soundManager;
		LightManager*	lightManager;
		MaterialManager* materialManager;
		VideoManager*	videoManager;
		ConfigManager*	configManager;
		LPDIRECT3DDEVICE9 d3dDevice;
		

	public:
		BaseScreen(void);
		BaseScreen(ScreenManager*);
		~BaseScreen(void);

		bool Register(ScreenManager*);

	public:
		/// @brief    GetDevice
		/// @return   LPDIRECT3DDEVICE9
		LPDIRECT3DDEVICE9	GetDevice();

		/// @brief    GetInput
		/// @return   InputManager*
		InputManager*	GetInput();

		/// @brief    GetSprite
		/// @return   SpriteManager*
		SpriteManager*	GetSprite();

		/// @brief    GetSound
		/// @return   SoundManager*		
		SoundManager*	GetSound();

		/// @brief    GetFont
		/// @return   FontManager*	
		FontManager*	GetFont();

		/// @brief    GetCamera
		/// @return   Camera*
		Camera*			GetCamera();

		/// @brief    GetWindow
		/// @return   SPWindow*
		SPWindow*		GetWindow();

		/// @brief    GetVideo
		/// @return   VideoManager*
		VideoManager*	GetVideo();

		/// @brief    GetConfig
		/// @return   ConfigManager*
		ConfigManager*	GetConfig();

		/// @brief    GetWidth
		/// @return   width
		int				GetWidth();

		/// @brief    GetHeight
		/// @return   height
		int				GetHeight();
		
		bool ExitScreen();		
		bool UpdateScreen(
			float timeDelta, bool inputValid, bool visible);

	public:
		virtual bool Initialize();
		virtual bool HandleInput(float timeDelta);
		virtual bool Update(float timeDelta);
		virtual bool Draw(float timeDelta);
		virtual bool Unload();
		virtual bool Load();

		bool IsPopup();
		bool IsExiting();
		bool IsInputValid();
	};
}
