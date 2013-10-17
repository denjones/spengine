#include "StdAfx.h"
#include "SPKeyboard.h"
#include "SPInputManager.h"
#include "SPWindow.h"
#include "SPDirectInput.h"

#ifdef CEGUI
#include "CEGUI.h"
#endif

namespace SPEngine
{
	SPKeyboard::SPKeyboard(void)
	{
		LoadDevice();
	}

	SPKeyboard::~SPKeyboard(void)
	{
		UnloadDevice();
	}

	bool SPKeyboard::LoadDevice()
	{
		// Reset
		memset(keyState, 0, sizeof(keyState));
		memset(lastKeyState, 0, sizeof(lastKeyState));

		// Create input device1
		if(FAILED(SPDirectInput::GetSingleton().GetDirectInput()->CreateDevice(
			GUID_SysKeyboard, &device, NULL)))
		{
			return false;
		}


		// Set data format
		if(FAILED(device->SetDataFormat(&c_dfDIKeyboard)))
		{
			return false;
		}

		// Set exclusive flags for cooperative level
		DWORD flags;

		// Alway non-exclusive.
		if(false) 
		{
			flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
		}
		else
		{
			flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		}

		// Set cooperative level
		if(FAILED(device->SetCooperativeLevel(
			SPWindow::GetSingleton().GetHWnd(), 
			flags)))
		{
			return false;
		}

		// Acquire device
		device->Acquire();

		return true;
	}
	bool SPKeyboard::UnloadDevice()
	{
		if (device)
		{
			device->Unacquire();
			device->Release();
			device = NULL;
		}

		return true;
	}

	bool SPKeyboard::UpdateDevice()
	{
		if(!device)
		{
			return false;
		}

		// Save old state for input comparing.
		memcpy(lastKeyState, keyState, sizeof(keyState));

		// If error getting device state, reacquire.
		if(FAILED(device->GetDeviceState(sizeof(keyState), (LPVOID)keyState)))
		{
			if(FAILED(device->Acquire()))
			{
				return false;
			}

			if(FAILED(device->GetDeviceState(sizeof(keyState), (LPVOID)keyState)))
			{
				return false;
			}
		}

#ifdef CEGUI
		for (UINT key = DIK_ESCAPE; key <= DIK_DELETE; key++)
		{
			if (ButtonJustDown(key))
			{
				CEGUI::System::getSingleton().injectKeyDown(key);
			}

			if (ButtonJustUp(key))
			{
				CEGUI::System::getSingleton().injectKeyUp(key);
			}
		}
#endif

		return true;
	}

	bool SPKeyboard::ButtonJustUp(unsigned int key)
	{
		if(ButtonUp(key) && (keyState[key] != lastKeyState[key]))
		{
			return true;
		}

		return false;
	}

	bool SPKeyboard::ButtonJustDown(unsigned int key)
	{
		if(ButtonDown(key) && (keyState[key] != lastKeyState[key]))
		{
			return true;
		}

		return false;
	}

