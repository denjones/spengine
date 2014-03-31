//////////////////////////////////////////////////////////////////////////
/// @file		SPGame.h the header file of base SPGame class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-15
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPPointer.h"
#include "SPConfig.h"
#include "SPComponentManager.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
/// @brief SPEngine The namespace which contains all engine elements.
///
///	Every engine class. function, variable, helper is inside this namespace.
//////////////////////////////////////////////////////////////////////////
namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief The base SPGame class to represent a base game.
	///
	///	To produce a new game, you should rewrite some of the virtual
	///		functions below:
	///			- virtual bool Initialize(void);
	///			- virtual bool LoadContent(void);
	///			- virtual bool UnloadContent(void);
	///			- virtual bool Update(float timeDelta);
	///			- virtual bool Draw(float timeDelta);
	///			- virtual void CleanUp(void);
	//////////////////////////////////////////////////////////////////////
	class SPGame
	{
		friend class SPGameManager;

	protected:
		/// @name State Variables
		/// @{
		bool				isReadyToStart;	///< To tell if the game can start. 
		bool				isExiting;		///< To tell if the game is exiting.
		bool				isGameThreadRunning; ///< To tell if the game thread is running.
		HANDLE				hGameThreadExited;
		bool				isRendering;
		bool				isNeedToRender;
		bool				isBackgroundLoading;
		bool				isLockFPS;
		int					lockedFPS;
		bool				isExitButtonPressed;
		CCritSec			backgroundLoadingLock;
		CCritSec			drawWhileLoadingLock;
		CCritSec			exitLock;
		CCritSec			exitBtnLock;
		CCritSec			modificationLock;
		SPPointer<SPConfig>	configToApply;
		SPPointer<SPComponentManager> componentManager;
		/// @}

		float				elapsedLastTimeS;///< The time last Frame
		HINSTANCE			hInstance;

	public:
		/// @name Properties
		/// @{				
		/// @brief    GetWidth
		/// @return   Width
		int	GetWidth();

		/// @brief    GetHeight
		/// @return   Height
		int	GetHeight();

		float GetLastTimeS();

		/// @brief    IsRendering
		/// @return   IsRendering
		bool IsRendering();
		bool IsExiting();

		bool IsGameThreadRunning();
		/// @}

		/// @brief    ResetDevice
		/// @return   bool. True if successful.
		bool ResetDevice(SPConfig config);

	protected:
		SPGame(void);
	public:
		virtual ~SPGame(void);

	public:		
		/// @brief    SPGame. Constructor of SPGame.
		/// @param[in] HINSTANCE. The hInstance of the main process.
		SPGame(HINSTANCE	hInstance);
		
		/// @brief    SPGame. Constructor of SPGame.
		/// @param[in] HINSTANCE. The hInstance of the main process.
		/// @param[in] int. The resolution width.
		/// @param[in] int. The resolution height
		/// @param[in] bool. Whether in fullScreen mode.
		/// @param[in] D3DDEVTYPE. D3D device type.
		SPGame(HINSTANCE	hInstance, 
			int				width,
			int				height,
			bool			isFullScreen,
			D3DDEVTYPE		deviceType);

	protected:		
		/// @brief    BuildEngine
		/// @return   bool		
		/// @param[in] HINSTANCE hInstance
		/// @param[in] int width
		/// @param[in] int height
		/// @param[in] bool isFullScreen
		/// @param[in] D3DDEVTYPE deviceType		
		bool BuildEngine();

	private: 		
		/// @brief    GameThreadProc. The main game thread process. 
		///	Including the main game loop.
		/// @return   DWORD WINAPI		
		/// @param[in] PVOID pParam. A pointer to SPGame object.
		static DWORD WINAPI GameThreadProc(PVOID pParam);
		
		/// @brief    Render. The main rendering method, dealing with the
		/// Update() and Draw() method.
		/// @return   bool. Return true if successfully Rendered.
		/// @param[in] float timeDelta. Elapsed game time in last frame
		/// in second.
		bool Render(float timeDelta);

	protected:
		
		/// @brief    Initialize. Doing the initialization before rendering.
		/// @return   bool. Return true if successfully initialized.		
		virtual bool Initialize();
		virtual bool InitializeComponents();
		
		/// @brief    LoadContent. Load contents before rendering
		/// and after initializing.
		/// @return   bool. Return true if successfully loaded.		
		virtual bool LoadContent();
		virtual bool Load();
	private:
		static DWORD WINAPI BackgroundLoadingThread(PVOID pParam);
		bool IsBackgroundLoading();
		void EndBackgroundLoading();
		void BeginBackgroundLoading();

	public:
		bool IsLockFPS();
		int	GetLockedFPS();
		bool LockFPSAt(int fps);
		bool UnlockFPS();
		bool LockFPS();
		
	protected:
		/// @brief    UnloadContent. Unload contents before exiting.
		/// @return   bool. Return true if successfully Unloaded.
		virtual bool UnloadContent();

		/// @brief    ReloadContent. Reload contents before after unloading.
		/// @return   bool. Return true if successfully Unloaded.
		virtual bool ReloadContent();
		
		/// @brief    Update. Calculation without rendering each frame.
		/// @return   bool. Return true if successfully updated.
		/// @param[in] float timeDelta. Elapsed game time in last frame
		/// in second.		
		virtual bool Update(float timeDelta);
		virtual bool UpdateWhileLoading(float timeDelta);
		
		/// @brief    Draw. Render on screen.
		/// @return   bool. Return true if successfully drawn.
		/// @param[in] float timeDelta. Elapsed game time in last frame
		/// in second.		
		virtual bool Draw(float timeDelta);
		virtual bool DrawWhileLoading(float timeDelta);
		
		/// @brief    CleanUp. Do the cleaning including
		/// deleting and releasing.
		/// @return   void.
		virtual void CleanUp();

	public:		
		/// @brief    Start. Start the game.
		/// @return   bool. Return true if successfully started and exited.
		virtual bool Start();

		/// @brief    Exit. Exit the game.
		/// @return   bool. Return true if successfully exited.
		virtual bool Exit();
		virtual bool ExitGameThread();
		bool		ExitButtonPressed();

		bool ApplyConfig(SPConfig config);
		void ApplyConfigWhenCurrentDrawFinished(SPConfig config);

		bool LockDrawingWhileLoading();
		bool UnlockDrawingWhileLoading();

	public:
		bool Refresh(D3DCOLOR color);
	};

	typedef SPPointer<SPGame> SPGamePtr;
}