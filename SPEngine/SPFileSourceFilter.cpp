#include "StdAfx.h"
#include "SPFileSourceFilter.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	//* Create a new instance of this class
	CUnknown * WINAPI SPFileSourceFilter::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
	{
		ASSERT(phr);

		//  DLLEntry does the right thing with the return code and
		//  the returned value on failure

		return new SPFileSourceFilter(pUnk, phr);
	}


	BOOL SPFileSourceFilter::ReadTheFile(LPCTSTR lpszFileName)
	{
		//DWORD dwBytesRead;

		// Open the requested file

		wstring wName = lpszFileName;
		SPString name = SPString(wName.begin(), wName.end());

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(name);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[DShow] WARNING: Failed to open video file: " + name);
			return FALSE;
		}

		//HANDLE hFile = CreateFile(lpszFileName,
		//	GENERIC_READ,
		//	FILE_SHARE_READ,
		//	NULL,
		//	OPEN_EXISTING,
		//	0,
		//	NULL);

		//if (hFile == INVALID_HANDLE_VALUE) 
		//{
		//	DbgLog((LOG_TRACE, 2, TEXT("Could not open %s\n"), lpszFileName));
		//	return FALSE;
		//}

		// Determine the file size
		//ULARGE_INTEGER uliSize;
		//uliSize.LowPart = GetFileSize(hFile, &uliSize.HighPart);

		PBYTE pbMem = new BYTE[(unsigned int)file->GetFileLength()];

		if (pbMem == NULL) 
		{
			//CloseHandle(hFile);
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to create buffer!");
			SPFileManager::GetSingleton().CloseFile(name);
			return FALSE;
		}

		// Read the data from the file
		//if (!ReadFile(hFile,
		//	(LPVOID) pbMem,
		//	uliSize.LowPart,
		//	&dwBytesRead,
		//	NULL) ||
		//	(dwBytesRead != uliSize.LowPart))
		//{
		//	DbgLog((LOG_TRACE, 1, TEXT("Could not read file\n")));

		//	delete [] pbMem;
		//	CloseHandle(hFile);
		//	return FALSE;
		//}
		if(!file->Read(pbMem, (DWORD)file->GetFileLength()))
		{
			delete [] pbMem;
			pbMem = NULL;
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to read file!");
			SPFileManager::GetSingleton().CloseFile(name);
			return FALSE;
		}

		// Save a pointer to the data that was read from the file
		m_pbData = pbMem;
		//m_llSize = (LONGLONG)uliSize.QuadPart;
		m_llSize = file->GetFileLength();

		// Close the file
		//CloseHandle(hFile);

		SPFileManager::GetSingleton().CloseFile(name);

		return TRUE;
	}
}