	int SPKeyboard::KeyNameToKey( SPString keyName )
	{
		for (int i = 0; i < keyName.length(); i++)
		{
			keyName[i] = toupper(keyName[i]);
		}

		if (keyName == L"ESCAPE")   	   return 0x01;
		if (keyName == L"1")               return 0x02;
		if (keyName == L"2")               return 0x03;
		if (keyName == L"3")               return 0x04;
		if (keyName == L"4")               return 0x05;
		if (keyName == L"5")               return 0x06;
		if (keyName == L"6")               return 0x07;
		if (keyName == L"7")               return 0x08;
		if (keyName == L"8")               return 0x09;
		if (keyName == L"9")               return 0x0A;
		if (keyName == L"0")               return 0x0B;
		if (keyName == L"MINUS")           return 0x0C;
		if (keyName == L"EQUALS")          return 0x0D;
		if (keyName == L"BACK")            return 0x0E;
		if (keyName == L"TAB")             return 0x0F;
		if (keyName == L"Q")               return 0x10;
		if (keyName == L"W")               return 0x11;
		if (keyName == L"E")               return 0x12;
		if (keyName == L"R")               return 0x13;
		if (keyName == L"T")               return 0x14;
		if (keyName == L"Y")               return 0x15;
		if (keyName == L"U")               return 0x16;
		if (keyName == L"I")               return 0x17;
		if (keyName == L"O")               return 0x18;
		if (keyName == L"P")               return 0x19;
		if (keyName == L"LBRACKET")        return 0x1A;
		if (keyName == L"RBRACKET")        return 0x1B;
		if (keyName == L"RETURN")          return 0x1C;
		if (keyName == L"LCONTROL")        return 0x1D;
		if (keyName == L"A")               return 0x1E;
		if (keyName == L"S")               return 0x1F;
		if (keyName == L"D")               return 0x20;
		if (keyName == L"F")               return 0x21;
		if (keyName == L"G")               return 0x22;
		if (keyName == L"H")               return 0x23;
		if (keyName == L"J")               return 0x24;
		if (keyName == L"K")               return 0x25;
		if (keyName == L"L")               return 0x26;
		if (keyName == L"SEMICOLON")       return 0x27;
		if (keyName == L"APOSTROPHE")      return 0x28;
		if (keyName == L"GRAVE")           return 0x29;
		if (keyName == L"LSHIFT")          return 0x2A;
		if (keyName == L"BACKSLASH")       return 0x2B;
		if (keyName == L"Z")               return 0x2C;
		if (keyName == L"X")               return 0x2D;
		if (keyName == L"C")               return 0x2E;
		if (keyName == L"V")               return 0x2F;
		if (keyName == L"B")               return 0x30;
		if (keyName == L"N")               return 0x31;
		if (keyName == L"M")               return 0x32;
		if (keyName == L"COMMA")           return 0x33;
		if (keyName == L"PERIOD")          return 0x34;
		if (keyName == L"SLASH")           return 0x35;
		if (keyName == L"RSHIFT")          return 0x36;
		if (keyName == L"MULTIPLY")        return 0x37;
		if (keyName == L"LMENU")           return 0x38;
		if (keyName == L"SPACE")           return 0x39;
		if (keyName == L"CAPITAL")         return 0x3A;
		if (keyName == L"F1")              return 0x3B;
		if (keyName == L"F2")              return 0x3C;
		if (keyName == L"F3")              return 0x3D;
		if (keyName == L"F4")              return 0x3E;
		if (keyName == L"F5")              return 0x3F;
		if (keyName == L"F6")              return 0x40;
		if (keyName == L"F7")              return 0x41;
		if (keyName == L"F8")              return 0x42;
		if (keyName == L"F9")              return 0x43;
		if (keyName == L"F10")             return 0x44;
		if (keyName == L"NUMLOCK")         return 0x45;
		if (keyName == L"SCROLL")          return 0x46;
		if (keyName == L"NUMPAD7")         return 0x47;
		if (keyName == L"NUMPAD8")         return 0x48;
		if (keyName == L"NUMPAD9")         return 0x49;
		if (keyName == L"SUBTRACT")        return 0x4A;
		if (keyName == L"NUMPAD4")         return 0x4B;
		if (keyName == L"NUMPAD5")         return 0x4C;
		if (keyName == L"NUMPAD6")         return 0x4D;
		if (keyName == L"ADD")			    return 0x4E;
		if (keyName == L"NUMPAD1")         return 0x4F;
		if (keyName == L"NUMPAD2")         return 0x50;
		if (keyName == L"NUMPAD3")         return 0x51;
		if (keyName == L"NUMPAD0")         return 0x52;
		if (keyName == L"DECIMAL")         return 0x53;
		if (keyName == L"OEM_102")         return 0x56;
		if (keyName == L"F11")             return 0x57;
		if (keyName == L"F12")             return 0x58;
		if (keyName == L"F13")             return 0x64;
		if (keyName == L"F14")             return 0x65;
		if (keyName == L"F15")             return 0x66;
		if (keyName == L"KANA")            return 0x70;
		if (keyName == L"ABNT_C1")         return 0x73;
		if (keyName == L"CONVERT")         return 0x79;
		if (keyName == L"NOCONVERT")       return 0x7B;
		if (keyName == L"YEN")             return 0x7D;
		if (keyName == L"ABNT_C2")         return 0x7E;
		if (keyName == L"NUMPADEQUALS")    return 0x8D;
		if (keyName == L"PREVTRACK")       return 0x90;
		if (keyName == L"AT")              return 0x91;
		if (keyName == L"COLON")           return 0x92;
		if (keyName == L"UNDERLINE")       return 0x93;
		if (keyName == L"KANJI")           return 0x94;
		if (keyName == L"STOP")            return 0x95;
		if (keyName == L"AX")              return 0x96;
		if (keyName == L"UNLABELED")       return 0x97;
		if (keyName == L"NEXTTRACK")       return 0x99;
		if (keyName == L"NUMPADENTER")     return 0x9C;
		if (keyName == L"RCONTROL")        return 0x9D;
		if (keyName == L"MUTE")            return 0xA0;
		if (keyName == L"CALCULATOR")      return 0xA1;
		if (keyName == L"PLAYPAUSE")       return 0xA2;
		if (keyName == L"MEDIASTOP")       return 0xA4;
		if (keyName == L"VOLUMEDOWN")      return 0xAE;
		if (keyName == L"VOLUMEUP")        return 0xB0;
		if (keyName == L"WEBHOME")         return 0xB2;
		if (keyName == L"NUMPADCOMMA")     return 0xB3;
		if (keyName == L"DIVIDE")          return 0xB5;
		if (keyName == L"SYSRQ")           return 0xB7;
		if (keyName == L"RMENU")           return 0xB8;
		if (keyName == L"PAUSE")           return 0xC5;
		if (keyName == L"HOME")            return 0xC7;
		if (keyName == L"UP")              return 0xC8;
		if (keyName == L"PRIOR")           return 0xC9;
		if (keyName == L"LEFT")            return 0xCB;
		if (keyName == L"RIGHT")           return 0xCD;
		if (keyName == L"END")             return 0xCF;
		if (keyName == L"DOWN")            return 0xD0;
		if (keyName == L"NEXT")            return 0xD1;
		if (keyName == L"INSERT")          return 0xD2;
		if (keyName == L"DELETE")          return 0xD3;
		if (keyName == L"LWIN")            return 0xDB;
		if (keyName == L"RWIN")            return 0xDC;
		if (keyName == L"APPS")            return 0xDD;
		if (keyName == L"POWER")           return 0xDE;
		if (keyName == L"SLEEP")           return 0xDF;
		if (keyName == L"WAKE")            return 0xE3;
		if (keyName == L"WEBSEARCH")       return 0xE5;
		if (keyName == L"WEBFAVORITES")    return 0xE6;
		if (keyName == L"WEBREFRESH")      return 0xE7;
		if (keyName == L"WEBSTOP")         return 0xE8;
		if (keyName == L"WEBFORWARD")      return 0xE9;
		if (keyName == L"WEBBACK")         return 0xEA;
		if (keyName == L"MYCOMPUTER")      return 0xEB;
		if (keyName == L"MAIL")            return 0xEC;
		if (keyName == L"MEDIASELECT")     return 0xED;

		/*
		 *  Alternate names for keys, to facilitate transition from DOS.
		 */
		if (keyName == L"BACKSPACE")       return DIK_BACK      ;       /* backspace */
		if (keyName == L"NUMPADSTAR")      return DIK_MULTIPLY  ;      /* * on numeric keypad */
		if (keyName == L"LALT")            return DIK_LMENU     ;      /* left Alt */
		if (keyName == L"CAPSLOCK")        return DIK_CAPITAL   ;      /* CapsLock */
		if (keyName == L"NUMPADMINUS")     return DIK_SUBTRACT  ;      /* - on numeric keypad */
		if (keyName == L"NUMPADPLUS")      return DIK_ADD       ;      /* + on numeric keypad */
		if (keyName == L"NUMPADPERIOD")    return DIK_DECIMAL   ;      /* . on numeric keypad */
		if (keyName == L"NUMPADSLASH")     return DIK_DIVIDE    ;      /* / on numeric keypad */
		if (keyName == L"RALT")            return DIK_RMENU     ;      /* right Alt */
		if (keyName == L"UPARROW")         return DIK_UP        ;      /* UpArrow on arrow keypad */
		if (keyName == L"PGUP")            return DIK_PRIOR     ;      /* PgUp on arrow keypad */
		if (keyName == L"LEFTARROW")       return DIK_LEFT      ;      /* LeftArrow on arrow keypad */
		if (keyName == L"RIGHTARROW")      return DIK_RIGHT     ;      /* RightArrow on arrow keypad */
		if (keyName == L"DOWNARROW")       return DIK_DOWN      ;      /* DownArrow on arrow keypad */
		if (keyName == L"PGDN")            return DIK_NEXT      ;      /* PgDn on arrow keypad */

		/*
		 *  Alternate names for keys originally not used on US keyboards.
		 */
		if (keyName == L"CIRCUMFLEX")      return DIK_PREVTRACK;      /* Japanese keyboard */
		return 0;
	}

	bool SPEngine::SPKeyboard::ButtonUp( unsigned int key )
	{
		// If the key in the variable is not pressed then return false.
		return (!(keyState[key] & 0x80) && keyState[key] != lastKeyState[key]);
	}

	bool SPEngine::SPKeyboard::ButtonDown( unsigned int key )
	{
		// If the key in the variable is not pressed then return false.
		return (keyState[key] & 0x80) > 0;
	}
}

