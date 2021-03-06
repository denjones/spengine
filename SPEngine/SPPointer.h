//////////////////////////////////////////////////////////////////////////
/// @file		SPPointer.h the header file of template SPPointer class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-8
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <assert.h>
#include "SPNullPointerException.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPPointer template class to represent a smart pointer.
	///
	//////////////////////////////////////////////////////////////////////
	template<typename T>
	class SPPointer
	{
		template<class U> friend class SPPointer;

	public:
		static const SPPointer<T> null;

	protected:
		int*	pointerCount;
		T*		pointer;
		CCritSec* threadLock;
		typedef T *(SPPointer::*bool_type)() const;

		virtual void AddReference()
		{
			threadLock->Lock();

			if (!pointerCount)
			{
				pointerCount = new int(1);
			}
			else
			{
				(*pointerCount)++;
			}

			threadLock->Unlock();
		}

		virtual void RemoveReference()
		{
			bool deleteLock = false;

			threadLock->Lock();

			if (pointerCount)
			{
				(*pointerCount)--;
				if (*pointerCount <= 0)
				{
					delete pointer;
					delete pointerCount;
					deleteLock = true;

					pointer = NULL;
					pointerCount = NULL;
				}
			}
			else
			{
				threadLock->Unlock();
				throw runtime_error("Error removing SPPointer reference.");
			}

			threadLock->Unlock();

			if (deleteLock)
			{
				delete threadLock;
				threadLock = NULL;
			}
		}

	public:
		SPPointer(void) : pointerCount(NULL), pointer(NULL), threadLock(NULL) {}

		SPPointer(T* ptr) : pointer(ptr), pointerCount(NULL), threadLock(NULL)
		{
			if (pointer)
			{
				threadLock = new CCritSec();
				AddReference();
			}
		}

		SPPointer(const SPPointer<T>& ptr) : pointer(NULL), pointerCount(NULL), threadLock(NULL)
		{
			if (ptr.pointer)
			{
				this->pointer = ptr.pointer;
				this->pointerCount = ptr.pointerCount;
				this->threadLock = ptr.threadLock;
				AddReference();
			}
		}

		template <typename U>
		SPPointer(SPPointer<U> const& ptr) : pointer(NULL), pointerCount(NULL), threadLock(NULL)
		{
			if (ptr.pointer)
			{
				this->pointer = static_cast<T*>(ptr.pointer);//reinterpret_cast<T*>(ptr.pointer);
				this->pointerCount = ptr.pointerCount;
				this->threadLock = ptr.threadLock;
				AddReference();
			}
		}

		SPPointer<T>& operator = (T* ptr)
		{
			// If ptr is different from pointer, go on.
			// Else do nothing.
			if (ptr != pointer)
			{
				// If pointer is not NULL
				if (pointer)
				{
					// Remove reference.
					RemoveReference();
					pointerCount = NULL;
					threadLock = NULL;
				}

				pointer = ptr;

				if (pointer)
				{
					threadLock = new CCritSec();
					AddReference();	
				}				
			}

			return *this;
		}

		SPPointer<T>& operator = (SPPointer<T>& ptr)
		{
			if (ptr.pointer != pointer)
			{
				if (ptr.pointer)
				{
					if (pointer)
					{
						RemoveReference();
					}

					pointer = ptr.pointer;
					pointerCount = ptr.pointerCount;
					threadLock = ptr.threadLock;

					AddReference();
				}
				else
				{
					RemoveReference();
					pointer = NULL;
					pointerCount = NULL;
					threadLock = NULL;
				}
			}

			return ptr;
		}

		template <typename U>
		SPPointer<T>& operator = (SPPointer<U> & ptr)
		{
			if (ptr.pointer != pointer)
			{
				if (ptr.pointer)
				{
					if (pointer)
					{
						RemoveReference();
					}

					pointer = reinterpret_cast<T*>(ptr.pointer);
					pointerCount = ptr.pointerCount;
					threadLock = ptr.threadLock;

					AddReference();
				}
				else
				{
					RemoveReference();
					pointer = NULL;
					pointerCount = NULL;
					threadLock = NULL;
				}
			}

			return *this;
		}

		/// @name Reference Operator
		/// @{
		T* operator -> ()
		{
			if (pointer)
			{
				return pointer;
			}

			__debugbreak();
			throw SPNullPointerException(); 
		}

		T** operator & ()
		{
			if (pointer)
			{
				return &pointer;
			}

			__debugbreak();
			throw SPNullPointerException(); 
		}

		T& operator * ()
		{
			if (pointer)
			{
				return *pointer;
			}

			__debugbreak();
			throw SPNullPointerException(); 
		}
		/// @}

		/// @name boolean expression
		/// @{
		bool operator == (SPPointer const& ptr) const
		{
			if (ptr.pointer == pointer)
			{
				return true;
			}

			return false;
		}

		bool operator != (SPPointer const& ptr) const
		{
			if (ptr.pointer != pointer)
			{
				return true;
			}

			return false;
		}

		operator bool() const {
			if (pointer) {
				return true;
			} else {
				return false;
			}
		}

		bool operator!() const {
			if (pointer) {
				return false;
			} else {
				return true;
			}
		}

		operator void*() const {
			return pointer;
		}

		class nested_class;
		operator nested_class*() const {
			return pointer != NULL ? reinterpret_cast<nested_class*>(pointer) : NULL;
		}

		operator bool_type() const {
			return pointer != NULL ? &SPPointer::get : NULL;
		}

		T *get() const {
			return pointer;
		}

		T *GetHandle() const {
			return pointer;
		}
		/// @}

		virtual ~SPPointer(void)
		{
			// Automatically remove reference.
			if (pointer)
			{
				RemoveReference();
			}
		}
	};

	template <typename T>
	SPPointer<T> SPPointer<T>::null = SPPointer<T>((T*)NULL);

	template <typename T>
	class SPPersistent : public SPPointer<T>
	{
		template<class U> friend class SPPersistent;

	public:
		SPPersistent(void) : SPPointer() {
			pointerCount = new int(256);
		}

		SPPersistent(T* ptr) : SPPointer(ptr) {
			pointerCount = new int(256);
		}

		SPPersistent(const SPPointer<T>& ptr) : SPPointer(ptr) {
			pointerCount = new int(256);
		}

		template <typename U>
		SPPersistent(SPPointer<U> const& ptr) : SPPointer(ptr) {
			pointerCount = new int(256);
		}

	protected:
		virtual void AddReference()
		{
			return;
		}

		virtual void RemoveReference()
		{
			return;
		}
	};
}
