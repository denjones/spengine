#pragma once

using namespace SPEngine;



class SUITransition : public SPTransition
{
public:
	enum TransitionType
	{
		Normal,
		SlowIn,
		SlowOut,
		SlowInOut,
		FastInOut,
	};

protected:
	bool canSkip;
	TransitionType type;

public:
	bool CanSkip() { return canSkip; }
	bool SetType(TransitionType setType);
	bool SetCanSkip(bool setSkip);
	float GetTransition();

public:
	SUITransition(void);
	virtual ~SUITransition(void);

	virtual bool Update(float timeDelta);
	virtual bool Play();
	virtual bool Stop();
	virtual bool Skip();
	virtual bool SetTime(float time);
};


