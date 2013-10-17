#pragma once
#include <string>

#ifndef ZLIB_WINAPI
#define ZLIB_WINAPI
#endif

using namespace std;

namespace SPEngine
{
	class PackageHelper
	{
	public:
		static bool GetFromFile(string fileName, string packName, 
			char* &buffer, int& fileSize);
	private:
		static FILE* packFile;
		static int FindOffset(string fileName, int& fileSize, int& zipSize);
		static bool EqualName(char* fileNameInPack, string fileName);
	};
};