//////////////////////////////////////////////////////////////////////////
/// @file		SPBaseScreen.h the header file of SPBaseScreen class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-30
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTransition.h"
#include "SPPointer.h"
#include "ISPLoadable.h"
#include "ISPDrawable.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPBaseScreen 
	/// Base game screen class. Its method would be called by the screen
	/// manager registered. To make use of the base screen, override one
	/// or some of these method:
	///		- virtual bool Initialize(void);
	///		- virtual bool Load(void);
	///		- virtual bool Unload(void);
	///		- virtual bool Reload(void);
	///		- virtual bool HandleInput(float timeDelta);
	///		- virtual bool Update(float timeDelta);
	///		- virtual bool Draw(float timeDelta);
	///
	///	And then use the AddScreen method of SPScreenManager:
	///		- SPScreenManager::GetSingleton()->AddScreen("[screen_name]", new MyScreen())
	///
	//////////////////////////////////////////////////////////////////////
	class SPBaseScreen : 
		public SPTransition,
		public ISPLoadable,
		public ISPDrawable
	{
	protected:
		bool isPopup;
		bool isExiting;
		bool isInputValid;

	public:
		/// @name Properties.
		/// @{
		bool IsPopup();
		bool IsExiting();
		bool IsInputValid();
		/// @}

	public:
		SPBaseScreen(void);
		virtual ~SPBaseScreen(void);

	public:
		/// @name Manage methods.
		/// @{
		void ExitScreen();
		void UpdateScreen(
			float timeDelta, bool inputValid, bool visible);
		/// @}

	public:
		/// @name Main Methods.
		/// @{
		virtual void Initialize();
		virtual void HandleInput(float timeDelta);
		virtual void Update(float timeDelta);
		virtual void Draw(float timeDelta);
		virtual void Unload();
		virtual void Load();
		virtual void Reload();
		/// @}
	};

	typedef SPPointer<SPBaseScreen> SPBaseScreenPtr;
}
