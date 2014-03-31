//////////////////////////////////////////////////////////////////////////
/// @file		SPGameFactory.h the header file of SPGameFactory class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "SPSingleton.h"
#include "SPPointer.h"
#include "SPGame.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief Template class SPGameFactory
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
	template <typename T>
	class SPGameFactory : public SPSingleton< SPGameFactory <T> >
	{
		/// @brief private constructor and destructor to prevent the class form
		/// constructing.
	public:
		SPGameFactory(void){}
		virtual ~SPGameFactory(void){};

	public:
		void Produce(HINSTANCE hInstance)
		{
			SPGameManager::GetSingleton()->SetGame(new T(hInstance));
		}
	};
}


