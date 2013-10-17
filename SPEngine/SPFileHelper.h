//////////////////////////////////////////////////////////////////////////
/// @file		SPFileHelper.h the header file of SPFileHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-10-05
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPString.h"

using namespace std;
namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFileHelper static class to provide helper function for
	/// file operation.
	///
	//////////////////////////////////////////////////////////////////////
	class SPFileHelper
	{
	private:
		SPFileHelper(void);
		~SPFileHelper(void);

	public:
		static bool IsPathExists(SPString path);
		static SPString GetUpperPath(SPString path);
		static bool CreatePath(SPString path);
	};
}
