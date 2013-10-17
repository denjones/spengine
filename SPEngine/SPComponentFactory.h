//////////////////////////////////////////////////////////////////////////
/// @file		SPComponentFactory.h the header file of SPComponentFactory class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <list>
#include "SPPointer.h"
#include "SPFactory.h"
#include "SPSingleton.h"
#include "SPString.h"

using namespace std;

namespace SPEngine
{	
	class SPGame;

	//////////////////////////////////////////////////////////////////////
	/// @brief Template class SPComponentFactory
	/// 
	/// A singleton template class to produce game components, and destroy
	/// the components it produced. Each factory can only produce one kind
	/// of component. And a factory can only destroy the products it produced. 
	/// If a product is never destroyed, the factory will destroy it when
	/// the factory destructs. It is invalid to produce non-component.
	/// 
	/// Usage:
	///		SPComponet component = SPComponentFactory<SPComponet>.
	///			Produce(ComponentManager::GetSingletonPtr());
	///
	//////////////////////////////////////////////////////////////////////
	template <class T>
	class SPComponentFactory : 
		public SPFactory<T>, 
		public SPSingleton<SPComponentFactory<T>>
	{
	public:
		SPComponentFactory(void) : SPFactory() {}
		virtual ~SPComponentFactory(void){}

		/// @param[in] ComponentManager& manager 
		SPPointer<T> Produce(SPString name, SPComponentManager& manager)
		{
			SPPointer<T> newProduct = new T();
			manager.RegisterComponent(name, newProduct);
			products.push_back(newProduct);
			return newProduct;
		}
	};	
}

