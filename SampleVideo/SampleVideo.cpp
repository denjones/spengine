// SampleSprite2D.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SampleVideo.h"
#include "SampleGame.h"
#include <SPEngine.h>


int _tmain(int argc, wchar_t** argv)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	HINSTANCE hInstance = GetModuleHandle(NULL);
	SPGameFactory<SampleGame>::GetSingleton()->Produce(hInstance);
	SPGameManager::GetSingleton()->Start();

	return 0;
}