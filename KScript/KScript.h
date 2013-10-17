//////////////////////////////////////////////////////////////////////////
/// @file		KScript.cpp the header file of KScript class.
/// @author		Ken.J
/// @version	Alpha 0.3
/// @date		2012-4-8
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"
#include <hash_map>
#include <vector>
#include <antlr3.h>
#include "KSmartPtr.h"

#ifdef UNICODE
#define KString wstring
#elif
#define KString string
#endif // UNICODE


using namespace std;

//////////////////////////////////////////////////////////////////////////
/// @brief Namespace KScript. To include element of the script engine.
//////////////////////////////////////////////////////////////////////////
namespace KScript 
{
	class KScriptRunner;

	//////////////////////////////////////////////////////////////////////
	/// @brief Value class. To represent a base variable type in the script.
	//////////////////////////////////////////////////////////////////////
	class Value
	{
	public:
		KString value;			///< The real value in KString.
		ANTLR3_UINT32 type;		///< The running type.

		/// @brief The constructor of a value.
		Value();
		Value(KString setValue, ANTLR3_UINT32 setType);
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief HashString class. To generate hash value of a KString.
	//////////////////////////////////////////////////////////////////////
	class HashString : public hash_compare<KString, less<KString>>
	{
	public:
		HashString( );
		HashString( less<KString> pred );

		size_t operator( )( const KString& _Key ) const;

		bool operator( )( 
			const KString& _Key1,
			const KString& _Key2
			) const;
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief EqualString class. To check if two KString is the same.
	//////////////////////////////////////////////////////////////////////
	struct EqualString 
	{
		bool operator()(const KString &string1, const KString &string2) const;
	};

	typedef hash_map<KString, Value, HashString> VariableMap;

	class Script;

	typedef KSmartPtr<Script> ScriptPtr;

	//////////////////////////////////////////////////////////////////////
	/// @brief Script class. To represent a script.
	//////////////////////////////////////////////////////////////////////
	class Script
	{
		void* parser;
		void* lexer;		
		pANTLR3_INPUT_STREAM input;
		void* tstream;		

		bool isInnerScript;
		bool isNeedToReturn;
		Value returnValue;
		

	public:
		VariableMap variables;	///< Variables list.
		pANTLR3_BASE_TREE tree;							///< The syntax tree.
		KScriptRunner* runner;							///< The runner belonged to.
		KString fileName;								///< File name of the script.
		int functionOrder;

		/// @brief Constructor of a script.
		Script();
		Script(KString setScript, KScriptRunner* setRunner, bool isInner = false);
		Script(KScriptRunner* setRunner, bool isInner = false);
		virtual ~Script();

		/// @brief Load a script from a file.
		bool LoadScript(KString path);
		bool LoadStringScript(KString script, KString path = L"");

		bool LoadScriptStream(void* pBuffer, DWORD length, KString path = L"" );

		/// @brief Execute the script file.
		Value Execute();
		Value Execute(pANTLR3_BASE_TREE root);

		/// @brief Check if a variable name is valid.
		bool IsIDValid( KString name );

		/// @brief New an ID with default zero value.
		void NewID(KString id);

		/// @brief Get the text of a tree node.
		KString GetText(pANTLR3_BASE_TREE theTree);

		/// @brief Get the type of a tree node.
		ANTLR3_UINT32 GetType(pANTLR3_BASE_TREE theTree);

		/// @brief Get the n(th) child node of a node.
		pANTLR3_BASE_TREE GetChild(pANTLR3_BASE_TREE theTree, int index);

		/// @brief Get the number of children of a node.
		int GetChildCount(pANTLR3_BASE_TREE theTree);

		/// @brief Get variables.
		hash_map<KString, Value, HashString> GetVariableMap();

		/// @brief Set variables.
		bool ClearVariableMap();
		bool SetVariableMap(hash_map<KString, Value, HashString> newMap);
		bool UpdateVariableMap(hash_map<KString, Value, HashString> newMap);

		/// @brief Analyze a tree recursively.
		Value Analyze(pANTLR3_BASE_TREE subTree);

		bool Unload();

		ScriptPtr Copy();
		pANTLR3_BASE_TREE FindFunctionRoot(KString name, pANTLR3_BASE_TREE subTree);
	};

	
}