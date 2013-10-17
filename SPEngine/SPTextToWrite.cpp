//////////////////////////////////////////////////////////////////////////
/// @file		SPTextToWrite.cpp the implement file of SPTextToWrite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPTextToWrite.h"
#include "SPColorHelper.h"

namespace SPEngine
{
	SPTextToWrite::SPTextToWrite(void)
	{
		font = NULL;
		pixelShader = NULL;
		text = L"";
		desRect = SPRectangle(0, 0, 0, 0);
		color = SPColor::White;
		format = Top;
		count = -1;
		depth = 1;
		target = NULL;
		wordSpace = 0;
	}


	SPTextToWrite::~SPTextToWrite(void)
	{
	}


	SPTextToWrite::SPTextToWrite( SPFontPtr setFont, SPEffectPtr setPS, wstring setText,
		int setCount, SPRectangle setDesRect, 
		TextFormat setFormat, D3DCOLOR setColor,float setSpace, float setDepth, SPTexturePtr setTarget )
	{
		font = setFont;
		pixelShader = setPS;
		text = setText;
		desRect = setDesRect;
		color = setColor;
		format = setFormat;
		count = setCount;
		depth = setDepth;
		target = setTarget;
		wordSpace = setSpace;
	}
}

