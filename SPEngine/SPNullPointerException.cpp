#include "StdAfx.h"
#include "SPNullPointerException.h"

namespace SPEngine
{
	SPNullPointerException::SPNullPointerException(void) : runtime_error("Access through NULL pointer")
	{
	}

	SPNullPointerException::~SPNullPointerException(void)
	{
	}
}