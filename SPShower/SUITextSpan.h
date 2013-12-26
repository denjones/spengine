#pragma once
#include "SUIText.h"

class SUITextSpan;

typedef SPPointer<SUITextSpan> SUITextSpanPtr;

class SUITextSpan
{
public:
	SUIText text;
	D3DXVECTOR2 position;

	SUITextSpan(SUIText text, D3DXVECTOR2 position)
	{
		this->text = text;
		this->position = position;
	}

	virtual ~SUITextSpan();

	bool StyleEquals(SUIText span);
};


