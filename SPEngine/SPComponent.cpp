//////////////////////////////////////////////////////////////////////////
/// @file		SPComponent.cpp the implement file of SPComponent class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-15
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPComponent.h"
#include "SPGame.h"

namespace SPEngine
{
	SPComponent::SPComponent(void)
	{
		isEnabled = false;
		isInitialized = false;
		isLoaded = false;
	}

	SPComponent::~SPComponent(void)
	{
	}

	void SPComponent::Enable()
	{
		isEnabled = true;
	}

	void SPComponent::Disable()
	{
		isEnabled = false;
	}

	void SPComponent::Load()
	{
		isLoaded = true;
	}

	void SPComponent::Unload()
	{
	}

	void SPComponent::Update( float timeElapsed )
	{
	}

	void SPComponent::Draw( float timeElapsed )
	{
	}

	void SPComponent::PreDraw()
	{
	}

	void SPComponent::PostDraw()
	{
	}

	void SPComponent::Reload()
	{		
		Load();
	}

	void SPComponent::Initialize()
	{
	}
}