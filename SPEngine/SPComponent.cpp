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

	bool SPComponent::Enable()
	{
		isEnabled = true;

		return true;
	}

	bool SPComponent::Disable()
	{
		isEnabled = false;

		return true;
	}

	//bool SPComponent::Register(ComponentManager& manager)
	//{
	//	manager.RegisterComponent(this);

	//	return true;
	//}

	//bool SPComponent::Unregister(ComponentManager& manager)
	//{
	//	manager.UnregisterComponent(this);

	//	return true;
	//}

	bool SPComponent::Load()
	{
		isLoaded = true;

		return true;
	}

	bool SPComponent::Unload()
	{
		return true;
	}

	bool SPComponent::Update( float timeElapsed )
	{
		return true;
	}

	bool SPComponent::Draw( float timeElapsed )
	{
		return true;
	}

	bool SPComponent::PreDraw()
	{
		return true;
	}

	bool SPComponent::PostDraw()
	{
		return true;
	}

	bool SPComponent::Reload()
	{		
		return Load();
	}

	bool SPComponent::Initialize()
	{
		return true;
	}
}