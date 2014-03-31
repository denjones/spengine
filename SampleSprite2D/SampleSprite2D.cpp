// SampleSprite2D.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SampleSprite2D.h"
#include <SPEngine.h>
#include "SampleGame.h"

//
// Memory leaks detection
//

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

int _tmain(int argc, wchar_t** argv)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	HINSTANCE hInstance = GetModuleHandle(NULL);
	SPGameFactory<SampleGame>::GetSingleton()->Produce(hInstance);
	SPGameManager::GetSingleton()->Start();

	return 0;
}