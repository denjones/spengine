// SPShower.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SPShower.h"
#include <SPEngine.h>
#include "SPGameShow.h"
#include "node.h"
#include <iostream>
//#include <vld.h> // Memory leaks detection


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

}

int _tmain(int argc, wchar_t** argv)
{
	//
	// Start memory leaks detection.
	//
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(84680);

	HWND hWnd = GetConsoleWindow();
	ShowWindow( hWnd, SW_HIDE );
	HINSTANCE hInstance = GetModuleHandle(NULL);
	SPGameFactory<SPGameShow>::GetSingleton()->Produce(hInstance);
	if (argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			SPString arg = argv[i];
			
			if (arg == L"-d")
			{
				SPConfigManager::GetSingleton()->SetDebug(true);
			}
			else if (arg == L"-l")
			{
				SPLogHelper::TurnOnLogging();
			}
		}
	}
	SPGameManager::GetSingleton()->Start();

	return 0;
}

