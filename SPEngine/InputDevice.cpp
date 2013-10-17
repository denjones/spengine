#include "StdAfx.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "SPComponent.h"
#include "SPGame.h"

using namespace SPEngine;
InputDevice::InputDevice(void)
{
	device = NULL;
	currentManager = NULL;
}

InputDevice::~InputDevice(void)
{
}