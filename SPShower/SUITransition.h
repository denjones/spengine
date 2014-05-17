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
	void SetType(TransitionType setType);
	void SetCanSkip(bool setSkip);
	float GetTransition();

public:
	SUITransition(void);
	virtual ~SUITransition(void);

	virtual void Update(float timeDelta);
	virtual void Play();
	virtual void Stop();
	virtual void Skip();
	virtual void SetTime(float time);
};


