// KScript.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "KScript.h"
#include "StringHelper.h"
#include "KScriptLexer.h"
#include "KScriptParser.h"
#include "KScriptRunner.h"
#include <hash_map>
#include <vector>
#include <antlr3.h>

using namespace std;
using namespace KScript::StringHelper;

namespace KScript 
{
	Value::Value()
	{
		value = L"";
		type = 0;
	}

	Value::Value(KString setValue, ANTLR3_UINT32 setType)
	{
		value = setValue;
		type = setType;
	}

	HashString::HashString(){}
	HashString::HashString( less<KString> pred ){}

	size_t HashString::operator( )( const KString& _Key ) const
	{
		unsigned long __h = 0;
		for (size_t i = 0 ; i < _Key.size() ; i ++)
		{
			__h = 107*__h + _Key[i];
		}
		return size_t(__h);
	}

	bool HashString::operator( )( 
		const KString& _Key1,
		const KString& _Key2
		) const
	{
		return !(_Key1.compare(_Key2) == 0);
	}

	bool EqualString::operator()(const KString &string1, const KString &string2) const
	{
		return string1.compare(string2) == 0;
	}

	Script::Script()
	{
		tree = NULL;
		runner = NULL;
		parser = NULL;
		lexer = NULL;
		input = NULL;
		tstream = NULL;
		isNeedToReturn = false;
		returnValue = Value(L"0",INT);
	}

	Script::Script(KString setScript, KScriptRunner* setRunner, bool isInner)
	{
		tree = NULL;
		runner = NULL;
		parser = NULL;
		lexer = NULL;
		input = NULL;
		tstream = NULL;
		runner = setRunner;
		isInnerScript = isInner;
		isNeedToReturn = false;
		returnValue = Value(L"0",INT);
		LoadScript(setScript);
		fileName = setScript;
	}

	Script::Script(KScriptRunner* setRunner, bool isInner)
	{
		tree = NULL;
		runner = NULL;
		parser = NULL;
		lexer = NULL;
		input = NULL;
		tstream = NULL;
		isInnerScript = isInner;
		runner = setRunner;
		isNeedToReturn = false;
		returnValue = Value(L"0",INT);
	}

	bool Script::LoadScript(KString path)
	{
		Unload();

		freopen("log\\script.log", "w", stderr);

		fileName = path;
		tree = NULL;

		input = antlr3FileStreamNew((pANTLR3_UINT8)path.c_str(), ANTLR3_ENC_UTF8);		

		// Load input stream
		//input = antlr3AsciiFileStreamNew((pANTLR3_UINT8)path.c_str());
		//	//antlr3AsciiFileStreamNew((pANTLR3_UINT8)path.c_str());

		if ( input == NULL )
		{
			ANTLR3_FPRINTF(stderr,"Failed to load script file!");
			fclose(stderr);
			return false;
		}

		// Create kscript lexer
		lexer = KScriptLexerNew((pANTLR3_INPUT_STREAM)input);

		if ( lexer == NULL )
		{
			ANTLR3_FPRINTF(stderr, "Failed to create the lexer!");
			fclose(stderr);
			return false;
		}

		// Get token stream
		tstream = antlr3CommonTokenStreamSourceNew(
			ANTLR3_SIZE_HINT, TOKENSOURCE(((pKScriptLexer)lexer)));
		if (tstream == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to get token stream!");
			fclose(stderr);
			return false;
		}

		// Create the parser
		parser = KScriptParserNew((pANTLR3_COMMON_TOKEN_STREAM)tstream); 
		if (parser == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to create the parser!");
			fclose(stderr);
			return false;
		}

		// Get the grammar tree
		KScriptParser_program_return  result =
			(KScriptParser_program_return)(((pKScriptParser)parser)->program((pKScriptParser)parser));

		if(((pKScriptParser)parser)->pParser->rec->state->errorCount>0)
		{
			ANTLR3_FPRINTF(stderr, "The parser returned %d errors.",
				((pKScriptParser)parser)->pParser->rec->state->errorCount);
			fclose(stderr);
			return false;
		}

		tree = (pANTLR3_BASE_TREE)result.tree;
		if (tree == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to build the grammar tree.");
			fclose(stderr);
			return false;
		}

		fclose(stderr);
		return true;
	}

