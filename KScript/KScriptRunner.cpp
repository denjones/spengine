#include "StdAfx.h"
#include "KScriptRunner.h"
#include <antlr3.h>
#include "KScriptLexer.h"
#include "KScriptParser.h"
#include "StringHelper.h"

namespace KScript
{
	KSValue ExtendedArgsFunction::Function(KSScript* currentScript, vector<KSValue> args)
	{
		return KSValue(L"0", INT);
	}

	KScriptRunner::KScriptRunner(void)
	{
		script = new KSScript(this);
		includeFunction = NULL;
		includeFunction = new IncludeFunction(this);
		AddExtension(L"include", includeFunction);
		AddExtension(L"include", new IncludeMapArgsFunction(this));
	}


	KScriptRunner::~KScriptRunner(void)	{}

	bool KScriptRunner::IsArgsFunctionValid(KString name)
	{
		if (extentedArgsFunctions.find(name) == extentedArgsFunctions.end())
		{
			return false;
		}

		return true;
	}

	bool KScriptRunner::AddExtension(KString name, ArgsFunctionPtr function)
	{
		extentedArgsFunctions[name] = function;
		return true;
	}

	bool KScriptRunner::AddExtension( KString name, MapArgsFunctionPtr function )
	{
		extentedMapArgsFunctions[name] = function;
		return true;
	}

	bool KScriptRunner::Load(KString path)
	{
		return script->LoadScript(path);
	}

	KSValue KScriptRunner::Execute()
	{
		return script->Execute();
	}

	KSValue KScriptRunner::ExecuteExtendedCommand(
		KSScript* currentScript, KString name, vector<KSValue> args)
	{
		KSValue result(L"0", INT);

		if (IsArgsFunctionValid(name))
		{
			result = extentedArgsFunctions[name]->Function(currentScript, args);
		}

		return result;
	}

	KSValue KScriptRunner::ExecuteExtendedCommand( KSScript* currentScript, KString name, VariableMap args )
	{
		KSValue result(L"0", INT);

		if (IsMapArgsFunctionValid(name))
		{
			result = extentedMapArgsFunctions[name]->Function(currentScript, args);
		}

		return result;
	}

	bool KScriptRunner::IsMapArgsFunctionValid( KString name )
	{
		if (extentedMapArgsFunctions.find(name) == extentedMapArgsFunctions.end())
		{
			return false;
		}

		return true;
	}

	bool KScriptRunner::LoadString( KString stringStream )
	{
		return script->LoadStringScript(stringStream);
	}

	bool KScriptRunner::AddUserDefinedFunction( KString name, MapArgsFunctionPtr function )
	{
		extentedMapArgsFunctions[name] = function;
		//userDefinedScriptStringFunctions[name] = function;
		return true;
	}

	KSValue IncludeFunction::Function(KSScript* currentScript, vector<KSValue> args )
	{
		if (args.size() == 0)
		{
			return KSValue();
		}

		bool inherit = false;
		bool rewrite = false;

		if (args.size() > 1)
		{
			inherit = StringHelper::StringToInt(args[1].value) != 0;
		}

		if (args.size() > 2)
		{
			rewrite = StringHelper::StringToInt(args[2].value) != 0;
		}

		KString path = args[0].value;
		KSScript innerScript(path, runner, true);
		innerScript.fileName = currentScript->fileName;

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}

		KSValue result = innerScript.Execute();

		if (rewrite)
		{
			currentScript->SetVariableMap(innerScript.GetVariableMap());
		}

		return result;
	}

	IncludeFunction::IncludeFunction( KScriptRunner* setRunner )
	{
		runner = setRunner;
	}


	ScriptStringFunction::ScriptStringFunction( KScriptRunner* setRunner, KString setScriptString )
	{
		runner = setRunner;
		scriptString = setScriptString;
		innerScript = new KSScript(runner, true);
		innerScript->LoadStringScript(scriptString, L"");
	}

	KScript::KSValue ScriptStringFunction::Function( KSScript* currentScript, VariableMap args )
	{	
		innerScript->SetVariableMap(currentScript->GetVariableMap());
		innerScript->SetVariableMap(args);
		innerScript->fileName = currentScript->fileName;
		innerScript->functionOrder = currentScript->functionOrder;
		KSValue result = innerScript->Execute();
		currentScript->UpdateVariableMap(innerScript->GetVariableMap());

		return result;
	}


	KScript::KSValue IncludeMapArgsFunction::Function( KSScript* currentScript, VariableMap args )
	{
		if (args.size() == 0)
		{
			return KSValue();
		}

		bool inherit = false;
		bool rewrite = false;

		if (args.find(L"inherit") != args.end() && args[L"inherit"].value != L"0")
		{
			inherit = true;
		}

		if (args.find(L"rewrite") != args.end() && args[L"rewrite"].value != L"0")
		{
			rewrite = true;
		}

		if (args.find(L"file") == args.end())
		{
			return KSValue();
		}

		KString path = args[L"file"].value;
		KSScript innerScript(path, runner, true);
		innerScript.fileName = currentScript->fileName;
		innerScript.functionOrder = currentScript->functionOrder;

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}		

		KSValue result = innerScript.Execute();

		if (rewrite)
		{
			currentScript->SetVariableMap(innerScript.GetVariableMap());
		}

		return result;
	}

	IncludeMapArgsFunction::IncludeMapArgsFunction( KScriptRunner* setRunner )
	{
		runner = setRunner;
	}


	KSValue UserDefinedMapArgsFunction::Function( KSScript* currentScript, VariableMap args )
	{
		innerScript->SetVariableMap(currentScript->GetVariableMap());
		innerScript->SetVariableMap(args);
		innerScript->functionOrder = currentScript->functionOrder;
		innerScript->fileName = currentScript->fileName;
		KSValue result = innerScript->Execute(functionRoot);
		currentScript->UpdateVariableMap(innerScript->GetVariableMap());
		return result;
	}

	UserDefinedMapArgsFunction::UserDefinedMapArgsFunction( KScriptRunner* setRunner, KSScript* sourceScript , KString funcName)
	{
		runner = setRunner;
		innerScript = sourceScript->Copy();
		functionRoot = innerScript->FindFunctionRoot(funcName, innerScript->tree);
	}

}
