//////////////////////////////////////////////////////////////////////////
/// @file		SPGameManager.h the header file of SPGameManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SPSingleton.h"
#include "SPPointer.h"
#include "SPGame.h"
#include "SPDevice.h"
#include "SPWindow.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief Template class SPGameManager
	/// 
	/// A singleton to produce game, and destroy the game it produced.
	/// Each factory can only produce one kind of game.
	/// And a factory can only destroy the game it produced. 
	/// If a product is never destroyed, the factory will destroy it when
	/// the factory destructs. 
	/// 
	/// Usage:
	///		SPGame game = SPGameFactory<SPGame>.Produce();
	///
	//////////////////////////////////////////////////////////////////////
	class SPGameManager : public SPSingleton< SPGameManager >
	{
		SPGamePtr currentGame; ///< A pointer to hold the product game.

		/// @brief private constructor and destructor to prevent the class form
		/// constructing.
	public:
		SPGameManager(void) : currentGame(NULL){}
		virtual ~SPGameManager(void){};

	public:
		void SetGame(SPGamePtr game)
		{
			currentGame = game;
		}

		SPGamePtr GetGame()
		{
			return currentGame;
		}

		bool ApplyConfig(SPConfigPtr config)
		{
			return currentGame->ApplyConfig(config);
		}
		
		void Start()
		{
			currentGame->Start();
		}

		void Exit()
		{
			currentGame->Exit();
		}
	};
}


