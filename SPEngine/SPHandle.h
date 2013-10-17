//////////////////////////////////////////////////////////////////////////
/// @file		SPHandle.h the header file of template SPHandle class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-8
//////////////////////////////////////////////////////////////////////////
#pragma once

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPHandle template to index data of game. Used with @see 
	/// SPHandleManager.
	//////////////////////////////////////////////////////////////////////
	template <typename TAG>
	class SPHandle
	{
		/// @brief The union part to represent a handle variable.
		union
		{
			/// @brief The constant defining each part length.
			enum
			{
				/// @name Bit fields.
				/// @{
				MAX_BITS_INDEX = 16, ///< Length of index
				MAX_BITS_MAGIC = 16, ///< Length of magic
				/// @}

				/// @name
				/// @{
				MAX_INDEX = (1 << MAX_BITS_INDEX) - 1,
				MAX_MAGIC = (1 << MAX_BITS_MAGIC) - 1,
				/// @}
			};

			unsigned int handle; ///< The handle.

			/// @brief A struct divides handle into two parts.
			struct  
			{
				unsigned index : MAX_BITS_INDEX; ///< First part to represent index.
				unsigned magic : MAX_BITS_MAGIC; ///< Second part to represent magic num.
			};			
		};		

	public:
		SPHandle(void) : handle(NULL) {}

		/// @brief Initialize index.
		void Init(unsigned int setIndex)
		{			
			assert(IsNull()); ///< Not allowed to reassign.
			assert(setIndex <= MAX_INDEX); ///< Range validation.

			static unsigned int autoMagic = 0; ///< Static counter.

			if (++autoMagic > MAX_MAGIC)
			{
				autoMagic = 1; ///< Use 0 as NULL handle.
			}

			index = setIndex;
			magic = autoMagic;
		}

		/// @name Query.
		/// @{
		unsigned int GetIndex() const
		{
			return index;
		}

		unsigned int GetMagic() const
		{
			return magic;
		}

		unsigned int GetHandle() const
		{
			return handle;
		}

		bool IsNull() const
		{
			return !handle;
		}

		operator unsigned int () const
		{
			return handle;
		}
		/// @}
	};

	/// @name Comparison
	/// @{
	template <typename TAG>
	inline bool operator != (SPHandle<TAG> left, SPHandle<TAG> right)
	{
		return left.GetHandle() != right.GetHandle();
	}

	template <typename TAG>
	inline bool operator == (SPHandle<TAG> left, SPHandle<TAG> right)
	{
		return left.GetHandle() == right.GetHandle();
	}
	/// @}
}
