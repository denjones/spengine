#include "StdAfx.h"
#include "KScriptRunner.h"
#include <antlr3.h>
#include "KScriptLexer.h"
#include "KScriptParser.h"
#include "StringHelper.h"

namespace KScript
{
	Value ExtendedArgsFunction::Function(Script* currentScript, vector<Value> args)
	{
		return Value(L"0", INT);
	}

	KScriptRunner::KScriptRunner(void)
	{
		script = new Script(this);
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

	Value KScriptRunner::Execute()
	{
		return script->Execute();
	}

	Value KScriptRunner::ExecuteExtendedCommand(
		Script* currentScript, KString name, vector<Value> args)
	{
		Value result(L"0", INT);

		if (IsArgsFunctionValid(name))
		{
			result = extentedArgsFunctions[name]->Function(currentScript, args);
		}

		return result;
	}

	Value KScriptRunner::ExecuteExtendedCommand( Script* currentScript, KString name, VariableMap args )
	{
		Value result(L"0", INT);

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

	Value IncludeFunction::Function(Script* currentScript, vector<Value> args )
	{
		if (args.size() == 0)
		{
			return Value();
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
		Script innerScript(path, runner, true);
		innerScript.fileName = currentScript->fileName;

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}

		Value result = innerScript.Execute();

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
		innerScript = new Script(runner, true);
		innerScript->LoadStringScript(scriptString, L"");
	}

	KScript::Value ScriptStringFunction::Function( Script* currentScript, VariableMap args )
	{	
		innerScript->SetVariableMap(currentScript->GetVariableMap());
		innerScript->SetVariableMap(args);
		innerScript->fileName = currentScript->fileName;
		innerScript->functionOrder = currentScript->functionOrder;
		Value result = innerScript->Execute();
		currentScript->UpdateVariableMap(innerScript->GetVariableMap());

		return result;
	}


	KScript::Value IncludeMapArgsFunction::Function( Script* currentScript, VariableMap args )
	{
		if (args.size() == 0)
		{
			return Value();
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
			return Value();
		}

		KString path = args[L"file"].value;
		Script innerScript(path, runner, true);
		innerScript.fileName = currentScript->fileName;
		innerScript.functionOrder = currentScript->functionOrder;

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}		

		Value result = innerScript.Execute();

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


	Value UserDefinedMapArgsFunction::Function( Script* currentScript, VariableMap args )
	{
		innerScript->SetVariableMap(currentScript->GetVariableMap());
		innerScript->SetVariableMap(args);
		innerScript->functionOrder = currentScript->functionOrder;
		innerScript->fileName = currentScript->fileName;
		Value result = innerScript->Execute(functionRoot);
		currentScript->UpdateVariableMap(innerScript->GetVariableMap());
		return result;
	}

	UserDefinedMapArgsFunction::UserDefinedMapArgsFunction( KScriptRunner* setRunner, Script* sourceScript , KString funcName)
	{
		runner = setRunner;
		innerScript = sourceScript->Copy();
		functionRoot = innerScript->FindFunctionRoot(funcName, innerScript->tree);
	}

}
