// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

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