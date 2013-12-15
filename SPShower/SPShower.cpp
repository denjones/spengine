// SPShower.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SPShower.h"
#include <SPEngine.h>
#include "SPGameShow.h"
//#include <vld.h> // Memory leaks detection

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//
	// Start memory leaks detection.
	//
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(84680);

	SPGameFactory<SPGameShow>::GetSingleton().Produce(hInstance);
	SPGameManager::GetSingleton().Start();

	return 0;
}

