//////////////////////////////////////////////////////////////////////////
/// @file		SPSprite.cpp the implement file of SPSprite class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPSprite.h"
#include "SPColorHelper.h"


using namespace SPEngine;

SPSprite::SPSprite(void)
{
	effect = NULL;
	color = SPColor::White;
	renderTarget = NULL;
	depth = 1;
	texture = NULL;
}

SPSprite::~SPSprite(void)
{
}