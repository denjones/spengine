#pragma once
#include <iostream>
#include <string>
#include <io.h>
#include <direct.h>
#include "FileManager.h"
#include "zlib.h"

//#pragma comment(lib, "zlibwapi.lib")

using namespace std;

FileManager::FileManager()
{
	inFiles.clear();
}

bool FileManager::IsFileFit(string name)
{
	if(name[0] == '.')
		return false;
	else 
		return true;
}

bool FileManager::AddDir(string name)
{
	_finddata64i32_t fileInfo;
	int handle;
	string dirName = name;
	name = name + "\\*.*";
	handle = _findfirst(name.c_str(), &fileInfo);
	if(handle == -1)
	{
		cout << "Dir Failed, Input Dir name again :" << endl;
		cin >> name;
		name = name + "\\*.*";
		return false;
	}else
	{
		if(IsFileFit(fileInfo.name))
		{
			InFile infile(dirName, fileInfo.name);
			AddInFile(infile);
		}
		while(_findnext(handle, &fileInfo) == 0)
		{
			if(IsFileFit(fileInfo.name))
			{
				InFile infile(dirName, fileInfo.name);
				AddInFile(infile);
			}
		}
		_findclose(handle);
	}
}

bool FileManager::AddInFile(InFile infile)
{
	inFiles.push_back(infile);
	return true;
}

bool FileManager::SetOutFileName(string name)
{
	outFile.SetFileName(name);
	return true;
}

bool FileManager::Pack()
{
	const int fileNameLength = 255;
	const int fileHeadLength = 2 * sizeof(int);
	FILE* file;
	char buffer[fileNameLength];
	int fileNum = inFiles.size();
	int singleIndexSize = fileNameLength + sizeof(int) * 3;
	int indexSize = fileNum * (fileNameLength + sizeof(int) * 3);
	int offsetNow = 0;
	const int tempSize = 2000000000;
	unsigned long zipFileSize = tempSize;
	if((file = fopen(outFile.GetFileName().c_str(), "wb+")) == NULL)
	{
		return false;
	}
	fwrite(&fileNum, sizeof(int), 1,  file);
	fwrite(&indexSize, sizeof(int), 1, file);

	offsetNow += sizeof(int) * 2 + indexSize;

	//cout << fileNum << " " << indexSize << endl;
	//DisplayPackInfo(fileNum);

	for(int i = 0;i < fileNum;i++)
	{
		int fileSize;

		//将名字复制到buffer
		for(int j = 0;j <= inFiles[i].GetInFileName().size(); j++)
			buffer[j] = inFiles[i].GetInFileName().c_str()[j];

		fwrite(buffer, sizeof(char), fileNameLength, file);
		fileSize = inFiles[i].GetInFileSize();
		fwrite(&offsetNow, sizeof(int), 1, file);
		fwrite(&fileSize, sizeof(int), 1, file);
		fwrite(&zipFileSize, sizeof(int), 1, file);
		cout << buffer << " " << offsetNow << " " << fileSize <<endl;
		offsetNow += fileSize;
	}
	for(int i = 0;i < fileNum;i++)
	{
		int fileSize;
		char* charBuffer = NULL;
		char* zipCharBuffer = NULL;
		//DisplayPackingInfo(inFiles[i].GetInFileName());

		fileSize = inFiles[i].GetInFileSize();
		charBuffer = new char[fileSize];
		zipCharBuffer = new char[fileSize * 2];

		fread(charBuffer, sizeof(char), fileSize, inFiles[i].GetInFile());

		zipFileSize = tempSize;//传出时一定要比传入时小
		if(compress((Bytef*)zipCharBuffer, (uLongf*)&zipFileSize, (Bytef*)charBuffer, (uLong)fileSize) == Z_BUF_ERROR)
			cout << "error!" << endl;

		inFiles[i].SetInFileZipSize(zipFileSize);
		inFiles[i].SetInFileOffset(ftell(file));
		cout << inFiles[i].GetInFileName() << " zipSize : " << zipFileSize << endl;
		//cout << "Detail : " << zipCharBuffer << endl;
		fwrite(zipCharBuffer, sizeof(char), zipFileSize, file);
		//fwrite(charBuffer, sizeof(char), fileSize, file);
		delete[] zipCharBuffer;
		delete[] charBuffer;
	}

	for(int i = 0;i < fileNum;i++)
	{
		int zipFileSize = inFiles[i].GetInFileZipSize();
		int zipOffset = 0;
		zipOffset = inFiles[i].GetInFileOffset();
		fseek(file, fileHeadLength + i * singleIndexSize + fileNameLength, SEEK_SET);
		fwrite(&zipOffset, sizeof(int), 1, file);
		fseek(file, fileHeadLength + i * singleIndexSize + fileNameLength + 2 * sizeof(int), SEEK_SET);
		fwrite(&zipFileSize, sizeof(int), 1, file);
		fseek(file, fileHeadLength + i * singleIndexSize + fileNameLength + 2 * sizeof(int), SEEK_SET);
		fread(&zipFileSize, sizeof(int), 1, file);
		cout << zipFileSize << endl;
	}
	fclose(file);
	//DisplayFinish();
	return true;
}

