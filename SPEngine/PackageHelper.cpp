#include "StdAfx.h"
#include "PackageHelper.h"
#include "zlib.h"

#pragma comment(lib, "zlibwapi.lib")

#pragma warning(disable:4996)

namespace SPEngine
{
	FILE* PackageHelper::packFile = NULL;
	bool PackageHelper::GetFromFile(string fileName, string packName,
		char* &buffer, int& fileSize)
	{
		//原始数据      
		unsigned char pchSrc[] = "xxx...." ;      
		unsigned long nSrcLen = sizeof(pchSrc);      
		//压缩之后的数据      
		unsigned char achComp[1024];      
		unsigned long nCompLen = 1024 ;      
		//解压缩之后的数据      
		unsigned char achUncomp[1024];      
		unsigned long nUncompLen = 1024 ;      
		//压缩      
		compress(achComp,&nCompLen, pchSrc,nSrcLen);      
		//解压缩      
		uncompress(achUncomp,&nUncompLen, achComp,nCompLen);      
		//显示原始数据信息      
		printf("原始数据(%d):/n%s/n/n", nSrcLen,pchSrc);      
		//显示压缩之后的数据      
		printf("压缩数据(%d):/n%s/n/n", nCompLen,achComp);      
		//显示解压缩之后的数据      
		printf("解压数据(%d):/n%s/n/n", nUncompLen,achUncomp);  

		unsigned char* zipBuffer;
		int fileOffset;
		int zipSize;
		unsigned long uncompressSize = -1;
		if((packFile = fopen(packName.c_str(), "rb+")) == NULL)
			return false;
		fileOffset = FindOffset(fileName, fileSize, zipSize);
		if(fileOffset == 0)
			return false;
		buffer = new char[fileSize];
		zipBuffer = new unsigned char[zipSize];
		fseek(packFile, fileOffset, SEEK_SET);
		fread(zipBuffer, sizeof(char), zipSize, packFile);
		uncompress((Bytef*)buffer, &uncompressSize, (Bytef*)zipBuffer, zipSize);
		if(uncompressSize != fileSize)
			MessageBoxA(NULL, NULL, "uncompress error", 0);
		fclose(packFile);
		return true;
	}

	int PackageHelper::FindOffset(string fileName, int& fileSize, int& zipSize)
	{
		const int fileNameLength = 255;
		const int headLength = sizeof(int) * 2;
		const int singleIndexLength = fileNameLength + sizeof(int) * 3;
		char fileNameInPack[255];
		int fileOffset = 0;
		int fileNumInPack;
		fseek(packFile, 0, SEEK_SET);
		fread(&fileNumInPack, sizeof(int), 1, packFile);
		for(int i = 0; i < fileNumInPack;i++)
		{
			fseek(packFile, headLength + i * singleIndexLength, SEEK_SET);
			fread(fileNameInPack, sizeof(char), fileNameLength, packFile);
			if(EqualName(fileNameInPack, fileName))
			{
				fread(&fileOffset, sizeof(int), 1, packFile);
				fread(&fileSize, sizeof(int), 1, packFile);
				fread(&zipSize, sizeof(int), 1, packFile);
				return fileOffset;
			}
		}
		// can't find the file;
		return 0;
	}

	bool PackageHelper::EqualName(char* fileNameInPack, string fileName)
	{
		const int fileNameLength = 255;
		bool flag = true;
		for(int i = 0;fileNameInPack[i] != '\0';i++)
		{
			if(fileNameInPack[i] != fileName[i])
			{
				flag = false;
				break;
			}
		}
		return flag;
	}
};