#include "StdAfx.h"
#include "SUITextSpan.h"



SUITextSpan::~SUITextSpan(void)
{
}

bool SUITextSpan::StyleEquals( SUIText text )
{
	return this->text.font == text.font && 
		this->text.color == text.color && 
		this->text.backEffect == text.backEffect && 
		this->text.frontEffect == text.frontEffect;
}