	bool Script::LoadStringScript( KString script , KString path)
	{
		string stringScript = StringHelper::WStringToUTF8String(script.c_str());
		DWORD size = stringScript.size() + 1;
		char* pData = new char[size];
		memcpy(pData, stringScript.c_str(),size);

		bool result = LoadScriptStream(pData, size, path);

		delete [] pData;

		return result;
	}


	bool Script::LoadScriptStream( void* pBuffer, DWORD length, KString path)
	{
		Unload();

		fileName = path;

		freopen("log\\script.log", "a", stderr);

		tree = NULL;

		// Allocate input stream.
		input   = (pANTLR3_INPUT_STREAM)
			ANTLR3_CALLOC(1, sizeof(ANTLR3_INPUT_STREAM));		

		string buffer;

		// See if there is a BOM at the start of this UTF-8 sequence
		// and just eat it if there is. Windows .TXT files have this for instance
		// as it identifies UTF-8 even though it is of no consequence for byte order
		// as UTF-8 does not have a byte order.
		//
		if  (   (ANTLR3_UINT8)(*(char*)pBuffer)      == 0xEF
			&&  (ANTLR3_UINT8)(*((char*)pBuffer + 1))    == 0xBB
			&&  (ANTLR3_UINT8)(*((char*)pBuffer + 2))    == 0xBF)
		{
			// The UTF8 BOM is present so skip it
			//
			buffer = "@KScript_0_8;" + string((char*)pBuffer + 3, length - 3);
		}
		else
		{
			buffer = "@KScript_0_8;" + string((char*)pBuffer, length);
		}
		
		// Read buffer.
		input->data	    = ANTLR3_MALLOC((size_t)buffer.size());
		input->sizeBuf  = buffer.size();

		if	(input->data == NULL)
		{
			fclose(stderr);
			return false;
		}

		input->isAllocated	= ANTLR3_TRUE;

		
		memcpy(input->data, buffer.c_str(), buffer.size());

		// Setup input stream.
		antlr3GenericSetupStream(input);

		input->encoding = ANTLR3_ENC_UTF8;

		//// See if there is a BOM at the start of this UTF-8 sequence
		//// and just eat it if there is. Windows .TXT files have this for instance
		//// as it identifies UTF-8 even though it is of no consequence for byte order
		//// as UTF-8 does not have a byte order.
		////
		//if  (   (ANTLR3_UINT8)(*((pANTLR3_UINT8)input->nextChar))      == 0xEF
		//	&&  (ANTLR3_UINT8)(*((pANTLR3_UINT8)input->nextChar+1))    == 0xBB
		//	&&  (ANTLR3_UINT8)(*((pANTLR3_UINT8)input->nextChar+2))    == 0xBF)
		//{
		//	// The UTF8 BOM is present so skip it
		//	//
		//	input->nextChar = (void *)((pANTLR3_UINT8)input->nextChar + 3);
		//}

		// Install the UTF8 input routines
		antlr3UTF8SetupStream(input);

		//input = antlr3FileStreamNew((pANTLR3_UINT8)path.c_str(), ANTLR3_ENC_UTF8);		

		// Load input stream
		//input = antlr3AsciiFileStreamNew((pANTLR3_UINT8)path.c_str());
		//	//antlr3AsciiFileStreamNew((pANTLR3_UINT8)path.c_str());

		if ( input == NULL )
		{
			ANTLR3_FPRINTF(stderr,"Failed to load script file!\n\n");
			fclose(stderr);
			return false;
		}

		input->istream->streamName	= input->strFactory->newStr8(input->strFactory, (pANTLR3_UINT8)StringHelper::WStringToUTF8String(fileName).c_str());
		input->fileName		= input->istream->streamName;
		//input->fileName		= input->strFactory->newStr8(input->strFactory, (pANTLR3_UINT8)StringHelper::WStringToUTF8String(fileName).c_str());

		// Create KScript lexer
		lexer = KScriptLexerNew((pANTLR3_INPUT_STREAM)input);

		if ( lexer == NULL )
		{
			ANTLR3_FPRINTF(stderr, "Failed to create the lexer!\n\n");
			fclose(stderr);
			return false;
		}

		// Get token stream
		tstream = antlr3CommonTokenStreamSourceNew(
			ANTLR3_SIZE_HINT, TOKENSOURCE(((pKScriptLexer)lexer)));
		if (tstream == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to get token stream!\n\n");
			fclose(stderr);
			return false;
		}

		// Create the parser
		parser = KScriptParserNew((pANTLR3_COMMON_TOKEN_STREAM)tstream); 
		if (parser == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to create the parser!\n\n");
			fclose(stderr);
			return false;
		}

		// Get the grammar tree
		KScriptParser_program_return  result =
			(KScriptParser_program_return)(((pKScriptParser)parser)->program((pKScriptParser)parser));

		if(((pKScriptParser)parser)->pParser->rec->state->errorCount>0)
		{
			ANTLR3_FPRINTF(stderr, "The parser returned %d errors.\n\n",
				((pKScriptParser)parser)->pParser->rec->state->errorCount);
			fclose(stderr);
			return false;
		}

		tree = (pANTLR3_BASE_TREE)result.tree;
		if (tree == NULL)
		{
			ANTLR3_FPRINTF(stderr, "Failed to build the grammar tree.\n\n");
			fclose(stderr);
			return false;
		}

		fclose(stderr);

		return true;
	}