bool FileManager::Unpack(string outputDirName)
{
	const int fileNameLength = 255;
	const int fileHeadLength = sizeof(int) * 2;
	const int singleIndexLength = fileNameLength + sizeof(int) * 3;
	const int tempSize = 2000000000;
	int fileNum, indexSize, fileOffset, fileSize, zipFileSize;
	FILE* file;
	if((file = fopen(outFile.GetFileName().c_str(), "rb+")) == NULL)
	{
		return false;
	}
	fread(&fileNum, sizeof(int), 1, file);
	fread(&indexSize, sizeof(int), 1, file);
	//fread(&zipFileSize, sizeof(int), 1, file);

	//cout << fileNum << " " << indexSize << endl;
	while(mkdir(outputDirName.c_str()) != 0)
	{
		cout << "Make new direct failed. Input a new direct name :";
		cin >> outputDirName;
	}

	//DisplayPackInfo(fileNum);

	for(int i = 0;i < fileNum;i++)
	{
		char fileName[255];
		char* charBuffer;
		char* zipCharBuffer;
		int zipSize;
		FILE* unpackFile;
		string pathName = outputDirName + "\\";
		fseek(file, fileHeadLength + i * (singleIndexLength), SEEK_SET);
		fread(fileName, sizeof(char), fileNameLength, file);
		fread(&fileOffset, sizeof(int), 1, file);
		fread(&fileSize, sizeof(int), 1, file);
		fread(&zipSize, sizeof(int), 1, file);
		//DisplayUnpackingInfo(fileName, fileSize);
		pathName = pathName + fileName;
		if((unpackFile = fopen(pathName.c_str(), "wb")) == NULL)
			//if((unpackFile = fopen("Test.png", "wb")) == NULL)
		{
			return false;
		}
		fseek(file, fileOffset, SEEK_SET);
		charBuffer = new char[fileSize];
		zipCharBuffer = new char[zipSize];
		//		cout << inFiles[i].GetInFileName() << " " << fileOffset << zipSize << endl;
		fread(zipCharBuffer, sizeof(char), zipSize, file);
		//cout << "Detail : " << zipCharBuffer << endl;
		fileSize = -1;
		if(uncompress((Bytef*)charBuffer, (uLongf*)&fileSize, (Bytef*)zipCharBuffer, zipSize) == Z_DATA_ERROR)
			cout << "data error " << endl;
		fwrite(charBuffer, fileSize, 1, unpackFile);
		fclose(unpackFile);

		cout << fileName << " " << fileOffset << " " << fileSize << endl;
		cout << "ZipSize : " << zipSize << endl;
		delete[] charBuffer;
		delete[] zipCharBuffer;
	}
	//DisplayFinish();
	return true;
}

bool FileManager::LookUpPack()
{
	const int fileNameLength = 255;
	const int fileHeadLength = sizeof(int) * 2;
	const int singleIndexLength = fileNameLength + sizeof(int) * 3;

	int fileNum, indexSize, fileOffset, fileSize, zipFileSize;
	FILE* file;
	if((file = fopen(outFile.GetFileName().c_str(), "rb+")) == NULL)
	{
		return false;
	}
	fread(&fileNum, sizeof(int), 1, file);
	fread(&indexSize, sizeof(int), 1, file);

	//DisplayPackInfo(fileNum);

	for(int i = 0;i < fileNum;i++)
	{
		char singleFileName[fileNameLength];
		fseek(file, fileHeadLength + singleIndexLength * i, SEEK_SET);
		fread(singleFileName, sizeof(char), fileNameLength, file);
		fread(&fileOffset, sizeof(int), 1, file);
		fread(&fileSize, sizeof(int), 1, file);
		fread(&zipFileSize, sizeof(int), 1, file);
		//DisplayPackFileInfo(singleFileName, fileSize, zipFileSize);
	}
	//DisplayFinish();
	return true;
}

//void FileManager::DisplayPackInfo(int fileNum)
//{
//	cout << "Numbers of file : " << fileNum << endl;
//}
//
//void FileManager::DisplayPackingInfo(string fileName)
//{
//	cout << "Packing :" << fileName << endl;
//}
//
//void FileManager::DisplayFinish()
//{
//	cout << "Working finish" << endl;
//}

bool FileManager::IsOutFileExist()
{
	return outFile.IsPackExist();
}

//string FileManager::InputAgain()
//{
//	string tempString;
//	cout << "Pack do not exist. Please input again :";
//	cin >> tempString;
//	return tempString;
//}
//
//void FileManager::DisplayPackFileInfo(string fileName, int fileSize, int zipFileSize)
//{
//	cout << "File : " << fileName << "      Size : " << fileSize << "    ZipSize : " << zipFileSize << endl;
//}
//
//void FileManager::DisplayUnpackingInfo(string fileName, int fileSize)
//{
//	cout << "Unpacking :" << fileName << "       Size :" << fileSize << endl;
//}

void FileManager::ClearInFiles()
{
	inFiles.clear();
}