
#pragma once
#include "ISPFilePackingMethod.h"
#include "SPString.h"
#include <vector>

namespace SPEngine
{
	class FileInfo
	{
	public:
		SPString fileName;
		int fileSize;
		int fileOffset;
		SPString fileInWhichPack;
		FileInfo()
		{
			fileName = L"";
			fileSize = 0;
			fileOffset = 0;
			fileInWhichPack = L"";
		};

		virtual ~FileInfo()
		{
			;
		};
	};

	typedef SPPointer<FileInfo> FileInfoPtr;

	class SPfPackingMethod : public ISPFilePackingMethod
	{
	public:
		SPfPackingMethod();
		virtual ~SPfPackingMethod();
		virtual bool IsFileInPack(SPString path);
		virtual LONGLONG GetFileLength(SPString path);
		virtual bool UnpackFile(SPString path, char* &outData, LONGLONG &outLength);
		virtual bool PackFile(SPString path, char* &inData, LONGLONG &inLength);
		
	protected:
		
		void DirectoryFile(SPString path);
		void InitFiles();
		int SizeOfFile(FILE* file);
		SPString ChangeTheString(SPString str);
		vector<SPString> fileNames;
		vector<SPString> patchNames;
		vector<FileInfoPtr> fileInfos;
		//SPString lastFileName;
		//int lastFileI;
		wchar_t dicBuffer[MAX_PATH];

		int myKey;
		int version;
		//CCritSec fileReadingLock;
	};
}
