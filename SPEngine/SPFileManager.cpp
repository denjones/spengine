#include "StdAfx.h"
#include "SPFileManager.h"

namespace SPEngine
{
	SPFileManager::SPFileManager(void)
	{
		setlocale(LC_ALL, "en_US.UTF-8");
	}

	SPFileManager::~SPFileManager(void)
	{
	}

	SPFilePtr SPFileManager::OpenFile( SPString path )
	{
		if (files.IsSet(path))
		{
			return files[path];
		}
		
		SPFilePtr file = new SPFile();

		if (!file->Open(path))
		{
			return NULL;
		}

		files.Set(path, file);

		return file;
	}

	bool SPFileManager::CloseFile( SPString path )
	{
		files.Remove(path);

		return true;
	}

}