	Value Script::Execute()
	{
		return Execute(tree);
	}

	KScript::Value Script::Execute( pANTLR3_BASE_TREE root )
	{
		Value result;

		try
		{
			if (root == NULL)
			{
				MessageBox(NULL, KString(
					L"Failed to load script! There may be some error in the script file \"" + fileName + L"\". For more details, please check the log file \"/log/script.log\".").c_str(), 
					NULL, NULL);
				return result;
			}

			if (GetChildCount(root) > 0)
			{
				for (int num = 0; num < GetChildCount(root); num++)
				{
					Analyze(GetChild(root, num));

					if (isNeedToReturn)
					{
						isNeedToReturn = false;
						return returnValue;
					}
				}
			}
		}
		catch (exception* e)
		{
			MessageBox(NULL, 
				KString(L"Error: runtime error while executing script file \""
				+ fileName + L"\"!").c_str() , NULL, NULL);
		}

		return result;
	}

	bool Script::IsIDValid( KString name )
	{
		if (variables.find(name) == variables.end())
		{
			return false;
		}

		return true;
	}

	void Script::NewID(KString id)
	{
		variables[id] = Value(L"0", REAL);
	}

	KString Script::GetText(pANTLR3_BASE_TREE theTree)
	{
		//setlocale(LC_ALL, "chs");		
		//wstring s = (wchar_t*)(theTree->getText(theTree))->chars;
		//KString s2 = (char*)(theTree->getText(theTree))->chars;
		KString s = StringHelper::UTF8CStringToWString((char*)(theTree->getText(theTree))->chars);
		return s;
	}

	ANTLR3_UINT32 Script::GetType(pANTLR3_BASE_TREE theTree)
	{
		return theTree->getType(theTree);
	}

	pANTLR3_BASE_TREE Script::GetChild(pANTLR3_BASE_TREE theTree, int index)
	{
		return (pANTLR3_BASE_TREE)theTree->getChild(theTree, index);
	}

	int Script::GetChildCount(pANTLR3_BASE_TREE theTree)
	{
		return theTree->getChildCount(theTree);
	}		

