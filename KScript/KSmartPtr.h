#pragma once

#include <assert.h>

//////////////////////////////////////////////////////////////////////
/// @brief KSmartPtr template class to represent a smart pointer.
///
//////////////////////////////////////////////////////////////////////
template<typename T>
class KSmartPtr
{
	template<class U> friend class KSmartPtr;

public:
	static const KSmartPtr<T> null;

protected:
	int*	pointerCount;
	T*		pointer;
	typedef T *(KSmartPtr::*bool_type)() const;

	void AddReference()
	{
		if (!pointerCount)
		{
			pointerCount = new int(1);
		}
		else
		{
			(*pointerCount)++;
		}
	}

	void RemoveReference()
	{
		if (pointerCount)
		{
			(*pointerCount)--;
			if (*pointerCount == 0)
			{
				delete pointer;
				delete pointerCount;

				pointer = NULL;
				pointerCount = NULL;
			}
		}
		else
		{
			throw runtime_error("Error removing KSmartPtr reference.");
		}
	}

public:
	KSmartPtr(void) : pointerCount(NULL), pointer(NULL) {}

	KSmartPtr(T* ptr) : pointer(ptr), pointerCount(NULL)
	{
		if (pointer)
		{
			AddReference();
		}
	}

	KSmartPtr(const KSmartPtr<T>& ptr) : pointer(NULL), pointerCount(NULL) 
	{
		if (ptr.pointer)
		{
			this->pointer = ptr.pointer;
			this->pointerCount = ptr.pointerCount;
			AddReference();
		}
	}

	template <typename U>
	KSmartPtr(KSmartPtr<U> const& ptr) : pointer(NULL), pointerCount(NULL)
	{
		if (ptr.pointer)
		{
			this->pointer = reinterpret_cast<T*>(ptr.pointer);
			this->pointerCount = ptr.pointerCount;
			AddReference();
		}
	}

	KSmartPtr<T>& operator = (T* ptr)
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
			}

			pointer = ptr;

			if (pointer)
			{
				AddReference();	
			}				
		}

		return *this;
	}

	KSmartPtr<T>& operator = (KSmartPtr<T>& ptr)
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

				AddReference();
			}
			else
			{
				RemoveReference();
				pointer = NULL;
				pointerCount = NULL;
			}
		}

		return ptr;
	}

	template <typename U>
	KSmartPtr<T>& operator = (KSmartPtr<U> & ptr)
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

				AddReference();
			}
			else
			{
				RemoveReference();
				pointer = NULL;
				pointerCount = NULL;
			}
		}

		return *this;
	}

	/// @name Reference Operator
	/// @{
	T* operator -> ()
	{
		assert(pointer);

		if (pointer)
		{
			return pointer;
		}

		throw runtime_error("Access through NULL pointer"); 
	}

	//T** operator & ()
	//{
	//	if (pointer)
	//	{
	//		return &pointer;
	//	}
	//}

	T& operator * ()
	{
		assert(pointer);

		if (pointer)
		{
			return *pointer;
		}

		throw runtime_error("Dereference of NULL pointer"); 
	}
	/// @}

	/// @name boolean expression
	/// @{
	bool operator == (KSmartPtr const& ptr) const
	{
		if (ptr.pointer == pointer)
		{
			return true;
		}

		return false;
	}

	bool operator != (KSmartPtr const& ptr) const
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
		return pointer != NULL ? &KSmartPtr::get : NULL;
	}

	T *get() const {
		return pointer;
	}
	/// @}

	~KSmartPtr(void)
	{
		// Automatically remove reference.
		if (pointer)
		{
			RemoveReference();
		}
	}
};

template <typename T>
KSmartPtr<T> KSmartPtr<T>::null = KSmartPtr<T>((T*)NULL);