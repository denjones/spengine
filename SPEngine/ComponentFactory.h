//////////////////////////////////////////////////////////////////////////
/// @file		ComponentFactory.h the header file of ComponentFactory class.
/// @author		Ken.J from SPRabbit
/// @version	Beta 0.3
/// @date		2012-3-8
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <vector>

using namespace std;

namespace SPEngine
{	
	class SPGame;

	//////////////////////////////////////////////////////////////////////
	/// @brief Template class ComponentFactory
	/// 
	/// A static class (in meaning, not really, because there is no static
	/// class in a C++ language) to produce game components, and destroy
	/// the components it produced. Each factory can only produce one kind
	/// of component. And a factory can only destroy the products it produced. 
	/// If a product is never destroyed, the factory will destroy it when
	/// the factory destructs. Although you can use the factory class to 
	/// produce any class object with default constructor, I suggest you to
	/// use the template to produce game component only.
	/// 
	/// Usage:
	///		SPComponet component = ComponentFactory<SPComponet>.Produce();
	///
	//////////////////////////////////////////////////////////////////////
	template <class T>
	class ComponentFactory
	{
	private:
		static vector<T*> products; ///< A vector to contain the products.

	/// @brief private constructor and destructor to prevent the class form
	/// constructing.
	private:
		ComponentFactory(void){}	
		~ComponentFactory(void){}

	public:
		/// @brief Produce method. Product products.
		/// @return A pointer of product.
		static T* Produce();

		/// @param[in] SPGame game 
		static T* Produce(SPGame* game);

		/// @brief Destroy method. Destroy products.
		/// @return bool value. True if successfully destroyed.
		static bool Destroy(T* productToDestroy);

		/// @brief DestroyALL method. Destroy all products.
		/// @return bool value. True if successfully destroyed.
		static bool DestroyALL();
	};	

	/// Initialize the private static member
	template <class T>
	vector<T*> ComponentFactory<T>::products = vector<T*>();

	template <class T>
	T* ComponentFactory<T>::Produce()
	{
		T* newProduct = new T();
		products.push_back(newProduct);
		return newProduct;
	}

	template <class T>
	T* ComponentFactory<T>::Produce(SPGame* game)
	{
		T* newProduct = new T();
		newProduct->Register(game);
		products.push_back(newProduct);
		return newProduct;
	}

	template <class T>
	bool ComponentFactory<T>::Destroy(T* productToDestroy)
	{
		foreach(T*, product, vector<T*>, products)
		{
			if (product == productToDestroy)
			{
				delete product;
				product = NULL;
				products.erase(iter);
				return true;
			}
		}

		return false;
	}

	template <class T>
	bool ComponentFactory<T>::DestroyALL()
	{
		foreach(T*, product, vector<T*>, products)
		{
			delete product;
			product = NULL;
		}

		products.clear();

		return true;
	}
}

