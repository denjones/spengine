#include "StdAfx.h"
#include "SPFilePacker.h"
#include "SPEmptyPackingMethod.h"
#include "SPfPackingMethod.h"

namespace SPEngine
{
	SPFilePacker::SPFilePacker(void)
	{
		packingMethod = new SPEmptyPackingMethod();
		packingMethod = new SPfPackingMethod();
	}


	SPFilePacker::~SPFilePacker(void)
	{
		packingMethod = NULL;
	}

	bool SPFilePacker::IsFileInPack( SPString path )
	{
		return packingMethod->IsFileInPack(path);
	}

	bool SPFilePacker::PackFileStream( SPString path, char* &pData, LONGLONG &length )
	{
		return packingMethod->PackFile(path, pData, length);
	}

	bool SPFilePacker::UnpackFileStream( SPString path, char* &pData, LONGLONG &length )
	{
		return packingMethod->UnpackFile(path, pData, length);
	}

	LONGLONG SPFilePacker::GetFileLength( SPString path )
	{
		return packingMethod->GetFileLength(path);
	}

}