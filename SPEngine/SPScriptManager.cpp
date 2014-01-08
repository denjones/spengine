#include "StdAfx.h"
#include "SPScriptManager.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

using namespace KScript;
using namespace std;

namespace SPEngine
{
	bool SPScriptManager::Load( SPString path )
	{
		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to open script file: " + path);
			return false;
		}

		
		LONGLONG length = file->GetFileLength();
		void* pData = new char[(UINT)length];

		if (!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to read script file: " + path);
			return false;
		}

		
		SPFileManager::GetSingleton().CloseFile(path);
		
		if (!script->LoadScriptStream(pData, (DWORD)length, path))
		{
			delete [] pData;
			pData = NULL;
			return false;
		}
		delete [] pData;
		pData = NULL;
		return true;
	}

	SPScriptManager::SPScriptManager() : KScriptRunner()
	{
		AddExtension(L"include", new SPIncludeFunction(this));
	}

	KSValue SPIncludeFunction::Function(KSScript* currentScript, vector<KSValue> args )
	{
		if (args.size() == 0)
		{
			return KSValue();
		}

		bool inherit = false;
		bool rewrite = false;

		if (args.size() > 1)
		{
			inherit = SPStringHelper::StringToInt(args[1].value) != 0;
		}

		if (args.size() > 2)
		{
			rewrite = SPStringHelper::StringToInt(args[2].value) != 0;
		}

		KString path = args[0].value;

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to open script file: " + path);
			return KSValue();
		}

		LONGLONG length = file->GetFileLength();
		void* pData = new char[(UINT)length];

		if (!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPScript] WARNING: Failed to read script file: " + path);
			return KSValue();
		}

		SPFileManager::GetSingleton().CloseFile(path);

		KSScript innerScript(runner);

		if (!innerScript.LoadScriptStream(pData, (DWORD)length, path))
		{
			delete [] pData;
			pData = NULL;
			return KSValue();
		}

		//Script innerScript(path, runner);

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}

		innerScript.Execute();

		if (rewrite)
		{
			currentScript->SetVariableMap(innerScript.GetVariableMap());
		}

		return KSValue();
	}

	SPIncludeFunction::SPIncludeFunction( SPScriptManager* setRunner )
	{
		runner = setRunner;
	}

}

