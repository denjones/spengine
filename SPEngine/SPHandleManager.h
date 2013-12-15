//////////////////////////////////////////////////////////////////////////
/// @file		SPHandleManager.h the header file of template SPHandleManager class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-8
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <vector>
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPHandleManager to manager handle and the data.
	//////////////////////////////////////////////////////////////////////
	template<typename DATA, typename HANDLE>
	class SPHandleManager
	{
		/// @name Private data type
		/// @{
		typedef std::vector<SPPointer<DATA>> DataVector;
		typedef std::vector<unsigned int>	MagicVector;
		typedef std::vector<unsigned int>	FreeVector;
		/// @}

		DataVector	datas;			///< Data instances.
		MagicVector magicNumbers;	///< List of magic numbers.
		FreeVector	freeSlots;		///< List of free slots.

	public:
		SPHandleManager(void) {};
		virtual ~SPHandleManager(void) {};

		/// @brief Acquire. Get the data corresponding to the handle.
		SPPointer<DATA>& Acquire(HANDLE& handle);
		/// @brief Release. Release the data corresponding to the handle.
		void Release(HANDLE handle);

		/// @brief Dereference. Dereference the handle and get the data.
		SPPointer<DATA>& Dereference(HANDLE handle);
		const SPPointer<DATA> Dereference(HANDLE handle) const;

		/// @brief GetUseHandleCount. Get the number of used handles.
		unsigned int GetUsedHandleCount() const
		{
			return magicNumbers.size() - freeSlots.size();
		}

		/// @brief HasUsedHandles. Check if there is a used handle.
		bool HasUsedHandles() const
		{
			return !!GetUsedHandleCount();
		}
	};

	template<typename DATA, typename HANDLE>
	SPPointer<DATA>& SPHandleManager<DATA, HANDLE>::Acquire(HANDLE& handle)
	{
		unsigned int index;

		// If there is no free slot, then add a new index.
		// Else use the first free slot.
		if (freeSlots.empty())
		{
			index = magicNumbers.size();
			handle.Init(index);
			datas.push_back(SPPointer<DATA>());
			magicNumbers.push_back(handle.GetMagic());
		}
		else
		{
			index = freeSlots.back();
			handle.Init(index);
			freeSlots.pop_back();
			magicNumbers[index] = handle.GetMagic();
		}

		return datas[index];
	}

	template<typename DATA, typename HANDLE>
	void SPHandleManager<DATA, HANDLE>::Release(HANDLE handle)
	{
		// Get the handle index.
		unsigned int index = handle.GetIndex();

		// Ensure the index is valid.
		assert(index < datas.size());
		assert(magicNumbers[index] == handle.GetMagic());

		// Remove the index.
		magicNumbers[index] = 0;
		freeSlots.push_back(index);
	}

	template<typename DATA, typename HANDLE>
	inline SPPointer<DATA>& SPHandleManager<DATA, HANDLE>::Dereference(HANDLE handle)
	{
		if (handle.IsNull())
		{
			return SPPointer<DATA>((DATA*) NULL);
		}

		// Get the handle index.
		unsigned int index = handle.GetIndex();

		// Ensure the index is valid.
		assert(index < datas.size());
		assert(magicNumbers[index] == handle.GetMagic());

		return datas[index];
	}

	template<typename DATA, typename HANDLE>
	inline const SPPointer<DATA> SPHandleManager<DATA, HANDLE>
		::Dereference(HANDLE handle) const
	{
		typedef SPHandleManager<DATA, HANDLE> ThisType;
		return const_cast<ThisType*>(this)->Dereference(handle);
	}
}


