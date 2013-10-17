#include "StdAfx.h"
#include "FontManager.h"
#include "SPGame.h"

using namespace SPEngine;

FontManager::FontManager(void)
{
	Renderer = NULL;
	currentGame = NULL;
}


FontManager::~FontManager(void)
{
	if (Renderer)
	{
		Renderer->Release();
	}	
}

LPDIRECT3DDEVICE9 FontManager::GetDevice()
{
	return currentGame->GetDevice();
}

bool FontManager::Load()
{
	if(FAILED(D3DXCreateSprite(currentGame->GetDevice(), &Renderer)))
	{
		return false;
	}

	return true;
}

bool FontManager::Unload()
{
	if (Renderer)
	{
		Renderer->Release();
		Renderer = NULL;
	}	

	return true;
}

FontManager::FontManager( SPGame* game )
{
	Register(game);
}

bool FontManager::Initialize()
{	
	return true;
}

bool FontManager::AddFont(SPFont* font)
{
	fonts.push_back(font);

	return true;
}

bool FontManager::Update(float timeDelte)
{
	return true;
}

bool FontManager::Draw(float timeDelte)
{
	Renderer->Begin(D3DXSPRITE_ALPHABLEND);

	foreach(TextToWrite, text, list<TextToWrite>, texts)
	{
		WriteText(text);
	}

	Renderer->End();

	texts.clear();

	return true;
}

bool FontManager::WriteText( TextToWrite text )
{
	text.font->Font->DrawTextA(Renderer,
		text.text.c_str(),text.count,&text.desRect.CRect(),
		text.format,text.color);

	return true;
}

bool FontManager::AddTextToWrite(
	SPFont*	font,
	string		text,
	int			count,
	SPRectangle destRect,
	TextFormat	format,
	D3DCOLOR	color)
{
	texts.push_back(TextToWrite(
		font, text, count, destRect, format, color));

	return true;
}

SPFont* FontManager::GetFont(int num)
{
	return fonts[num];
}