//////////////////////////////////////////////////////////////////////////
/// @file		SPFilePacker.h the header file of SPFilePacker class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "ISPFilePackingMethod.h"
#include "SPSingleton.h"
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFilePacker class to present packing method to pack and 
	/// unpack file file in virtual file system.
	//////////////////////////////////////////////////////////////////////
	class SPFilePacker : public SPSingleton<SPFilePacker>
	{
		SPPackingMethodPtr packingMethod;

	public:
		bool SetPackingMethod(SPPackingMethodPtr setMethod)
		{
			packingMethod = setMethod;
		}

	public:
		SPFilePacker(void);
		virtual ~SPFilePacker(void);
		
		bool IsFileInPack(SPString path);
		LONGLONG GetFileLength(SPString path);
		bool UnpackFileStream(SPString path, char* &pData, LONGLONG &length);
		bool PackFileStream(SPString path, char* &pData, LONGLONG &length);
	};
}
