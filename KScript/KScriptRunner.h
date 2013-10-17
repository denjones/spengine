//////////////////////////////////////////////////////////////////////////
/// @file		KScriptRunner.cpp the header file of KScriptRunner class.
/// @author		Ken.J
/// @version	Alpha 0.3
/// @date		2012-4-8
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "KScript.h"
#include "KSmartPtr.h"

using namespace std;


namespace KScript
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ExtentedArgsFunction class to represent an "@" function, of 
	/// which arguments list is a vector of Value.
	//////////////////////////////////////////////////////////////////////
	class ExtendedArgsFunction
	{
	public:
		virtual ~ExtendedArgsFunction(){}
		/// @brief Function method.
		/// Complete the method to build a function.
		/// @param[in] vector<Value> arguments list.
		/// @return Value type.
		virtual Value Function(Script* currentScript, vector<Value> args) = 0;
	};

	typedef KSmartPtr<ExtendedArgsFunction> ArgsFunctionPtr;

	//////////////////////////////////////////////////////////////////////
	/// @brief ExtendedMapArgsFunction class to represent an "@" function,
	/// of which arguments list is a set of key-value pairs.
	//////////////////////////////////////////////////////////////////////
	class ExtendedMapArgsFunction
	{
	public:
		virtual ~ExtendedMapArgsFunction(){}
		/// @brief Function method.
		/// Complete the method to build a function.
		/// @param[in] VariableMap arguments list.
		/// @return Value type.
		virtual Value Function(Script* currentScript, VariableMap args) = 0;
	};

	typedef KSmartPtr<ExtendedMapArgsFunction> MapArgsFunctionPtr;


	//////////////////////////////////////////////////////////////////////
	/// @brief UserDefinedMapArgsFunction class to include a function.
	//////////////////////////////////////////////////////////////////////
	class UserDefinedMapArgsFunction : public ExtendedMapArgsFunction
	{
		ScriptPtr innerScript;
		pANTLR3_BASE_TREE functionRoot;
		KScriptRunner* runner;

	public:
		virtual ~UserDefinedMapArgsFunction(){}

		UserDefinedMapArgsFunction(KScriptRunner* setRunner, Script* sourceScript, KString funcName);

		Value Function(Script* currentScript, VariableMap args);
	};


	//////////////////////////////////////////////////////////////////////
	/// @brief IncludeFunction class to include a script file in a script.
	//////////////////////////////////////////////////////////////////////
	class IncludeFunction : public ExtendedArgsFunction
	{
	public:
		virtual ~IncludeFunction(){}
		IncludeFunction(KScriptRunner* setRunner);
		KScriptRunner* runner;

		Value Function(Script* currentScript, vector<Value> args);

	};

	//////////////////////////////////////////////////////////////////////
	/// @brief IncludeMapArgsFunction class to include a script file in a script.
	//////////////////////////////////////////////////////////////////////
	class IncludeMapArgsFunction : public ExtendedMapArgsFunction
	{
	public:
		virtual ~IncludeMapArgsFunction(){}
		IncludeMapArgsFunction(KScriptRunner* setRunner);
		KScriptRunner* runner;

		Value Function(Script* currentScript, VariableMap args);

	};

	//////////////////////////////////////////////////////////////////////
	/// @brief ScriptStringFunction class to include a script string.
	//////////////////////////////////////////////////////////////////////
	class ScriptStringFunction : public ExtendedMapArgsFunction
	{
	public:
		ScriptStringFunction(KScriptRunner* setRunner, KString setScriptString);
		virtual ~ScriptStringFunction(){}
		KScriptRunner* runner;
		KString scriptString;
		ScriptPtr innerScript;

		Value Function(Script* currentScript, VariableMap args);

	};

	typedef KSmartPtr<ScriptStringFunction> ScriptStringFunctionPtr;

	typedef hash_map<KString, ArgsFunctionPtr, HashString> ArgsFunctionMap;
	typedef hash_map<KString, MapArgsFunctionPtr, HashString> MapArgsFunctionMap;
	typedef hash_map<KString, ScriptStringFunctionPtr, HashString> ScriptStringFunctionMap;

	//////////////////////////////////////////////////////////////////////
	/// @brief KScriptRunner class to run a KScript.
	//////////////////////////////////////////////////////////////////////
	class KScriptRunner
	{
	protected:
		friend class Script;
		friend class UserDefinedMapArgsFunction;

		ScriptPtr script;	///< Inner script.

		/// @brief A hash map to hold extended functions.
		ArgsFunctionMap extentedArgsFunctions;
		MapArgsFunctionMap extentedMapArgsFunctions;
		ScriptStringFunctionMap userDefinedScriptStringFunctions;

		ArgsFunctionPtr includeFunction;

	public:
		KScriptRunner(void);
		virtual ~KScriptRunner(void);

		/// @brief Load Load a script file.
		/// @param[in] path The path of the script file.
		virtual bool Load(KString path);
		virtual bool LoadString(KString stringStream);

		/// @brief IsFunctionValid Check if a function is implemented.
		/// @param[in] name The name of the function.
		virtual bool IsArgsFunctionValid(KString name);
		virtual bool IsMapArgsFunctionValid(KString name);

		/// @brief ExecuteExtendedCommand 
		/// Run a function with given name and arguments.
		/// @param[in] name The name of the function.
		/// @param[in] args The arguments list.
		virtual Value ExecuteExtendedCommand(Script* currentScript, KString name, vector<Value> args);
		virtual Value ExecuteExtendedCommand(Script* currentScript, KString name, VariableMap args);

		/// @brief Execute Execute the script.
		virtual Value Execute();

		/// @brief AddExtension Add an extended function.
		/// @param[in] name The name of the function.
		/// @param[in] function The pointer to an ExtendedFunction.
		virtual bool AddExtension(KString name, ArgsFunctionPtr function);
		virtual bool AddExtension(KString name, MapArgsFunctionPtr function);
		virtual bool AddUserDefinedFunction(KString name, MapArgsFunctionPtr function);
	};

	typedef KSmartPtr<KScriptRunner> KScriptRunnerPtr;
}



