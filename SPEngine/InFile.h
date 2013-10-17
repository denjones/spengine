#pragma once
#include <string>

using namespace std;

class InFile
{
public:
	InFile(string dirName, string filename);
	FILE* GetInFile();
	string GetInFileName();
	int GetInFileSize();
	void SetInFileZipSize(int setSize);
	int GetInFileZipSize();
	void SetInFileOffset(int setOffset);
	int GetInFileOffset();
private:
	long size;
	long zipSize;
	long offset;
	string fileName;
	FILE* file;
	unsigned char* buffer;
};