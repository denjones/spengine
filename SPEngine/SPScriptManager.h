//////////////////////////////////////////////////////////////////////////
/// @file		SPScriptManager.h the header file of SPScriptManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-30
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <KScriptRunner.h>
#include <vector>
#include "SPString.h"

using namespace KScript;
using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPScriptManager
	/// Inherit form KScriptRunner and rewrite the load method so that input
	/// file can be in memory.
	///
	//////////////////////////////////////////////////////////////////////
	class SPScriptManager : public KScriptRunner
	{
	public:
		SPScriptManager();
		virtual bool Load(SPString path);
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief IncludeFunction class to include a script file in a script.
	//////////////////////////////////////////////////////////////////////
	class SPIncludeFunction : public ExtendedArgsFunction
	{
	public:
		SPIncludeFunction(SPScriptManager* setRunner);
		SPScriptManager* runner;

		KSValue Function(KSScript* currentScript, vector<KSValue> args);

	};
}

