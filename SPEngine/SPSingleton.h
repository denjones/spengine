//////////////////////////////////////////////////////////////////////////
/// @file		SPSingleton.h the header file of template SPSingleton class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-7
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <assert.h>
#include "SPPointer.h"
#include <wxutil.h>
namespace SPEngine
{
	///////////////////////////////////////////////////////////////////////
	/// @brief A template base class of singleton object.
	///
	/// Usage:
	///		class MyClass : public SPSingleton<MyClass> {}
	///////////////////////////////////////////////////////////////////////
	template<typename T> class SPSingleton
	{
		//static SPPointer<T> singleton; ///< Pointer to hold the singleton.
		//static CCritSec singletonLock;

	public:
		SPSingleton(void)
		{
			//assert(!singleton);
			//int offset = (int)(SPPointer<T>)1 - (int)(SPSingleton<T>*)(SPPointer<T>)1;
			//singleton = (SPPointer<T>)((int)this + offset);
		}

		~SPSingleton(void)
		{
			// Do not release in the destructor of singleton!!
		}

		/// @name Create and Destroy
		/// @{
		static void CreateSingleton()
		{
			singletonLock->Lock();

			if (!singleton)
			{
				singleton = new T();
			}

			singletonLock->Unlock();

			assert(singleton);			
		}

		static void DestroySingleton()
		{			
			if (singleton)
			{
				singleton = NULL;
			}

			assert(!singleton);
		}
		/// @}

		/// @brief GetSingleton. Get the reference of the inner singleton instance.
		/// @return T&
		static SPPersistent<T> GetSingleton()
		{
			// = NULL;
			static SPPersistent<CCritSec> singletonLock = new CCritSec();
			singletonLock->Lock();
			static SPPersistent<T> singleton = new T();
			singletonLock->Unlock();

			assert(singleton);
			return singleton;
		}

		/// @brief GetSingleton. Get the pointer to the inner singleton instance.
		/// the return value could be null.
		/// @return T*
		//static SPPointer<T> GetSingleton()
		//{
		//	return singleton;
		//}
	};

	//template<typename T> 
	//SPPointer<T> SPSingleton<T>::singleton = NULL;
	//template<typename T> 
	//CCritSec SPSingleton<T>::singletonLock;
}




