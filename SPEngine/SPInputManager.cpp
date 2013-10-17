//////////////////////////////////////////////////////////////////////////
/// @file		SPInputManager.cpp the implement file of SPInputManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPInputManager.h"
#include "SPWindow.h"
#include "SPFileManager.h"

namespace SPEngine
{
	SPInputManager::SPInputManager(void)
	{
	}

	SPInputManager::~SPInputManager(void)
	{
		Unload();
	}

	bool SPInputManager::Initialize()
	{
		// Everything took place in the constructor.
		// Force keyboard and mouse before considering the
		// system initialized.
		keyboard = new SPKeyboard();
		mouse = new SPMouse();
		joystick = new SPJoystick();

		numXController = 1;

		for (int num = 0; num < 4;num++ )
		{
			xControllers.push_back(new SPXController(num));
		}

		return (keyboard && mouse);
	}

	bool SPInputManager::Load()
	{
		if (!keyboard)
		{
			keyboard = new SPKeyboard();
		}

		if (!mouse)
		{
			mouse = new SPMouse();
		}

		if (!joystick)
		{
			joystick = new SPJoystick();
		}

		for(int num = 0; num < 4; num++)
		{
			if (!xControllers[num])
			{
				xControllers[num] = new SPXController(num);
			}		
		}

		return true;
	}

	bool SPInputManager::Unload()
	{
		for (int num = 0; num < 4;num++ )
		{
			if (xControllers[num])
			{
				xControllers[num] = NULL;
			}
		}

		return true;
	}

	bool SPInputManager::Update( float timeElapsed )
	{
		// Get the device state.
		if(mouse)
		{
			mouse->UpdateDevice();
		}

		if(keyboard)
		{
			keyboard->UpdateDevice();
		}

		if(joystick)
		{
			joystick->UpdateDevice();
		}

		for (int num = 0; num < numXController; num++ )
		{
			if (xControllers[num])
			{
				xControllers[num]->UpdateDevice();
			}
			
		}

		return true;
	}

	bool SPInputManager::Draw(float timeElapsed)
	{
		return true;
	}	

	bool SPInputManager::SetMaxXController( int max )
	{
		max = min(max, 4);

		numXController = max;

		return true;
	}

	bool SPInputManager::SetCursor( SPString path )
	{
		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			return false;
		}

		LONGLONG length = file->GetFileLength();
		char* pData = new char[length];
		file->Read(pData, length);

		wchar_t tname[10];		
		_wtmpnam_s(tname, 10);

		SPString name = SPString(tname);// + path.substr(path.find_last_of(L".") + 1);

		HANDLE newFile = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (newFile == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD numOfByte;
		if(FALSE == WriteFile(newFile, pData, length, &numOfByte, NULL))
		{ 
			delete [] pData;
			pData = NULL;
			SPFileManager::GetSingleton().CloseFile(path);
			CloseHandle(newFile);
			DeleteFile(name.c_str());
			return false;
		}

		CloseHandle(newFile);
		HCURSOR cursor = LoadCursorFromFile(name.c_str());
		if (!cursor)
		{
			DWORD err = GetLastError();
			delete [] pData;
			pData = NULL;
			SPFileManager::GetSingleton().CloseFile(path);
			CloseHandle(newFile);
			DeleteFile(name.c_str());
			return false;
		}

		SPWindow::GetSingleton().SetCursor(cursor);

		DeleteFile(name.c_str());

		delete [] pData;
		pData = NULL;
		SPFileManager::GetSingleton().CloseFile(path);
		//CloseHandle(newFile);

		return true;
	}
}

