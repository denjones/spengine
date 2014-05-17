#pragma once
#include "SUIProperties.h"
#include "SUITransition.h"

using namespace SPEngine;

class SUIAnimation : public SUITransition
{
	SUIProperties startPoint;
	SUIProperties endPoint;
	SUIProperties currentPoint;

public:
	void SetStartPoint(SUIProperties setStart);
	void SetEndPoint(SUIProperties setEnd);
	SUIProperties GetCurrentPoint();
	SUIProperties GetTargetPoint();

public:
	SUIAnimation(void);
	virtual ~SUIAnimation(void);

	void Update(float timeDelta);
};

typedef SPPointer<SUIAnimation> SUIAnimationPtr;
