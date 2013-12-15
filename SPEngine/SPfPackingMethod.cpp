#include "StdAfx.h"
#include "SPfPackingMethod.h"
#include <direct.h>
#include <string>
#include "SPLogHelper.h"
#include "SPStringHelper.h"


namespace SPEngine
{
	SPfPackingMethod::SPfPackingMethod()
	{
		fileNames.clear();
		patchNames.clear();
		//lastFileName = L"";
		_wgetcwd(dicBuffer, MAX_PATH);
		DirectoryFile(dicBuffer);
		InitFiles();
	}

	bool SPfPackingMethod::IsFileInPack( SPString path )
	{
		SPString tempPath;
		if(path == L"")
		{
			return false;
		}

		tempPath = path;
		tempPath = ChangeTheString(tempPath);
		//if(_wcsicmp(path.c_str(), lastFileName.c_str()) == 0)
		//{
		//	return true;
		//}

		for(int i = 0;i < fileInfos.size();i++)
		{
			if(_wcsnicmp(tempPath.c_str(), fileInfos[i]->fileName.c_str(), tempPath.length()) == 0)
			{
				//lastFileName = path;
				//lastFileI = i;
				return true;
			}
		}
		return false;
	}

	LONGLONG SPfPackingMethod::GetFileLength( SPString path )
	{
		path = ChangeTheString(path);
		if(path == L"")
		{
			return 0;
		}

		//if(_wcsicmp(path.c_str(), lastFileName.c_str()) == 0)
		//{
		//	return true;
		//}

		for(int i = 0;i < fileInfos.size();i++)
		{
			if(_wcsicmp(path.c_str(), fileInfos[i]->fileName.c_str()) == 0)
			{
				//lastFileName = path;
				//lastFileI = i;
				return fileInfos[i]->fileSize;
			}
		}

		return 0;
	}

	bool SPfPackingMethod::UnpackFile( SPString path, char* &pData, LONGLONG &length )
	{
		path = ChangeTheString(path);
		if(path == L"")
		{
			return false;
		}

		for(int i = 0;i < fileInfos.size();i++)
		{
			if(_wcsicmp(path.c_str(), fileInfos[i]->fileName.c_str()) == 0)
			{
				//lastFileName = path;
				//lastFileI = i;

				//FILE* packFile = NULL;
				//packFile = _wfopen(fileInfos[i].fileInWhichPack.c_str(), L"rb");

				HANDLE file = NULL;
				file = CreateFile(fileInfos[i]->fileInWhichPack.c_str(),
					GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,	NULL,NULL);

				DWORD er = GetLastError();

				//if (!packFile)
				//{
				//	SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to open package file: " + path);
				//	return false;
				//}

				if (!file)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to open package file: " + path);
					return false;
				}

				//fread(&version, sizeof(int),1,packFile);
				//fread(&myKey, sizeof(int), 1, packFile);

				DWORD numOfBytesRead = 0;
				if(ReadFile(file, &version, sizeof(int), &numOfBytesRead, NULL) != TRUE)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to read package version: " + path);
					CloseHandle(file);
					return false;
				}

				if(ReadFile(file, &myKey, sizeof(int), &numOfBytesRead, NULL) != TRUE)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to read package key: " + path);
					CloseHandle(file);
					return false;
				}

				if(version > 0)
				{
					myKey = 0;
				}

				//fseek(packFile, fileInfos[i].fileOffset, SEEK_SET);
				//pData = new char[fileInfos[i].fileSize];
				//fread(pData, sizeof(char), fileInfos[i].fileSize, packFile);

