#pragma once
#include <SPEngine.h>

using namespace SPEngine;

class PrintScriptManager : public SPScriptManager
{
public:
	PrintScriptManager(){}
	~PrintScriptManager(){}	
};

class Print : public ExtendedArgsFunction
{	
public:
	virtual Value Function(KScript::Script* currentScript, vector<Value> args )
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
	virtual Value Function(KScript::Script* currentScript, VariableMap args )
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
	virtual Value Function(KScript::Script* currentScript, VariableMap args )
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
	SampleGame(HINSTANCE hInstance) : SPGame(hInstance) {}

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

		// Load script.
		print.Load(L"test.ks");

		// Add print function.
		//print.AddExtension("print", p);
		//print.AddExtension("print", p2);
		print.AddExtension(L"显示", p3);

		return true;
	}

	bool Draw(float timeDelta)
	{		
		// Using 3D sprite manager.

		SPFontWriter::GetSingleton().WriteCentered(font, NULL, L"哈哈", D3DXVECTOR2(400,300), SPColor::Wheat, 1, 0, NULL);

		SPSpriteManager3D::GetSingleton().RenderByPosition(texture, NULL, D3DXVECTOR3(0, 0, 0));

		// Execute script.
		print.Execute();

		return SPGame::Draw(timeDelta);
	}
};

