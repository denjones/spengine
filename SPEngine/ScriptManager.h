#pragma once
#include <KScriptRunner.h>
#include <vector>

using namespace KScript;
using namespace std;

namespace SPEngine
{
	class ScriptManager : public KScriptRunner
	{
	public:
		ScriptManager(void);
		~ScriptManager(void);
	};
}