	Value Script::Analyze(pANTLR3_BASE_TREE subTree)
	{		
		if (isNeedToReturn)
		{
			return Value(L"0", INT);
		}

		ANTLR3_UINT32 type = INT;

		type = GetType(subTree);

		if (type >= EOF || type < 0 )
		{
			return Value(L"EOF", EOF);
		}

		if (type == RETURN)
		{
			isNeedToReturn = true;

			if (GetChildCount(subTree) > 0)
			{
				returnValue = Analyze(GetChild(subTree, 0));
			}
			else
			{
				returnValue =  Value(L"0", INT);	
			}

			return Value(L"0", INT);
		}

		#pragma region Base Type ��������

		if (type == KNULL)
		{
			return Value(L"0", INT);
		}

		if (type == INT ||
			type == REAL)
		{
			return Value(GetText(subTree), type);
		}

		if (type == HEX)
		{
			wstring hex = GetText(subTree);
			UINT decimalValue;
			swscanf(hex.c_str(), L"%x", &decimalValue);
			return Value(StringHelper::ToWString((int)decimalValue),INT);
		}

		if (type == STRING)
		{
			KString str = GetText(subTree).substr(1, GetText(subTree).length() - 2);

			str = StringHelper::ReplaceAll(str, L"\\[", L"[");
			str = StringHelper::ReplaceAll(str, L"\\]", L"]");
			str = StringHelper::ReplaceAll(str, L"\\n", L"\n");
			str = StringHelper::ReplaceAll(str, L"\\f", L"\f");
			str = StringHelper::ReplaceAll(str, L"\\'", L"\'");
			str = StringHelper::ReplaceAll(str, L"\\\"", L"\"");

			return Value(str, STRING);
		}

		if (type == BTRUE)
		{
			return Value(L"1",INT);
		}

		if (type == BFALSE)
		{
			return Value(L"0",INT);
		}
		#pragma endregion

		#pragma region Identifier ��ʶ��
		if (type == IDENTIFIER)
		{
			Value result;

			if (IsIDValid(GetText(subTree)))
			{
				result = variables[GetText(subTree)];
			}
			else
			{					
				result.value = L"0";
				result.type  = INT;
				variables[GetText(subTree)] = result;
			}


			if (GetChildCount(subTree) > 0)
			{
				if (GetType(GetChild(subTree, 0)) == PLUSPLUS)
				{
					if (result.type == INT)
					{
						variables[GetText(subTree)].value = ToWString(
							(int)(StringToInt(variables[GetText(subTree)].value) + 1));
					}
					else
					{
						variables[GetText(subTree)].value = ToWString(
							StringToFloat(variables[GetText(subTree)].value) + 1);
					}
				}
				else
				{
					if (result.type == INT)
					{
						variables[GetText(subTree)].value = ToWString(
							(int)(StringToInt(variables[GetText(subTree)].value) - 1));
					}
					else
					{
						variables[GetText(subTree)].value = ToWString(
							StringToFloat(variables[GetText(subTree)].value) - 1);
					}
				}
			}

			return result;
		}
		#pragma endregion

		#pragma region Assignment ��ֵ����
		#pragma region Simple Assignment һ�㸳ֵ
		if (type == ASSIGN)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = Analyze(GetChild(subTree, 1));

			variables[parameterA] = result;

			return result;				
		}
		#pragma endregion