				if(SetFilePointer(file, fileInfos[i]->fileOffset, 0, FILE_BEGIN) == HFILE_ERROR)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to seek package file: " + path);
					CloseHandle(file);
					return false;
				}

				if (pData)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to read package data: " + path);
					CloseHandle(file);
					return false;
				}

				pData = new char[fileInfos[i]->fileSize];

				if(ReadFile(file, pData, fileInfos[i]->fileSize, &numOfBytesRead, NULL) != TRUE)
				{
					SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to read package data: " + path
						+ L" Error Type: " + SPStringHelper::ToWString((int)GetLastError()));
					CloseHandle(file);
					delete pData;
					pData = NULL;
					return false;
				}

				for(int j = 0;j < fileInfos[i]->fileSize;j++)
				{
					pData[j] = pData[j] ^ myKey;
				}

				length = fileInfos[i]->fileSize;

				//fclose(packFile);

				CloseHandle(file);

				SPLogHelper::WriteLog(L"[SPFile] read " + SPStringHelper::ToWString((int)length) + L" bytes from package file: " + path);

				return true;
			}
		}

		return false;
	}

	bool SPfPackingMethod::PackFile( SPString path, char* &inData, LONGLONG &inLength )
	{
		return false;
	}

	void SPfPackingMethod::DirectoryFile(SPString path)
	{
		//CFileFind finder;
		//SPString filePath;
		//SPString findPath = path + L"//*.pak";
		//bool working = finder.FindFile(findPath.c_str());
		//while(working)
		//{
		//	working = finder.FindNextFile();
		//	CString totalName = finder.GetRoot();
		//	if(finder.IsDots())
		//		continue;
		//	if(!finder.IsDirectory())
		//	{
		//		if(finder.GetFileName().Find(_T("patch")) != -1)
		//		{
		//			patchNames.push_back(finder.GetFilePath().GetString());
		//		}
		//		else
		//		{
		//			fileNames.push_back(finder.GetFilePath().GetString());
		//		}
		//	}
		//	if(finder.IsDirectory())
		//		DirectoryFile(finder.GetFilePath().GetString());
		//	}
		//寻找该文件夹下的PAK文件
		HANDLE hFile;
 		SPString cFileName;
		WIN32_FIND_DATA flInfo;
		DWORD errorCode = 0;
		SPString findPath = path + L"\\*.pak";
		hFile = FindFirstFile(findPath.c_str(), &flInfo);
		while(hFile != INVALID_HANDLE_VALUE && errorCode != ERROR_NO_MORE_FILES)
		{
			cFileName = flInfo.cFileName;
			if(cFileName.find(L"patch") != std::wstring::npos)
			{
				patchNames.push_back(path + L"\\" + cFileName);
			}else
			{
				fileNames.push_back(path + L"\\" + cFileName);
			}
			FindNextFile(hFile, &flInfo);
			errorCode = GetLastError();
		}
		FindClose(hFile);
		//寻找文件夹下的文件夹
		HANDLE hFile2;
		WIN32_FIND_DATA flInfo2;
		SPString findPath2 = path + L"\\*.*";
		hFile2 = FindFirstFile(findPath2.c_str(), &flInfo2);
		errorCode = 0;
		while(hFile2 != INVALID_HANDLE_VALUE && errorCode != ERROR_NO_MORE_FILES)
		{
			cFileName = flInfo2.cFileName;
			if(cFileName.find(L".") == std::wstring::npos && flInfo2.nFileSizeHigh == 0)
			{
				DirectoryFile(path + L"\\" + cFileName);
			}
			SetLastError(0);
			FindNextFile(hFile2, &flInfo2);
			errorCode = GetLastError();
		}
		FindClose(hFile2);
	}

	int SPfPackingMethod::SizeOfFile(FILE* file)
	{
		int len;
		fseek(file, 0, SEEK_END);
		len = ftell(file);
		fseek(file, 0, SEEK_SET);
		return len;
	}

	void SPfPackingMethod::InitFiles()
	{
		fileInfos.clear();
		for(int i = patchNames.size() - 1; i >= 0; i--)
		{
			FILE* packFile;
			int sizeOfPack;
			_wfopen_s(&packFile, patchNames[i].c_str(), L"rb");

			if (!packFile)
			{
				SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to open patch file: " + patchNames[i]);
				continue;
			}

			sizeOfPack = SizeOfFile(packFile);
			fseek(packFile, 0, SEEK_SET);
			while(ftell(packFile) < sizeOfPack)
			{
				int dicFileNum;
				int dicSize;
				//=====================添加密码部分  2013-3-11
				fread(&version, sizeof(int),1,packFile);
				fread(&myKey, sizeof(int), 1, packFile);
				if(version > 0)
					fseek(packFile, 0, SEEK_SET);
				//===================================
				fread(&dicFileNum, sizeof(int), 1, packFile);
				fread(&dicSize, sizeof(int), 1, packFile);
				for(int j = 0;j < dicFileNum;j++)
				{
					int nameLen;
					wchar_t* dicFileName;
					int fileSize;
					int fileOffset;
					fread(&nameLen, sizeof(int), 1, packFile);
					dicFileName = new wchar_t[nameLen];
					fread(dicFileName, sizeof(wchar_t), nameLen, packFile);
					fread(&fileSize, sizeof(int), 1, packFile);
					fread(&fileOffset, sizeof(int), 1, packFile);
					FileInfoPtr tempInfo = new FileInfo();
					tempInfo->fileName = dicFileName;
					tempInfo->fileSize = fileSize;
					tempInfo->fileOffset = fileOffset;
					tempInfo->fileInWhichPack = patchNames[i];
					fileInfos.push_back(tempInfo);
					delete [] dicFileName;
					dicFileName = NULL;
				}
				fseek(packFile, dicSize, SEEK_CUR);
			}
			fclose(packFile);
		}

		for(int i = 0;i < fileNames.size();i++)
		{
			FILE* packFile = NULL;
			int sizeOfPack;
			_wfopen_s(&packFile, fileNames[i].c_str(), L"rb");

			if (!packFile)
			{
				SPLogHelper::WriteLog(L"[SPFile] WARNING: Failed to open package file: " + patchNames[i]);
				continue;
			}

			//packFile = fopen("pack1.pak", "rb+");
			sizeOfPack = SizeOfFile(packFile);
			fseek(packFile, 0, SEEK_SET);
			while(ftell(packFile) < sizeOfPack)
			{
				int dicFileNum;
				int dicSize;
				//=====================添加密码部分  2013-3-11
				fread(&version, sizeof(int),1,packFile);
				fread(&myKey, sizeof(int), 1, packFile);
				if(version > 0)
					fseek(packFile, 0, SEEK_SET);
				//===================================
				fread(&dicFileNum, sizeof(int), 1, packFile);
				fread(&dicSize, sizeof(int), 1, packFile);
				for(int j = 0;j < dicFileNum;j++)
				{
					int nameLen;
					int fileSize;
					int fileOffset;
					fread(&nameLen, sizeof(int), 1, packFile);
					wchar_t* dicFileName = new wchar_t[nameLen];
					fread(dicFileName, sizeof(wchar_t), nameLen, packFile);
					fread(&fileSize, sizeof(int), 1, packFile);
					fread(&fileOffset, sizeof(int), 1, packFile);
					FileInfoPtr tempInfo = new FileInfo();
					fileInfos.push_back(tempInfo);
					tempInfo->fileName = dicFileName;
					tempInfo->fileSize = fileSize;
					tempInfo->fileOffset = fileOffset;
					tempInfo->fileInWhichPack = fileNames[i];	
					tempInfo = NULL;
					delete [] dicFileName;
					dicFileName = NULL;
				}
				fseek(packFile, dicSize, SEEK_CUR);
			}
			fclose(packFile);
		}
	}

	SPString SPfPackingMethod::ChangeTheString(SPString str)
	{
		wstring::size_type pos;
		while((pos = str.find(L"/")) != str.npos)
		{
			str = str.replace(pos, 1, L"\\");
		}
		return str;
	}

	SPfPackingMethod::~SPfPackingMethod()
	{
		fileNames.clear();
		patchNames.clear();
		fileInfos.clear();
	}

}
