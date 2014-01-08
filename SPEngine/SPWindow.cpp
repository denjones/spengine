//////////////////////////////////////////////////////////////////////////
/// @file		SPWindow.cpp the implement file of base SPWindow class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPWindow.h"
#include "SPEngine.h"
#include "SPGame.h"
#include <mmsystem.h>
#include "SPGameManager.h"

namespace SPEngine
{
	//SPGame* SPWindow::currentGame = NULL;

	SPWindow::SPWindow(){}

	SPWindow::SPWindow(HINSTANCE hInstance, int width, int height, bool fullScreen)
	{
		Initialize(hInstance, width, height, fullScreen);
	}

	SPWindow::~SPWindow(void) {	}

	bool SPWindow::Initialize(HINSTANCE hInstance, int setWidth, int setHeight, bool fullScreen)
	{		
		hWnd = NULL;
		hInst = NULL;
		hCursor = LoadCursor(NULL, IDC_ARROW);

		width = setWidth;
		height = setHeight;
		hInst = hInstance;
		isFullScreen = fullScreen;
		isLastActive = true;
		isActive = true;

		LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInstance, IDC_SPENGINE, szWindowClass, MAX_LOADSTRING);

		// Register window class.
		RegisterWindowClass(hInstance);

		// Create window handle.
		hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | 
			WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 0, width, height, GetDesktopWindow(),
			NULL, hInstance, NULL);

		if (!hWnd)
		{
			return false;
		}

		return true;
	}

	ATOM SPWindow::RegisterWindowClass( HINSTANCE hInstance )
	{
		// Instantiate Window class.
		WNDCLASSEX wcex;

		// Set window properties.
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW; //CS_CLASSDC 
		wcex.lpfnWndProc	= WindowProcess;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPENGINE));
		wcex.hCursor		= NULL;
		wcex.hbrBackground	= NULL;	//(HBRUSH)(COLOR_WINDOW+1);	
		wcex.lpszMenuName	= NULL;	// Menu is not necessary.
		wcex.lpszClassName	= szWindowClass;
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		// Register.
		return RegisterClassEx(&wcex);
	}

	bool SPWindow::UnregisterWindowClass()
	{
		UnregisterClass(szWindowClass, hInst);

		return true;
	}

	LRESULT CALLBACK SPWindow::WindowProcess( HWND hWnd,
		UINT message, WPARAM wParam, LPARAM lParam )
	{

		//  WM_COMMAND	- process the application menu
		//  WM_PAINT	- Paint the main window
		//  WM_DESTROY	- post a quit message and return
		switch (message)
		{
			// Check if the game thread is exited before quiting.
			case WM_CLOSE:
				SPGameManager::GetSingleton().GetGame()->ExitButtonPressed();
				//SPGameManager::GetSingleton().GetGame()->ExitGameThread();
				//PostMessage(hWnd, WM_QUIT, NULL, NULL);
				break;

			// Custom message post by game thread.
			case WM_GAMETHREADEXIT:
				PostMessage(hWnd, WM_QUIT, NULL, NULL);
				break;

			case WM_MOUSEMOVE:
				::SetCursor(SPWindow::GetSingleton().GetCursor());

			default:
				// If the message is none of the above, 
				// parse the message with following method.
				return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

	void SPWindow::Show()
	{
		AdjustMainWindow(isFullScreen, GetWidth(), GetHeight());
	}

	void SPWindow::Update()
	{
		UpdateWindow(hWnd);
	}

	bool SPWindow::Update( float timeDelta )
	{
		isLastActive = isActive;

		HWND topHWnd;
		topHWnd = GetForegroundWindow();

		isActive = topHWnd == hWnd;

		return true;
	}

	int	SPWindow::EnterMsgLoop()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		static float lastTime = (float)timeGetTime();

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				// Translate message.
				TranslateMessage(&msg);

				// Send the message to the processing method (WndProc()).
				DispatchMessage(&msg);
			}			
		}

		return msg.wParam;
	}

	HWND SPWindow::GetHWnd()
	{
		return hWnd;
	}

	HINSTANCE SPWindow::GetHInstance()
	{
		return hInst;
	}

	RECT SPWindow::CalculateWindowRect(HWND hWndToAdjust, SIZE szDesiredClient)
	{
		// declare a RECT to hold the results of our calculations
		RECT rcDesiredWindowRect;
		ZeroMemory(&rcDesiredWindowRect, sizeof( rcDesiredWindowRect ));

		// get the current window rect and its client rect
		RECT rcCurrentWindowRect;
		RECT rcCurrentClientRect;

		GetWindowRect(hWndToAdjust, &rcCurrentWindowRect);
		GetClientRect(hWndToAdjust, &rcCurrentClientRect);

		// get the difference between the current and desired client areas
		SIZE szClientDifference;

		szClientDifference.cx = (rcCurrentClientRect.right  
			- szDesiredClient.cx);
		szClientDifference.cy = (rcCurrentClientRect.bottom 
			- szDesiredClient.cy);

		// get the difference between the current window rect and the desired
		// desired window rect
		rcDesiredWindowRect.left   = rcCurrentWindowRect.left;
		rcDesiredWindowRect.top    = rcCurrentWindowRect.top;
		rcDesiredWindowRect.right  = (rcCurrentWindowRect.right 
			- szClientDifference.cx);
		rcDesiredWindowRect.bottom = (rcCurrentWindowRect.bottom 
			- szClientDifference.cy);

		return rcDesiredWindowRect;
	}

	void SPWindow::AdjustMainWindow(bool bExclusive, 
		int nScreenWidth, int nScreenHeight)
	{
		SPLogHelper::WriteLog(SPStringHelper::Format("[SPWindow] Adjusting window to %d x %d", nScreenWidth, nScreenHeight));	
		string winMode = bExclusive ? "full screen":"windowed";
		SPLogHelper::WriteLog("[SPWindow] Window mode: " + winMode);

		width = nScreenWidth;
		height = nScreenHeight;

		Hide();

		// Check if the window need to be resized.
		bool bNeedToResize = false;

		if (!bExclusive)
		{
			UINT nClientWidth;
			UINT nClientHeight;

			if( IsIconic( hWnd ) )
			{
				// Window is currently minimized. To tell if it needs to resize, 
				// get the client rect of window when its restored the 
				// hard way using GetWindowPlacement()
				WINDOWPLACEMENT wp;
				ZeroMemory( &wp, sizeof( WINDOWPLACEMENT ) );
				wp.length = sizeof( WINDOWPLACEMENT );
				GetWindowPlacement( hWnd, &wp );

				if( ( wp.flags & WPF_RESTORETOMAXIMIZED ) != 0 && wp.showCmd == SW_SHOWMINIMIZED )
				{
					// WPF_RESTORETOMAXIMIZED means that when the window is restored it will
					// be maximized.  So maximize the window temporarily to get the client rect 
					// when the window is maximized.  GetSystemMetrics( SM_CXMAXIMIZED ) will give this 
					// information if the window is on the primary but this will work on multimon.
					ShowWindow( hWnd, SW_RESTORE );
					RECT rcClient;
					GetClientRect( hWnd, &rcClient );
					nClientWidth = ( UINT )( rcClient.right - rcClient.left );
					nClientHeight = ( UINT )( rcClient.bottom - rcClient.top );
					ShowWindow( hWnd, SW_MINIMIZE );
				}
				else
				{
					// Use wp.rcNormalPosition to get the client rect, but wp.rcNormalPosition 
					// includes the window frame so subtract it
					RECT rcFrame = {0};
					AdjustWindowRect( &rcFrame, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, false);
					LONG nFrameWidth = rcFrame.right - rcFrame.left;
					LONG nFrameHeight = rcFrame.bottom - rcFrame.top;
					nClientWidth = ( UINT )( wp.rcNormalPosition.right - wp.rcNormalPosition.left - nFrameWidth );
					nClientHeight = ( UINT )( wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - nFrameHeight );
				}
			}
			else
			{
				// Window is restored or maximized so just get its client rect
				RECT rcClient;
				GetClientRect( hWnd, &rcClient );
				nClientWidth = ( UINT )( rcClient.right - rcClient.left );
				nClientHeight = ( UINT )( rcClient.bottom - rcClient.top );
			}

			// Now that we know the client rect, compare it against the back buffer size
			// to see if the client rect is already the right size
			if( nClientWidth != nScreenWidth ||
				nClientHeight != nScreenHeight )
			{
				bNeedToResize = true;
			}
		}
			
		if (bNeedToResize)
		{
			// Need to resize, so if window is maximized or minimized then restore the window
			if( IsIconic( hWnd ) )
			{
				ShowWindow( hWnd, SW_RESTORE );
			}
			
			if( IsZoomed( hWnd ) ) // doing the IsIconic() check first also handles the WPF_RESTORETOMAXIMIZED case
			{
				ShowWindow( hWnd, SW_RESTORE );
			}
			
			// Make a window rect with a client rect that is the same size as the backbuffer
			RECT rcWindow = {0};
			rcWindow.right = ( long )( nScreenWidth );
			rcWindow.bottom = ( long )( nScreenHeight );
			AdjustWindowRect( &rcWindow, GetWindowLong( hWnd, GWL_STYLE ), false );

			// Resize the window.  It is important to adjust the window size 
			// after resetting the device rather than beforehand to ensure 
			// that the monitor resolution is correct and does not limit the size of the new window.
			int cx = ( int )( rcWindow.right - rcWindow.left );
			int cy = ( int )( rcWindow.bottom - rcWindow.top );
			SetWindowPos( hWnd, 0, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE );
		}

		// Make the window visible
		if( !IsWindowVisible( hWnd ) )
		{
			ShowWindow( hWnd, SW_SHOW );
		}

		// Ensure that the display doesn't power down when fullscreen but does when windowed
		if( isFullScreen )
		{
			SetThreadExecutionState( ES_DISPLAY_REQUIRED | ES_CONTINUOUS );
		}
		else
		{
			SetThreadExecutionState( ES_CONTINUOUS );
		}

		//if( bExclusive && !isFullScreen)
		//{

		//	
		//	resizelock.Lock();
		//	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP |WS_SYSMENU |WS_VISIBLE);
		//	resizelock.Unlock();

		//	////Set the window position
		//	RECT windowRect;
		//	GetWindowRect(hWnd, &windowRect);

		//	resizelock.Lock();
		//	SetWindowPos(hWnd, HWND_NOTOPMOST,
		//		windowRect.left, windowRect.top,
		//		(windowRect.right - windowRect.left),
		//		(windowRect.bottom - windowRect.top),
		//		NULL);
		//	resizelock.Unlock();

		//	isFullScreen = true;

		//}
		//else
		//{
		//	// windowed mode code

		//	//RECT clientRect;
		//	//GetClientRect(hWnd, &clientRect);

		//	//if (clientRect.right - clientRect.left == nScreenWidth &&
		//	//	clientRect.bottom - clientRect.top == nScreenHeight)
		//	//{
		//	//	Unhide();
		//	//	return;
		//	//}

		//	Hide();

		//	// calculate the new window rect
		//	SIZE szDesiredClient;

		//	szDesiredClient.cx = nScreenWidth;
		//	szDesiredClient.cy = nScreenHeight;

		//	// resize the window according to the new rect
		//	resizelock.Lock();
		//	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPED | 
		//		WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
		//	resizelock.Unlock();

		//	//SetWindowPos(hWnd, HWND_NOTOPMOST,
		//	//	rcNewWindowRect.left, rcNewWindowRect.top,
		//	//	(rcNewWindowRect.right - rcNewWindowRect.left),
		//	//	(rcNewWindowRect.bottom - rcNewWindowRect.top),
		//	//	NULL);
		//	RECT rcNewWindowRect = CalculateWindowRect(
		//		hWnd, szDesiredClient);

		//	resizelock.Lock();
		//	SetWindowPos(hWnd, HWND_NOTOPMOST,
		//		rcNewWindowRect.left, rcNewWindowRect.top,
		//		(rcNewWindowRect.right - rcNewWindowRect.left),
		//		(rcNewWindowRect.bottom - rcNewWindowRect.top),
		//		NULL);
		//	resizelock.Unlock();

		//	//MoveWindow(hWnd, rcNewWindowRect.left, rcNewWindowRect.top, 
		//	//	(rcNewWindowRect.right - rcNewWindowRect.left),
		//	//	(rcNewWindowRect.bottom - rcNewWindowRect.top), true);

		//	rcNewWindowRect = CalculateWindowRect(
		//		hWnd, szDesiredClient);

		//	MoveWindow(hWnd, rcNewWindowRect.left, rcNewWindowRect.top, 
		//		(rcNewWindowRect.right - rcNewWindowRect.left),
		//		(rcNewWindowRect.bottom - rcNewWindowRect.top), true);

		//	isFullScreen = false;

		//}

		//// unhide the window now that we're done with it
		//Unhide();

		isFullScreen = bExclusive;
	}

	int SPWindow::GetWidth()
	{
		return width;
	}

	int SPWindow::GetHeight()
	{
		return height;
	}

	void SPWindow::Hide()
	{
		ShowWindow(hWnd, SW_HIDE);
	}

	void SPWindow::Unhide()
	{
		ShowWindow(hWnd, SW_SHOW);
	}

	bool SPWindow::IsActive()
	{
		return isActive;
	}

	bool SPWindow::IsJustActive()
	{
		return isActive && !isLastActive;
	}

	void SPWindow::Focus()
	{
		SetForegroundWindow(hWnd);
	}

	HCURSOR SPWindow::GetCursor()
	{
		return hCursor;
	}

	bool SPWindow::SetCursor( HCURSOR setCur )
	{
		hCursor = setCur;

		return true;
	}

#pragma endregion
}

