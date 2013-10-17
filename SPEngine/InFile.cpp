#pragma once
#include <string>
#include <iostream>
#include "InFile.h"

using namespace std;

InFile::InFile(string dirName, string filename)
{
	string pathName = dirName + "\\" + filename;
	file = NULL;
	fileName = filename;
	while((file = fopen(pathName.c_str(), "rb")) == NULL)
	{
		cout << "error file name.\n Input again : ";
		cin >> fileName;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
}

FILE* InFile::GetInFile()
{
	return file;
}

string InFile::GetInFileName()
{
	return fileName;
}

int InFile::GetInFileSize()
{
	int len;
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	return len;
}

void InFile::SetInFileZipSize(int setSize)
{
	zipSize = setSize;
}

int InFile::GetInFileZipSize()
{
	return zipSize;
}

void InFile::SetInFileOffset(int setOffset)
{
	offset = setOffset;
}

int InFile::GetInFileOffset()
{
	return offset;
}