		#pragma region Add and Assign �ӵ���
		if (type == PLUSASSIGN)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = Analyze(GetChild(subTree, 1));

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) + StringToInt(result.value));
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) + StringToFloat(result.value));
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion

		#pragma region Subtract and Assign ������
		if (type == MINUSASSIGN)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = Analyze(GetChild(subTree, 1));

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) - StringToInt(result.value));
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) - StringToFloat(result.value));
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion

		#pragma region Multiply and Assign �˵���
		if (type == MULTASSIGN)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = Analyze(GetChild(subTree, 1));

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) * StringToInt(result.value));
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) * StringToFloat(result.value));
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion

		#pragma region Divide and Assign ������
		if (type == DIVIDEASSIGN)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = Analyze(GetChild(subTree, 1));

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) / StringToInt(result.value));
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) / StringToFloat(result.value));
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion
		#pragma endregion

		#pragma region Arithmetic Operation ��������
		#pragma region Self Addition �Լ�
		if (type == PLUSPLUS)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = variables[parameterA];

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) + 1);
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) + 1);
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion

		#pragma region Self Subtraction �Լ�
		if (type == MINUSMINUS)
		{
			Value result;

			KString parameterA = GetText(GetChild(subTree, 0));

			if (!IsIDValid(parameterA))
			{
				NewID(parameterA);
			}

			result = variables[parameterA];

			if (variables[parameterA].type == INT && result.type == INT)
			{
				result.value = ToWString(StringToInt(
					variables[parameterA].value) - 1);
			}
			else
			{
				result.value = ToWString(StringToFloat(
					variables[parameterA].value) - 1);
				result.type = REAL;
			}

			variables[parameterA] = result;

			return result;
		}
		#pragma endregion

		#pragma region Addition �ӷ�
		if (type == PLUS)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == STRING || parameterB.type == STRING)
			{
				result.value = parameterA.value + parameterB.value;
				result.type = STRING;
			}
			else if (parameterA.type == INT && parameterB.type == INT)
			{
				result.value = ToWString(StringToInt(
					parameterA.value) + StringToInt(parameterB.value));
				result.type = INT;
			}
			else if (parameterA.type == REAL || parameterB.type == REAL)
			{
				result.value = ToWString(StringToFloat(
					parameterA.value) + StringToFloat(parameterB.value));
				result.type = REAL;
			}		 

			return result;
		}
		#pragma endregion

		#pragma region Subtraction ����
		if (type == MINUS)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
				
			if (GetChildCount(subTree) == 1)
			{
				if (parameterA.type == INT)
				{
					result.value =  ToWString(-StringToInt(parameterA.value));
					result.type = INT;
					return result;
				}
				else
				{
					result.value =  ToWString(-StringToFloat(parameterA.value));
					result.type = REAL;
					return result;
				}
			}
			else
			{
				parameterB = Analyze(GetChild(subTree, 1));

				if (parameterA.type == INT && parameterB.type == INT)
				{
					result.value = ToWString(StringToInt(
						parameterA.value) - StringToInt(parameterB.value));
					result.type = INT;
				}
				else
				{
					result.value = ToWString(StringToFloat(
						parameterA.value) - StringToFloat(parameterB.value));
					result.type = REAL;
				}
			}

			return result;
		}
		#pragma endregion

		#pragma region Multiplication �˷�
		if (type == STAR)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				result.value = ToWString(StringToInt(
					parameterA.value) * StringToInt(parameterB.value));
				result.type = INT;
			}
			else
			{
				result.value = ToWString(StringToFloat(
					parameterA.value) * StringToFloat(parameterB.value));
				result.type = REAL;
			}

			return result;
		}
		#pragma endregion

		#pragma region Division ����
		if (type == DIVIDE)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				result.value = ToWString(StringToInt(
					parameterA.value) / StringToInt(parameterB.value));
				result.type = INT;
			}
			else
			{
				result.value = ToWString(StringToFloat(
					parameterA.value) / StringToFloat(parameterB.value));
				result.type = REAL;
			}

			return result;
		}
		#pragma endregion

		#pragma region Modulus ȡ��
		if (type == MOD)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			result.value = ToWString(StringToInt(
				parameterA.value) % StringToInt(parameterB.value));
			result.type = INT;			

			return result;
		}
		#pragma endregion

		#pragma region Exponentiation ����
		if (type == POWER)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				result.value = ToWString(pow(StringToFloat(
					parameterA.value), StringToInt(parameterB.value)));
				result.type = REAL;
			}
			else
			{
				result.value = ToWString(pow(StringToFloat(
					parameterA.value), StringToFloat(parameterB.value)));
				result.type = REAL;
			}

			return result;
		}
		#pragma endregion
		#pragma endregion

		#pragma region Logical Operation �߼�����
		if (type == AND)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) > 0 &&
					StringToInt(parameterB.value) > 0)
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) > 0 &&
					StringToFloat(parameterB.value) > 0)
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == OR)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) > 0 ||
					StringToInt(parameterB.value) > 0)
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) > 0 ||
					StringToFloat(parameterB.value) > 0)
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == NOT)
		{
			Value result;
			Value parameterA;

			parameterA = Analyze(GetChild(subTree, 0));

			if (parameterA.type == INT)
			{
				if (StringToInt(parameterA.value) > 0)
				{
					result.value = ToWString(0);
				}
				else
				{
					result.value = ToWString(1);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) > 0)
				{
					result.value = ToWString(0);
				}
				else
				{
					result.value = ToWString(1);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == GREATERTHAN)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) >
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) >
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == LESSTHAN)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) <
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) <
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == LESSTHANOREQUALTO)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) <=
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) <=
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == GREATERTHANOREQUALTO)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) >=
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) >=
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == NOTEQUAL1 ||
			type == NOTEQUAL2)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) !=
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) !=
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}

		if (type == EQUALTO)
		{
			Value result;
			Value parameterA;
			Value parameterB;

			parameterA = Analyze(GetChild(subTree, 0));
			parameterB = Analyze(GetChild(subTree, 1));

			if (parameterA.type == INT && parameterB.type == INT)
			{
				if (StringToInt(parameterA.value) ==
					StringToInt(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}
			else
			{
				if (StringToFloat(parameterA.value) ==
					StringToFloat(parameterB.value))
				{
					result.value = ToWString(1);
				}
				else
				{
					result.value = ToWString(0);
				}

				result.type = INT;
			}

			return result;
		}
		#pragma endregion

		#pragma region Conditional Statement �������
		if (type == IF)
		{
			Value parameterA = Analyze(GetChild(subTree, 0));

			if (StringToInt(parameterA.value) > 0)
			{
				int count = GetChildCount(subTree);
				Value result;

				// Skip Else
				if (GetType(GetChild(subTree, count - 1)) == ELSE)
				{
					count -= 1;
				}

				for (int num = 1; num < count; num++)
				{
					result = Analyze(GetChild(subTree, num));

					if (result.type == BREAK || result.type == CONTINUE || isNeedToReturn)
					{
						return result;
					}
				}
			}
			else
			{
				if (GetType(GetChild(subTree, GetChildCount(subTree) - 1)) == ELSE)
				{
					Value result;

					for (int num = 0; num < GetChildCount(
						GetChild(subTree, GetChildCount(subTree) - 1)); num++)
					{
						result = Analyze(GetChild(
							GetChild(subTree, GetChildCount(subTree) - 1), num));

						if (result.type == BREAK || result.type == CONTINUE || isNeedToReturn)
						{
							return result;
						}
					}
				}
			}
		}

		if (type == QUESTION)
		{
			Value result;
			Value parameterA = Analyze(GetChild(subTree, 0));

			if (StringToInt(parameterA.value) > 0)
			{
				Value parameterB = Analyze(GetChild(subTree, 1));
				return parameterB;
			}
			else
			{
				Value parameterC = Analyze(GetChild(subTree, 2));
				return parameterC;
			}
		}
		#pragma endregion

		#pragma region Circulation Statement ѭ�����
		if (type == WHILE)
		{
			while (StringToInt(Analyze(GetChild(subTree, 0)).value) > 0)
			{
				Value result(L"0", INT);

				for (int num = 1; num < GetChildCount(subTree); num++)
				{
					result = Analyze(GetChild(subTree, num));

					if (result.type == BREAK ||
						result.type == CONTINUE ||
						isNeedToReturn)
					{
						break;
					}
				}

				if (result.type == BREAK || isNeedToReturn)
				{
					break;
				}
				else if (result.type == CONTINUE)
				{
					continue;
				}
			}

			return Value(L"0", INT);
		}

		if (type == DO)
		{
			double parameterA = 1;
			do
			{
				Value result(L"0", INT);

				for (int num = 0; num < GetChildCount(subTree) - 1; num++)
				{
					result = Analyze(GetChild(subTree, num));

					if (result.type == BREAK ||
						result.type == CONTINUE || isNeedToReturn)
					{
						break;
					}
				}

				if (result.type == BREAK || isNeedToReturn)
				{
					break;
				}
				else if (result.type == CONTINUE)
				{
					continue;
				}
			} while (StringToInt(Analyze(GetChild(
				subTree, GetChildCount(subTree) - 1)).value) > 0);
		}

		if (type == FOR)
		{
			Value result(L"0", INT);

			KString parameterA = GetText(GetChild(subTree, 0));
			Value parameterB = Analyze(GetChild(subTree, 1));
			Value parameterC = Analyze(GetChild(subTree, 2));

			if (StringToInt(parameterB.value) < 
				StringToInt(parameterC.value))
			{
				for (variables[parameterA] = parameterB;
					StringToInt(variables[parameterA].value) <= 
					StringToInt(parameterC.value);
					variables[parameterA].value = 
						ToWString(StringToInt(
						variables[parameterA].value) + 1))
				{
					for (int num = 3; num < GetChildCount(subTree); num++)
					{
						result = Analyze(GetChild(subTree, num));

						if (result.type == BREAK ||
							result.type == CONTINUE || isNeedToReturn)
						{
							break;
						}
					}

					if (result.type == BREAK || isNeedToReturn)
					{
						break;
					}
					else if (result.type == CONTINUE)
					{
						continue;
					}
				}
			}
			else
			{
				for (variables[parameterA] = parameterB;
					StringToInt(variables[parameterA].value) >= 
					StringToInt(parameterC.value);
				variables[parameterA].value = 
					ToWString(StringToInt(
					variables[parameterA].value) - 1))
				{
					for (int num = 3; num < GetChildCount(subTree); num++)
					{
						result = Analyze(GetChild(subTree, num));

						if (result.type == BREAK ||
							result.type == CONTINUE || isNeedToReturn)
						{
							break;
						}
					}

					if (result.type == BREAK || isNeedToReturn)
					{
						break;
					}
					else if (result.type == CONTINUE)
					{
						continue;
					}
				}
			}
		}
		#pragma endregion

		#pragma region Selection Statement ѡ�����
		if (type == SWITCH)
		{
			double parameterA = StringToFloat(
				Analyze(GetChild(subTree, 0)).value);

			int def = -1;

			bool inCase = false;

			for (int num = 1; num < GetChildCount(subTree); num++)
			{
				pANTLR3_BASE_TREE theChild = GetChild(subTree, num);

				if (GetType(theChild) == DEFAULT)
				{
					def = num;
				}
				else if (GetType(theChild) == CASE)
				{
					if (parameterA == StringToFloat(
						Analyze(GetChild(theChild, 0)).value))
					{
						inCase = true;
						for (int count = 1; count < 
							GetChildCount(theChild); count++)
						{
							if (isNeedToReturn)
							{
								break;
							}

							Analyze(GetChild(theChild, count));
						}
					}
				}
			}

			if (!inCase && def != -1)
			{
				pANTLR3_BASE_TREE theChild = GetChild(subTree, def);
				for (int count = 1; count < GetChildCount(theChild); count++)
				{
					if (isNeedToReturn)
					{
						break;
					}

					Analyze(GetChild(theChild, count));
				}
			}
		}
		#pragma endregion

		#pragma region Jump Operation ��ת����
		if (type == BREAK)
		{
			return Value(L"break", BREAK);
		}

		if (type == CONTINUE)
		{
			return Value(L"continue", CONTINUE);
		}
		#pragma endregion

		#pragma region Extented Statement ��չ���
		if (type == AT)
		{
			Value result(L"0", INT);
			KString name = GetText(GetChild(subTree, 0));

			if (GetChildCount(subTree) > 1 
				&& GetType(GetChild(subTree, 1)) == LCURLY)
			{
				VariableMap commandParts;

				for (int num = 2; num < GetChildCount(subTree); num++)
				{
					KString key = GetText(GetChild(subTree, num));
					Value v = Analyze(GetChild(subTree, ++num));
					commandParts[key] = v;
				}

				if (!isInnerScript)
				{
					functionOrder++;
				}

				result = runner->ExecuteExtendedCommand(this, name, commandParts);
			}
			else if (GetChildCount(subTree) > 1 
				&& GetType(GetChild(subTree, 1)) == LPAREN)
			{
				// If last children are "{" and STRING, then it's a string function
				if (GetType(GetChild(subTree, GetChildCount(subTree) - 1)) == STRING 
					&& GetType(GetChild(subTree, GetChildCount(subTree) - 2)) == LCURLY
					&& GetChildCount(subTree) == 3)
				{
					KString scriptString = Analyze(GetChild(subTree, GetChildCount(subTree) - 1)).value;

					runner->AddUserDefinedFunction(name, new ScriptStringFunction(runner, scriptString));
				}
				else
				{
					runner->AddUserDefinedFunction(name, new UserDefinedMapArgsFunction(runner, this, name));
				}
				
			}
			else if (GetChildCount(subTree) == 1 && runner->IsMapArgsFunctionValid(name))
			{
				VariableMap nil;

				if (!isInnerScript)
				{
					functionOrder++;
				}

				result = runner->ExecuteExtendedCommand(this, name, nil);
			}
			else
			{
				vector<Value> commandParts;
				for (int num = 1; num < GetChildCount(subTree); num++)
				{
					commandParts.push_back(Analyze(GetChild(subTree, num)));
				}	

				if (!isInnerScript)
				{
					functionOrder++;
				}

				result = runner->ExecuteExtendedCommand(this, name, commandParts);
			}		
			
			return result;
		}
		#pragma endregion

		return Value(L"0", INT);
	}

	hash_map<KString, Value, HashString> Script::GetVariableMap()
	{
		return variables;
	}

	bool Script::SetVariableMap( hash_map<KString, Value, HashString> newMap )
	{
		for(hash_map<KString, Value, HashString>::iterator iter = newMap.begin();
			iter != newMap.end(); iter++)
		{
			variables[iter->first] = iter->second;
		}

		return true;
	}

	Script::~Script()
	{
		Unload();
		
		return;
	}

	bool Script::Unload()
	{
		functionOrder = -1;

		if (input)
		{
			((pANTLR3_INPUT_STREAM)input)->free((pANTLR3_INPUT_STREAM)input);
			input = NULL;
		}

		if (lexer)
		{
			((pKScriptLexer)lexer)->free((pKScriptLexer)lexer);
			lexer = NULL;
		}

		if (tstream)
		{
			((pANTLR3_COMMON_TOKEN_STREAM)tstream)->free((pANTLR3_COMMON_TOKEN_STREAM)tstream);
			tstream = NULL;
		}

		if (parser)
		{
			((pKScriptParser)parser)->free((pKScriptParser)parser);
			parser = NULL;
		}

		//if (tree)
		//{
		//	tree->free(tree);
		//	tree = NULL;
		//}

		return true;
	}

	bool Script::UpdateVariableMap( hash_map<KString, Value, HashString> newMap )
	{
		for(hash_map<KString, Value, HashString>::iterator iter = newMap.begin();
			iter != newMap.end(); iter++)
		{
			if (IsIDValid(iter->first))
			{
				variables[iter->first] = iter->second;
			}			
		}

		return true;
	}

	bool Script::ClearVariableMap()
	{
		variables.clear();

		return true;
	}

	KScript::ScriptPtr Script::Copy()
	{
		ScriptPtr copy = new Script(runner, true);

		copy->LoadScriptStream(input->data, (DWORD)input->sizeBuf, fileName);

		return copy;
	}

	pANTLR3_BASE_TREE Script::FindFunctionRoot( KString name , pANTLR3_BASE_TREE subTree)
	{
		if (!subTree)
		{
			return NULL;
		}

		ANTLR3_UINT32 type = INT;

		type = GetType(subTree);

		if (type == AT
			&& GetChildCount(subTree) > 1 
			&& GetType(GetChild(subTree, 1)) == LPAREN
			&& GetText(GetChild(subTree, 0)) == name)
		{
			return subTree;
		}
		else if (GetChildCount(subTree) > 0)
		{
			for (int num = 0; num < GetChildCount(subTree); num++)
			{
				pANTLR3_BASE_TREE result = FindFunctionRoot(name, GetChild(subTree, num));

				if (result)
				{
					return result;
				}
			}
		}

		return NULL;
	}
}