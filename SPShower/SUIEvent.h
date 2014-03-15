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

	SPPointer<Persistent<Object>> v8Obj;

public:
	SUIEvent();

	EventType type;
	int button;
	int positionX;
	int positionY;
	int movementX;
	int movementY;
	int absoluteX;
	int absoluteY;
	bool returnValue;

	Handle<Object> GetV8Obj();
};

typedef SUIEvent* SUIEventHandle;
typedef SPPointer<SUIEvent> SUIEventPtr;

