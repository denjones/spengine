//////////////////////////////////////////////////////////////////////////
/// @file		SPTransition.h the header file of base SPTransition class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-30
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "ISPUpdatable.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief TransitionState to represent the state of transition.
	/// 
	//////////////////////////////////////////////////////////////////////
	enum TransitionState
	{
		TransitionOn,
		Active,
		TransitionOff,
		Hidden,
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief SPTransition
	/// A base object component class to represent an object which has 
	/// transition state.
	///
	//////////////////////////////////////////////////////////////////////
	class SPTransition :
		public ISPUpdatable
	{
	protected:
		TransitionState state;
		float transitionOnTime;
		float transitionOffTime;
		float transitionPosition;

		bool isDisplay;

	public:
		/// @name Properties.
		/// @{
		TransitionState State();
		float TransitionOnTime();
		float TransitionPosition();
		float TransitionOffTime();
		/// @}

	public:
		SPTransition(void);
		virtual ~SPTransition(void);

		/// @name Update
		/// @{
		virtual void Update(float timeDelta);

	protected:
		bool UpdateTransition(float timeDelta, int direction);
		/// @}
	};
}


