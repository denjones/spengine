#pragma once
#include <iostream>
#include "OutFile.h"

using namespace std;

void PackFile::SetFileName(string name)
{
	fileName = name;
}

string PackFile::GetFileName()
{
	return fileName;
}

bool PackFile::IsPackExist()
{
	FILE* testFile;
	bool flag = false;
	if((testFile = fopen(fileName.c_str(), "rb+")) != NULL)
	{
		flag = true;
		fclose(testFile);
	}
	return flag;
}