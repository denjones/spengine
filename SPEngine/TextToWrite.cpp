#include "StdAfx.h"
#include "TextToWrite.h"
#include "ColorHelper.h"

using namespace SPEngine;

TextToWrite::TextToWrite(void)
{
	font = NULL;
	text = "";
	desRect = SPRectangle(0, 0, 0, 0);
	color = Color::White;
	format = Top;
	count = -1;
}


TextToWrite::~TextToWrite(void)
{
}


TextToWrite::TextToWrite( SPFont* setFont, string setText,
	int setCount, SPRectangle setDesRect, 
	TextFormat setFormat, D3DCOLOR setColor )
{
	font = setFont;
	text = setText;
	desRect = setDesRect;
	color = setColor;
	format = setFormat;
	count = setCount;
}
