#pragma once

namespace SPEngine
{
	enum UIState
	{
		TransitionOn,
		Active,
		TransitionOff,
		Hidden,
	};

	class UIComponent
	{
	protected:
		UIState state;
		float transitionOnTime;
		float transitionOffTime;
		float transitionPosition;

		bool isDisplay;

	public:
		UIComponent(void);
		~UIComponent(void);

		virtual bool Load() = 0;
		virtual bool Unload() = 0;
		virtual bool Update(float timeDelta);
		virtual bool Draw(float timeDelta) = 0;
		virtual bool Initialize() = 0;

		UIState State();
		float TransitionOnTime();
		float TransitionPosition();
		float TransitionOffTime();
		bool UpdateTransition(float timeDelta, int direction);
	};
}


