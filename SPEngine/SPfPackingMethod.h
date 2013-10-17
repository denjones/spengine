
#pragma once
#include "ISPFilePackingMethod.h"
#include "SPString.h"
#include <vector>

namespace SPEngine
{
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
		struct fileInfo
		{
			SPString fileName;
			int fileSize;
			int fileOffset;
			SPString fileInWhichPack;
		};
		typedef struct fileInfo FileInfo;
		void DirectoryFile(SPString path);
		void InitFiles();
		int sizeOfFile(FILE* file);
		SPString ChangeTheString(SPString str);
		vector<SPString> fileNames;
		vector<SPString> patchNames;
		vector<FileInfo> fileInfos;
		//SPString lastFileName;
		//int lastFileI;
		wchar_t dicBuffer[MAX_PATH];

		int myKey;
		int version;
		//CCritSec fileReadingLock;
	};
}
