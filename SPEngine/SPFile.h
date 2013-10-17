//////////////////////////////////////////////////////////////////////////
/// @file		SPFile.h the header file of SPFile class.
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
	
	enum SPFileType
	{
		FileInDisk,
		FileInMemory,
		FileNotOpened,
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief SPFile class to represent a file in virtual file system.
	//////////////////////////////////////////////////////////////////////
	class SPFile
	{
	protected:
		HANDLE		hFile;
		LONGLONG	position;
		char*		pData;
		LONGLONG	length;
		SPFileType	type;
		SPString		path;

	public:
		SPFile(void);
		virtual ~SPFile(void);

		bool Open(SPString path);
		bool CreateAndOpen(SPString path);
		bool Close();

		HANDLE GetFileHandle(){ return hFile; }		

		bool Read(void* pBuffer, DWORD size);
		bool Read(void* pBuffer, DWORD size, LPOVERLAPPED overlapped);
		bool Write(void* pBuffer, DWORD size);

		bool SetPosition(LONGLONG setPostion);
		bool SetOffset(LONGLONG setOffset);
		LONGLONG GetPosition();
		LONGLONG GetFileLength();
	};

	typedef SPPointer<SPFile> SPFilePtr;
}
