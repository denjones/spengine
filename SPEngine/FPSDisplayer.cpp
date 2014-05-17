//////////////////////////////////////////////////////////////////////////
/// @file		FPSDisplayer.cpp the implement file of FPSDisplayer class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-15
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "FPSDisplayer.h"
#include "SPColorHelper.h"
#include "SPGame.h"
#include "SPStringHelper.h"
#include "SPGameManager.h"
#include "SPConfigManager.h"
#include "SPFontWriter.h"
#include "SPFontManager.h"

using namespace SPEngine;

FPSDisplayer::FPSDisplayer(void) : SPComponent()
{
	fps = 0;
	frameCount = 0;
	elapsedCountTime = 0;
	location = RightBottom;
}

FPSDisplayer::~FPSDisplayer(void)
{
}

void FPSDisplayer::Update( float timeElapsed )
{
	frameCount++;
	elapsedCountTime += timeElapsed;

	if(elapsedCountTime >= 1)
	{
		fps = frameCount / elapsedCountTime;
		elapsedCountTime = 0;
		frameCount = 0;
	}
}

void FPSDisplayer::Draw( float timeElapsed )
{
	SPString text = L"FPS: " + SPStringHelper::ToWString((int)fps);
	D3DXVECTOR2 position;
	D3DXVECTOR2 size = font->GetTextSize(text, 0);

	switch(location)
	{
	case LeftTop:
		position = D3DXVECTOR2(0, 0);
		SPFontWriter::GetSingleton()->Write(font, NULL, text, position, SPColor::Yellow, 0, 0, NULL);
		break;

	case LeftBottom:
		position = D3DXVECTOR2(0,
			(float)SPConfigManager::GetSingleton()->GetCurrentConfig().
			workingHeight - font->GetHeight());
		SPFontWriter::GetSingleton()->Write(font, NULL, text, position, SPColor::Yellow, 0, 0, NULL);
		break;

	case RightTop:
		position = D3DXVECTOR2(
			(float)SPConfigManager::GetSingleton()->GetCurrentConfig().
			workingWidth - size.x, 0);
		SPFontWriter::GetSingleton()->Write(font, NULL, text, SPRectangle((int)position.x, (int)position.y, 
			(int)size.x, (int)size.y),
			(TextFormat)(Top|Right),SPColor::Yellow, 0, 0, NULL);
		break;

	case RightBottom:
		position = D3DXVECTOR2((float)SPConfigManager::GetSingleton()->
			GetCurrentConfig().workingWidth - size.x,
			(float)(SPConfigManager::GetSingleton()->GetCurrentConfig().
			workingHeight - font->GetHeight()));
		SPFontWriter::GetSingleton()->Write(font, NULL, text, SPRectangle((int)position.x, (int)position.y, 
			(int)size.x, (int)size.y),
			(TextFormat)(Top|Right),SPColor::Yellow, 0, 0, NULL);
		break;
	}
}

void FPSDisplayer::Load()
{
	font = SPFontManager::GetSingleton()->GetFont(L"yh_20");
}

void FPSDisplayer::Initialize()
{
	font = SPFontManager::GetSingleton()->CreateFont(L"yh_20", 20, 0, FW_BOLD, 99, false, L"Î¢ÈíÑÅºÚ");
}

void FPSDisplayer::Unload()
{
	font = NULL;
}

void SPEngine::FPSDisplayer::SetLocation( FPSLocation setLocation )
{
	location = setLocation;
}

SPEngine::FPSLocation SPEngine::FPSDisplayer::GetLocation()
{
	return location;
}
