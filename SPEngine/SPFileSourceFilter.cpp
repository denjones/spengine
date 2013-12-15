#include "StdAfx.h"
#include "SPFileSourceFilter.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	// Create a new instance of this class
	CUnknown * WINAPI SPFileSourceFilter::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
	{
		ASSERT(phr);

		//  DLLEntry does the right thing with the return code and
		//  the returned value on failure

		return new SPFileSourceFilter(pUnk, phr);
	}


	BOOL SPFileSourceFilter::ReadTheFile(LPCTSTR lpszFileName)
	{
		// Open the requested file

		wstring wName = lpszFileName;
		SPString name = SPString(wName.begin(), wName.end());

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(name);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[DShow] WARNING: Failed to open video file: " + name);
			return FALSE;
		}

		PBYTE pbMem = new BYTE[(unsigned int)file->GetFileLength()];

		if (pbMem == NULL) 
		{
			//CloseHandle(hFile);
			SPLogHelper::WriteLog("[DShow] WARNING: Failed to create buffer!");
			SPFileManager::GetSingleton().CloseFile(name);
			return FALSE;
		}

		// Read the data from the file

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
		m_llSize = file->GetFileLength();

		// Close the file

		SPFileManager::GetSingleton().CloseFile(name);

		return TRUE;
	}
}

