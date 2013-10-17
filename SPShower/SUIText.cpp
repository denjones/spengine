#include "StdAfx.h"
#include "SUIText.h"


SUIText::SUIText(void)
{
	function = NULL;
	args.clear();
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
	function = NULL;
	args.clear();
	color = SPColor::White;
	backEffect = NULL;
	frontEffect = NULL;
}

SUIText::SUIText( 
	SPString setText, 
	SPFontPtr setFont, 
	D3DCOLOR setColor,
	SUIEffectPtr setFrontEffect,
	SUIEffectPtr setBackEffect,
	MapArgsFunctionPtr setFunction,
	VariableMap setArgs )
{
	text = setText;
	font = setFont;
	color = setColor;
	frontEffect = setFrontEffect;
	backEffect = setBackEffect;
	function = setFunction;
	args = setArgs;
}

SUIText::SUIText( SPString setText )
{
	text = setText;
	function = NULL;
	args.clear();
	font = NULL;
	color = SPColor::White;
	backEffect = NULL;
	frontEffect = NULL;
}


SUIText::~SUIText(void)
{
}
