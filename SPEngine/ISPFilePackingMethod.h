//////////////////////////////////////////////////////////////////////////
/// @file		ISPFilePackingMethod.h the header file of ISPFilePackingMethod interface.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPPointer.h"
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ISPFilePackingMethod class to represent a packing method.
	///
	//////////////////////////////////////////////////////////////////////
	class ISPFilePackingMethod
	{
	public:
		virtual ~ISPFilePackingMethod(){};
		virtual bool IsFileInPack(SPString path) = 0;
		virtual LONGLONG GetFileLength(SPString path) = 0;
		virtual bool UnpackFile(SPString path, char* &outData, LONGLONG &outLength) = 0;
		virtual bool PackFile(SPString path, char* &inData, LONGLONG &inLength) = 0;
	};

	typedef SPPointer<ISPFilePackingMethod> SPPackingMethodPtr;
}
