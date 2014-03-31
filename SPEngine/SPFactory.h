//////////////////////////////////////////////////////////////////////////
/// @file		SPFactory.h the header file of SPFactory class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <list>
#include "SPPointer.h"

using namespace std;

namespace SPEngine
{	
	//////////////////////////////////////////////////////////////////////
	/// @brief Template class SPFactory
	/// 
	/// A template base factory class to produce game components, and destroy
	/// the components it produced. Each factory can only produce one kind
	/// of component. And a factory can only destroy the products it produced. 
	/// If a product is never destroyed, the factory will destroy it when
	/// the factory destructs.
	/// 
	/// Usage:
	///		A component = SPFactory<A>.Produce();
	///
	//////////////////////////////////////////////////////////////////////
	template <class T>
	class SPFactory
	{
	protected:
		list<SPPointer<T>> products; ///< A vector to contain the products.

	/// @brief private constructor and destructor to prevent the class form
	/// constructing.
	public:
		SPFactory(void){ products = list<SPPointer<T>>();}	
		virtual ~SPFactory(void){ DestroyALL();}

	public:
		/// @brief Produce method. Product products.
		/// @return A pointer of product.
		SPPointer<T> Produce();

		/// @brief Destroy method. Destroy products.
		/// @return bool value. True if successfully destroyed.
		bool Destroy(SPPointer<T> productToDestroy);

		/// @brief DestroyALL method. Destroy all products.
		/// @return bool value. True if successfully destroyed.
		bool DestroyALL();
	};	

	template <class T>
	SPPointer<T> SPFactory<T>::Produce()
	{
		SPPointer<T> newProduct = new T();
		SPComponentManager::GetSingleton()->RegisterComponent(newProduct);
		products.push_back(newProduct);
		return newProduct;
	}

	template <class T>
	bool SPFactory<T>::Destroy(SPPointer<T> productToDestroy)
	{
		list<SPPointer<T>>::iterator iter = products.begin();

		while(iter != products.end())
		{
			if (*iter == productToDestroy)
			{
				*iter = NULL;
				iter = products.erase(iter);
				return true;
			}
			else
			{
				iter++;
			}			
		}

		//foreach(SPPointer<T>, product, list<SPPointer<T>>, products)
		//{
		//	if (product == productToDestroy)
		//	{
		//		product = NULL;
		//		vector<SPPointer<T>>::iterator iterToRemove = iter;
		//		iter++;
		//		products.erase(iterToRemove);
		//		iter--;
		//		return true;
		//	}
		//}

		return false;
	}

	template <class T>
	bool SPFactory<T>::DestroyALL()
	{
		foreach(SPPointer<T>, product, list<SPPointer<T>>, products)
		{
			product = NULL;
		}

		products.clear();

		return true;
	}
}

