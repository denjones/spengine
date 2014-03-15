#pragma once
#include <vector>
#include "SUIEffect.h"

using namespace std;
using namespace SPEngine;

class SUIText
{
public:
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
		SUIEffectPtr setBackEffect);
	virtual ~SUIText(void);
};

