#pragma once
#include "SUITextSpan.h"

using namespace SPEngine;

class SUITextLine : public vector<SUITextSpanPtr>
{
public:
	float height;
	float width;
	float wordSpace;
	SPFontPtr defaultFont;
	D3DXVECTOR2 currentPosition;

	SUITextLine(float wordSpace, SPFontPtr defaultFont, D3DXVECTOR2 currentPosition);
	~SUITextLine(void);

	void Push(SUIText text);
	float TestPush(SUIText text);
	D3DXVECTOR2 CurrentPosition();
};

typedef SPPointer<SUITextLine> SUITextLinePtr;

