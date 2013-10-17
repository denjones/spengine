#pragma once
#include "SPEngine.h"

using namespace SPEngine;

class SUIEvent
{
public:
	enum EventType
	{
		None,
		MouseDown,
		MouseUp,
		MouseClick,
		MouseDClick,
		MouseScrollUp,
		MouseScrollDown,
		MouseMove,
		KeyDown,
		KeyUp,
		KeyPress,		
	};

public:
	SUIEvent();

	EventType type;
	int button;
	int positionX;
	int positionY;
	int movementX;
	int movementY;
};

typedef SPPointer<SUIEvent> SUIEventPtr;

