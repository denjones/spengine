#pragma once

using namespace SPEngine;

class SUIMixMode : public SPEffect
{
public:
	bool SetTarget(SPTexturePtr setTarget);

public:
	SUIMixMode(SPString path);
	SUIMixMode(void);
	virtual ~SUIMixMode(void);
};

typedef SPPointer<SUIMixMode> SUIMixModePtr;
