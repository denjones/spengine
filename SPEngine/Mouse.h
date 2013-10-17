#pragma once
#include "InputDevice.h"

namespace SPEngine
{
	class InputManager;

	class Mouse : public InputDevice
	{
	public:
		Mouse(void);
		~Mouse(void);

		bool UpdateDevice();

		bool LoadDevice(InputManager* manager, bool exclusive);
		bool Shutdown();

		int ButtonUp(unsigned int key);
		int ButtonDown(unsigned int key);

		int ButtonJustUp(unsigned int key);
		int ButtonJustDown(unsigned int key);

		bool ScollUp();
		bool ScollDown();

		POINT GetMovement();

		POINT GetPosition();
		POINT GetZPosition();

		// Mouse state
		DIMOUSESTATE mouseState;
		DIMOUSESTATE lastMouseState;
		//bool button[3];

		// Mouse x, y, and wheel position.
		int xPos;
		int yPos;
		int wheelPos;

		// Max x (width) and y (height)
		// Restrict means to cap at width/height.
		bool m_restrict;
		int maxWidth;
		int maxHeight;
	};
}
