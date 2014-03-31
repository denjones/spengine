#pragma once
#include <SPEngine.h>

using namespace SPEngine;

class SampleGame : public SPGame
{
	SPTexturePtr texture;
	SPSoundPtr sound;
	SPVideoPtr video;

public:
	SampleGame(HINSTANCE hInstance) : SPGame(hInstance) {}
	SampleGame(void) : SPGame() { texture = NULL; }
	~SampleGame(void) {}

	bool LoadContent()
	{
		if(!SPGame::LoadContent())
		{
			return false;
		}

		// Load texture.
		video = SPVideoManager::GetSingleton()->GetVideo(L"logo01.mpg");
		//video->SetFlipVertical(true);
		video->SetLoopTimes(-1);
		texture = SPTextureManager::GetSingleton()->GetVideo(L"logo01.mpg");

		video->Play();

		return true;
	}

	bool Draw(float timeDelta)
	{
		// Render video texture on screen.
		SPSpriteManager::GetSingleton()->RenderOnScreen(texture, NULL, SPRectangle(0,0,
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth,
			SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight),
			SPColor::White, 1, NULL);

		return SPGame::Draw(timeDelta);
	}
};

