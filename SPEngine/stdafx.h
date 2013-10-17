// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//// Windows Header Files:
//#include <intsafe.h>
//#include <objbase.h>
//#include <windows.h>
//
//// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <comdef.h>
//#include <commdlg.h>
//
//
//// TODO: reference additional headers your program requires here
//#include <DShow.h>
//#include <streams.h>
//#include <d3d9.h>
//#include <dinput.h>
//#include <d3dx9math.h>
//#include <CGuid.h>
//#include <XAudio2.h>
//#include <vmr9.h>
#define DIRECTINPUT_VERSION 0x0800

// Windows Header Files:
#include <string>
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
#include <Evr.h>
#include <assert.h>

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "strmbasd.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xinput.lib")

//#ifdef DEBUG
//#pragma comment(lib, "libvorbis_static_d.lib")
//#pragma comment(lib, "libvorbisfile_static_d.lib")
//#else
//#pragma comment(lib, "libvorbis_static.lib")
//#pragma comment(lib, "libvorbisfile_static.lib")
//#endif

//#pragma comment(lib, "KScript.lib")

#ifdef CEGUI
#ifdef DEBUG
#pragma comment(lib, "CEGUIBase_d.lib")
#pragma comment(lib, "CEGUIDirect3D9Renderer_d.lib")
#else
#pragma comment(lib, "CEGUIBase.lib")
#pragma comment(lib, "CEGUIDirect3D9Renderer.lib")
#endif
#endif

///
/// Define the foreach loop in C++
/// Usage
///		- foreach(elementType, element, containerType, container)
///			-#elementType:		the class of element.
///			-#element:			the variable name to represent each element.
///			-#containerType:	the class of container, such as "list<int>".
///			-#container:		the variable name of the container.
///
#define foreach(elementType, element, containerType, container) \
	for (containerType::iterator iter = container.begin(); iter != container.end(); iter++)\
	for (bool go = true; go;)\
	for (elementType & element = *iter;go; go=false)

#define FAIL_RET(x) do { if( FAILED( hr = ( x  ) ) ) \
	return hr; } while(0)

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) { x->Release(); x = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { delete x; x = NULL; }
#endif

#endif