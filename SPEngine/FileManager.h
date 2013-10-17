#pragma once
#include <vector>
#include "OutFile.h"
#include "InFile.h"

#ifndef ZLIB_WINAPI
#define ZLIB_WINAPI
#endif

class FileManager
{
public:
	FileManager();
	bool AddInFile(InFile infile);
	bool AddDir(string name);
	bool SetOutFileName(string name);
	bool IsOutFileExist();
	bool Pack();
	bool Unpack(string outputDirName);
	string InputAgain();
	bool LookUpPack();
	void ClearInFiles();
private:
	PackFile outFile;
	vector<InFile> inFiles;

	bool IsFileFit(string name);
	//void DisplayPackInfo(int fileNum);
	//void DisplayPackingInfo(string fileName);
	//void DisplayPackFileInfo(string fileName, int fileSize, int zipFileSize);
	//void DisplayUnpackingInfo(string fileName, int fileSize);
	//void DisplayFinish();
};