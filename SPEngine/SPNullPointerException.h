#pragma once
#include <stdexcept>
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	class SPNullPointerException :
		public runtime_error
	{
	public:
		SPNullPointerException(void);
		~SPNullPointerException(void);
	};
}

