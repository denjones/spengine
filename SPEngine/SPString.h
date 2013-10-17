#pragma once
#include <string>

namespace SPEngine
{
#ifdef UNICODE
#define SPString std::wstring
#else
#define	SPString std::string
#endif
}