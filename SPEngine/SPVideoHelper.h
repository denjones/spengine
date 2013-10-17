//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoHelper.h the header file of SPVideoHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPVideoHelper static class to provide converting function
	/// among video texture formats.
	///
	//////////////////////////////////////////////////////////////////////
	class SPVideoHelper
	{
	private:
		SPVideoHelper(void);
		~SPVideoHelper(void);

	public:
		static void Convert_UYV2_ARGB(
			unsigned char* source,
			int width, int height,
			int source_scan_size,
			unsigned char* dest, 
			int dest_scan_size,
			bool flipVertical);
	};

}


