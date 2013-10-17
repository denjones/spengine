// SampleSprite2D.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SampleVideo.h"
#include "SampleGame.h"
#include <SPEngine.h>


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	SPGameFactory<SampleGame>::GetSingleton().Produce(hInstance);
	SPGameManager::GetSingleton().Start();

	return 0;
}