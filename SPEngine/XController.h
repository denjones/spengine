#pragma once
#include <XInput.h>
#include <d3dx9math.h>

namespace SPEngine
{
	class XController
	{
		int num;
		bool isConnected;
		float magnitudeLeft;
		float magnitudeRight;
		float lX;
		float lY;
		float rX;
		float rY;

	public:
		XController(void);
		XController(int setNum);
		~XController(void);

		int Num();

		bool ButtonUp(WORD button);
		bool ButtonDown(WORD button);

		bool ButtonJustDown(WORD button);
		bool ButtonJustUp(WORD button);

		XINPUT_STATE xState;
		XINPUT_STATE lastXState;

		bool UpdateDevice();
		bool IsConnected();
		float MagnitudeLeft();
		float MagnitudeRight();
		D3DXVECTOR2 LeftPosition();
		D3DXVECTOR2 RightPostion();
		bool SetVibration(int left, int right);

		bool Reset();
	};
}

