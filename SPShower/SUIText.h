#pragma once
#include <vector>
#include "SUIEffect.h"

using namespace std;
using namespace SPEngine;
using namespace KScript;

class SUIText
{
public:
	MapArgsFunctionPtr	function;
	VariableMap args;
	SPFontPtr	font;
	SPString	text;
	SUIEffectPtr backEffect;
	SUIEffectPtr frontEffect;
	D3DCOLOR	color;

public:
	SUIText(void);
	SUIText(SPString setText);
	SUIText(
		SPString setText, 
		SPFontPtr setFont);
	SUIText(
		SPString setText, 
		SPFontPtr setFont, 
		D3DCOLOR setColor,
		SUIEffectPtr setFrontEffect,
		SUIEffectPtr setBackEffect,
		MapArgsFunctionPtr setFunction, 
		VariableMap setArgs);
	virtual ~SUIText(void);
};

