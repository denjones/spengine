#include "StdAfx.h"
#include "SPFile.h"
#include "SPFilePacker.h"
#include "SPStringHelper.h"
#include "SPLogHelper.h"

namespace SPEngine
{
	SPFile::SPFile(void):
		hFile(0),
		pData(NULL),
		position(0),
		type(FileNotOpened)
	{
	}


	SPFile::~SPFile(void)
	{
		Close();
	}

	bool SPFile::Open( SPString setPath )
	{
		if (SPFilePacker::GetSingleton()->IsFileInPack(setPath))
		{
			if(!SPFilePacker::GetSingleton()->UnpackFileStream(setPath, pData, length))
			{				
				return false;
			}

			path = setPath;

			type = FileInMemory;
		}
		else
		{
			HANDLE handle = NULL;
			handle = CreateFile(setPath.c_str(),
				GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,	NULL,NULL);

			if (handle == INVALID_HANDLE_VALUE)
			{
				SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to open file: " + setPath);
				return false;
			}

			if (hFile)
			{
				Close();
			}

			hFile = handle;

			type = FileInDisk;
		}

		return true;
	}

	bool SPFile::CreateAndOpen( SPString setPath )
	{
		HANDLE handle = NULL;
		handle = CreateFile(setPath.c_str(),
			GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, NULL,NULL);

		if (handle == INVALID_HANDLE_VALUE)
		{
			SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to create file: " + setPath);
			return false;
		}

		if (hFile)
		{
			Close();
		}

		hFile = handle;
		type = FileInDisk;

		return true;
	}

	bool SPFile::Close()
	{
		if (type == FileInDisk)
		{
			if (hFile)
			{
				CloseHandle(hFile);
				hFile = NULL;
			}
		}
		else if (type == FileInMemory)
		{
			SPFilePacker::GetSingleton()->PackFileStream(path, pData, length);
			if(pData)
			{
				delete pData;
			}
			pData = NULL;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool SPFile::Read( void* pBuffer, DWORD size )
	{
		if (type == FileInDisk)
		{
			DWORD rSize;
			return ReadFile(hFile, pBuffer, size, &rSize, NULL) == TRUE;
		}
		else if (type == FileInMemory)
		{
			if (position > length)
			{
				return false;
			}

			if (position + size > length)
			{
				size = length - position;

			}

			memcpy(pBuffer, pData + position, size);

			position += size;
		}
		else
		{
			return false;
		}
		
		return true;
	}

	bool SPFile::Read( void* pBuffer, DWORD size, LPOVERLAPPED overlapped )
	{
		if (type == FileInDisk)
		{
			DWORD rSize;
			return ReadFile(hFile, pBuffer, size, &rSize, overlapped) == TRUE;
		}
		else if (type == FileInMemory)
		{
			if (position > length)
			{
				return false;
			}

			if (position + size > length)
			{
				size = length - position;
			}

			memcpy(pBuffer, pData + position, size);

			position += size;
		}
		else
		{
			return false;
		}

		return true;
	}

	LONGLONG SPFile::GetFileLength()
	{
		if (type == FileInDisk)
		{
			ULARGE_INTEGER fileLength = {0};
			fileLength.LowPart = GetFileSize(hFile, &fileLength.HighPart);
			return fileLength.QuadPart;
		}
		else if (type == FileInMemory)
		{
			return length;
		}

		return 0;
	}

	bool SPFile::Write( void* pBuffer, DWORD size )
	{
		if (type == FileInDisk)
		{
			WriteFile(hFile, pBuffer, size, (DWORD*)&size, NULL);
		}
		else if (type == FileInMemory)
		{
			memcpy(pData + position, pBuffer, size);
		}
		else
		{
			return false;
		}

		return true;
	}

	bool SPFile::SetPosition( LONGLONG setPostion )
	{
		if (type == FileInDisk)
		{
			LARGE_INTEGER largeInt = {0};
			largeInt.QuadPart = setPostion;

			return HFILE_ERROR != SetFilePointer(hFile, largeInt.LowPart, &largeInt.HighPart, FILE_BEGIN);
		}
		else if (type == FileInMemory)
		{
			if (position < 0)
			{
				position = 0;
				return false;
			}

			if (position > length)
			{
				position = length;
				return false;
			}

			position = setPostion;
			return true;
		}

		return false;		
	}

	LONGLONG SPFile::GetPosition()
	{
		if (type == FileInDisk)
		{
			DWORD pos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
			return pos;
		}
		else if (type == FileInMemory)
		{
			return position;
		}
		else
		{
			return -1;
		}
	}

	bool SPFile::SetOffset( LONGLONG setOffset )
	{
		if (type == FileInDisk)
		{
			LARGE_INTEGER largeInt = {0};
			largeInt.QuadPart = setOffset;

			return HFILE_ERROR != SetFilePointer(hFile, largeInt.LowPart, &largeInt.HighPart, FILE_CURRENT);
		}
		else if (type == FileInMemory)
		{
			if (position + setOffset < 0)
			{
				position = 0;
				return false;
			}

			if (position + setOffset > length)
			{
				position = length;
				return false;
			}

			position += setOffset;
			return true;
		}

		return false;		
	}

}