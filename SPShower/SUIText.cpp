#include "StdAfx.h"
#include "SUIText.h"


SUIText::SUIText(void)
{
	font = NULL;
	text = L"";
	color = SPColor::White;
	backEffect = NULL;
	frontEffect = NULL;
}

SUIText::SUIText( 
	SPString setText, 
	SPFontPtr setFont ) 
{
	text = setText;
	font = setFont;
	color = SPColor::White;
	backEffect = NULL;
	frontEffect = NULL;
}

SUIText::SUIText( 
	SPString setText, 
	SPFontPtr setFont, 
	D3DCOLOR setColor,
	SUIEffectPtr setFrontEffect,
	SUIEffectPtr setBackEffect)
{
	text = setText;
	font = setFont;
	color = setColor;
	frontEffect = setFrontEffect;
	backEffect = setBackEffect;
}

SUIText::SUIText( SPString setText )
{
	text = setText;
	font = NULL;
	color = SPColor::White;
	backEffect = NULL;
	frontEffect = NULL;
}


SUIText::~SUIText(void)
{
}
