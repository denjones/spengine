//////////////////////////////////////////////////////////////////////////
/// @file		SPWindow.h the header file of base SPWindow class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPSingleton.h"
#include "ISPUpdatable.h"

#define WM_GAMETHREADEXIT (WM_APP + 1)

namespace SPEngine
{
	#define MAX_LOADSTRING 100

	///////////////////////////////////////////////////////////////////////
	/// @brief SPWindow. The class to represent a game window, and contain
	/// all window methods.
	///
	//////////////////////////////////////////////////////////////////////////
	class SPWindow : 
		public ISPUpdatable,
		public SPSingleton<SPWindow>
	{
		/// Variables
		HINSTANCE	hInst;							///< Handle of current process instance.
		TCHAR		szTitle[MAX_LOADSTRING];		///< The title bar text.
		TCHAR		szWindowClass[MAX_LOADSTRING];	///< The main window class name.
		HWND		hWnd;							///< Handle of window.
		HCURSOR		hCursor;

		WINDOWPLACEMENT windowedPlacement;
		INT			width;	///< The width of window custom area.
		INT			height;	///< The height of window custom area.
		bool		isFullScreen;
		bool		isLastActive;
		bool		isActive;

		CCritSec	resizelock;

	public:
		/// @name Properties
		/// @{
		HWND		GetHWnd();
		HINSTANCE	GetHInstance();
		int			GetWidth();
		int			GetHeight();
		/// @}

	public:
		/// Constructor
		/// @brief SPWindow. Constructor of SPWindow class.
		SPWindow();
	
		/// @brief SPWindow. Constructor of SPWindow class.
		/// @param HINSTANCE hInstance
		/// @param int width
		/// @param int height
		/// @param bool fullScreen
		SPWindow(HINSTANCE hInstance, int width, int height, bool fullScreen);

		/// Destructor
		virtual ~SPWindow(void);

		/// Initialize
		/// @brief Initialize
		/// @param HINSTANCE hInstance
		/// @param int width
		/// @param int height
		/// @param bool fullScreen
		bool Initialize(HINSTANCE hInstance, int width, int height, bool fullScreen);

		/// Register
		/// @brief   RegisterWindowClass
		/// @return   ATOM
		/// @param HINSTANCE hInstance
		ATOM RegisterWindowClass(HINSTANCE hInstance);

		/// Window Process
		/// @brief WindowProcess
		/// @return LRESULT CALLBACK
		/// @param HWND hWnd
		/// @param UINT message
		/// @param WPARAM wParam
		/// @param LPARAM lParam
		static LRESULT CALLBACK WindowProcess(HWND hWnd, 
			UINT message, WPARAM wParam, LPARAM lParam);

		/// @brief Show. Show window.
		void Show();

		/// @brief Focus
		void Focus();

		/// @brief Update. Update window
		void Update();

	public:
		/// @brief Hide. Hide window.
		void Hide();

		/// @brief Unhide. Unhide window.
		void Unhide();

		/// @brief EnterMsgLoop. Enter window message loop.
		int	EnterMsgLoop();

		/// @brief UnregisterWindowClass. Unregister window class.
		bool UnregisterWindowClass();

		/// @brief CalculateWindowRect
		/// @return RECT
		/// @param HWND hWndToAdjust
		/// @param SIZE szDesiredClient
		RECT CalculateWindowRect(HWND hWndToAdjust, SIZE szDesiredClient);

		/// @brief AdjustMainWindow
		/// @return void
		/// @param[in] bool bExclusive
		/// @param[in] int nScreenWidth
		/// @param[in] int nScreenHeight
		void AdjustMainWindow(bool bExclusive,
			int nScreenWidth, int nScreenHeight);

		bool Update(float timeDelta);

		bool IsActive();
		bool IsJustActive();

		HCURSOR GetCursor();
		bool SetCursor(HCURSOR setCur);
	};
}
