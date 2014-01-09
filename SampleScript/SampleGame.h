#pragma once
#include <SPEngine.h>
#include <v8.h>
#include <map>

using namespace SPEngine;
using namespace std;

class PrintScriptManager : public SPScriptManager
{
public:
	PrintScriptManager(){}
	~PrintScriptManager(){}	
};

void Print4(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	SPString printResult = L"";
	bool first = true;

	for (int i = 0; i < args.Length(); i++) 
	{
		v8::HandleScope handle_scope(args.GetIsolate());
		if (first) 
		{
			first = false;
		} 
		else 
		{
			printResult += L" ";
		}
		printResult += SPV8ScriptEngine::StringToSPString(args[i]->ToString());
	}

	SPFontWriter::GetSingleton().Write(SPFontManager::GetSingleton().GetFont(L"yy_20"), NULL,
		L"Script: " + printResult,
		D3DXVECTOR2(0, 0), SPColor::Magenta, 1, 0, NULL);
}

class Print : public ExtendedArgsFunction
{	
public:
	virtual KScript::KSValue Function(KScript::KSScript* currentScript, vector<KScript::KSValue> args )
	{
		SPFontWriter::GetSingleton().Write(SPFontManager::GetSingleton().GetFont(L"yy_20"), NULL,
			L"Script: " + args[0].value,
			D3DXVECTOR2(0, 0), SPColor::Magenta, 1, 0, NULL);
		return args[0];
	}

};

class Print2 : public ExtendedMapArgsFunction
{	
public:
	virtual KScript::KSValue Function(KScript::KSScript* currentScript, VariableMap args )
	{
		SPFontWriter::GetSingleton().Write(SPFontManager::GetSingleton().GetFont(L"yy_20"), NULL, 
			L"Script: " + args[0].value,
			D3DXVECTOR2(0, 0), SPColor::Magenta, 1, 0, NULL);
		return args[L"text"];
	}

};

class Print3 : public ExtendedMapArgsFunction
{	
public:
	virtual KScript::KSValue Function(KScript::KSScript* currentScript, VariableMap args )
	{
		SPString s = L"Script : " + args[L"头"].value + L"\n" + args[L"值"].value;
		SPFontWriter::GetSingleton().Write(SPFontManager::GetSingleton().GetFont(L"yy_20"), NULL,
			s, D3DXVECTOR2(0, 0), SPColor::Magenta, 1, 0, NULL);
		return args[L"值"];
	}

};

class SampleGame : public SPGame
{
	SPTexturePtr	texture;
	SPFontPtr		font;
	ArgsFunctionPtr		p;
	MapArgsFunctionPtr p2;
	MapArgsFunctionPtr p3;
	PrintScriptManager print;

public:
	SampleGame(HINSTANCE hInstance) : SPGame(hInstance)
	{
	}

	SampleGame(void) : SPGame() 
	{
		texture = NULL; 
		font = NULL;
		p = NULL;
		p2 = NULL;
		p3 = NULL;
	}

	~SampleGame(void) 
	{ 
		p = NULL;
		p2 = NULL;
		p3 = NULL;
	}

	bool LoadContent()
	{
		if(!SPGame::LoadContent())
		{
			return false;
		}

		// Load texture.
		texture = SPTextureManager::GetSingleton().GetTexture(L"sicily.jpg");

		// Load font.
		font = SPFontManager::GetSingleton().CreateFont(L"yy_20", 30, 0, FW_HEAVY, 10, FALSE, L"幼圆");

		// Load function.
		p3 = new Print3();
		p2 = new Print2();
		p = new Print();

		SPV8ScriptEngine::GetSingleton().AddFunction(L"print", Print4);

		// Load script.
		print.Load(L"test.ks");

		// Add print function.
		//print.AddExtension("print", p);
		//print.AddExtension("print", p2);
		print.AddExtension(L"显示", p3);

		SPV8ScriptEngine::GetSingleton().RunScript(L"a = 0;");

		return true;
	}

	bool Draw(float timeDelta)
	{	
		// The following statements are necessary for real time V8 script execution.
		Locker lock(SPV8ScriptEngine::GetSingleton().GetIsolate());
		Isolate::Scope isolateScope(SPV8ScriptEngine::GetSingleton().GetIsolate());		
		HandleScope handleScope(SPV8ScriptEngine::GetSingleton().GetIsolate());
		Handle<Context> context = SPV8ScriptEngine::GetSingleton().GetContext();
		Context::Scope contextScope(context);
		
		// Run the script to get the result.
		Handle<Value> result = SPV8ScriptEngine::GetSingleton().EvalFile(L"test.js", true);
		Handle<String> theResult = result->ToString();

		// Convert the result to an ASCII string and print it.
		SPFontWriter::GetSingleton().WriteCentered(font, NULL, SPV8ScriptEngine::StringToSPString(theResult), D3DXVECTOR2(400,300), SPColor::Wheat, 0, 0, NULL);

		SPSpriteManager3D::GetSingleton().RenderByPosition(texture, NULL, D3DXVECTOR3(0, 0, 0));

		// Execute script.
		print.Execute();		

		return SPGame::Draw(timeDelta);
	}
};

