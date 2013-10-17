// SampleSprite2D.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SampleScript.h"
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

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//
	// Start memory leaks detection.
	//
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(435960);


	SPGameFactory<SampleGame>::GetSingleton().Produce(hInstance);
	SPGameManager::GetSingleton().Start();

	return 0;
}