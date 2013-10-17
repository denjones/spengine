// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <string>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Windows Header Files:

#include <intsafe.h>
#include <objbase.h>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <comdef.h>
#include <commdlg.h>
#include <intrin.h>

// DirectShow Header Files
#include <dshow.h>
#include <streams.h>

#include <d3d9.h>
#include <dinput.h>
#include <d3dx9math.h>
#include <vmr9.h>
#include <evr.h>


// TODO: reference additional headers your program requires here
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "strmbasd.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xinput.lib")
//#pragma comment(lib, "KScript.lib")
//#pragma comment(lib, "SPEngine.lib")