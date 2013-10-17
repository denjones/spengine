//////////////////////////////////////////////////////////////////////////
/// @file		SPEmptyPackingMethod.h the header file of SPEmptyPackingMethod class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "ISPFilePackingMethod.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPEmptyPackingMethod class to represent a packing method that 
	/// did nothing.
	///
	//////////////////////////////////////////////////////////////////////
	class SPEmptyPackingMethod : public ISPFilePackingMethod
	{
	public:
		virtual bool IsFileInPack(SPString path);
		virtual LONGLONG GetFileLength(SPString path);
		virtual bool UnpackFile(SPString path, char* &outData, LONGLONG &outLength);
		virtual bool PackFile(SPString path, char* &inData, LONGLONG &inLength);
	};
}
