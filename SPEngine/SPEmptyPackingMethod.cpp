#include "StdAfx.h"
#include "SPEmptyPackingMethod.h"

namespace SPEngine
{
	bool SPEmptyPackingMethod::IsFileInPack( SPString path )
	{
		return false;
	}

	LONGLONG SPEmptyPackingMethod::GetFileLength( SPString path )
	{
		return 0;
	}

	bool SPEmptyPackingMethod::UnpackFile( SPString path, char* &outData, LONGLONG &outLength )
	{
		return false;
	}

	bool SPEmptyPackingMethod::PackFile( SPString path, char* &inData, LONGLONG &inLength )
	{
		return false;
	}

}
