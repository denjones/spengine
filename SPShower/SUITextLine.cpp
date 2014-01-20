#include "StdAfx.h"
#include "SUITextLine.h"


SUITextLine::SUITextLine(float wordSpace, SPFontPtr defaultFont, D3DXVECTOR2 currentPosition)
{
	this->height = 0;
	this->width = 0;
	this->wordSpace = wordSpace;
	this->defaultFont = defaultFont;
	this->currentPosition = currentPosition;
}


SUITextLine::~SUITextLine(void)
{
}

void SUITextLine::Push( SUIText text )
{
	modificationLock.Lock();

	//
	// Get Text Size
	//

	SPFontPtr font = text.font ? text.font : defaultFont;
	D3DXVECTOR2 size = font->GetTextSize(L"a" + text.text + L"a", wordSpace);
	float wordSpaceInPixel = size.y * wordSpace;
	size.x -= 2 * (font->GetTextSize(L"a", wordSpace).x + wordSpaceInPixel);

	if (this->size() == 0)
	{
		//
		// If the line is empty, just add new text span.
		//

		this->push_back(new SUITextSpan(text, currentPosition));
		width = size.x;
		height = size.y;
		currentPosition.x += size.x + wordSpaceInPixel;
	}
	else
	{
		//
		// Get last text span size
		//

		SUITextSpanPtr lastSpan = this->back();
		SPFontPtr lastFont = lastSpan->text.font ? lastSpan->text.font : defaultFont;
		D3DXVECTOR2 lastSize = lastFont->GetTextSize(L"a" + lastSpan->text.text + L"a", wordSpace);
		float lastWordSpaceInPixel = lastSize.y * wordSpace;
		lastSize.x -= 2 * (lastFont->GetTextSize(L"a", wordSpace).x + lastWordSpaceInPixel);

		if(	lastSpan->StyleEquals(text))
		{
			//
			// If style equal, add text to last text span.
			//

			lastSpan->text.text += text.text;
			D3DXVECTOR2 newSize = lastFont->GetTextSize(L"a" + lastSpan->text.text + L"a", wordSpace);
			newSize.x -= 2 * (lastFont->GetTextSize(L"a", wordSpace).x + lastWordSpaceInPixel);
			currentPosition.x -= width;
			width += newSize.x - lastSize.x;
			currentPosition.x += width;
		}
		else
		{
			//
			// Style different, add new text span.
			//

			this->push_back(new SUITextSpan(text, currentPosition));
			width += lastWordSpaceInPixel + size.x;
			currentPosition.x += size.x + wordSpaceInPixel;

			if (size.y > height)
			{
				height = size.y;
			}
		}
	}

	modificationLock.Unlock();
}

float SUITextLine::TestPush( SUIText text )
{
	SPFontPtr font = text.font ? text.font : defaultFont;
	D3DXVECTOR2 size = font->GetTextSize(L"a" + text.text + L"a", wordSpace);
	float wordSpaceInPixel = size.y * wordSpace;
	size.x -= 2 * (font->GetTextSize(L"a", wordSpace).x + wordSpaceInPixel);

	if (this->size() == 0)
	{
		return size.x;
	}
	else
	{
		SUITextSpanPtr lastSpan = this->back();
		SPFontPtr lastFont = lastSpan->text.font ? lastSpan->text.font : defaultFont;
		D3DXVECTOR2 lastSize = lastFont->GetTextSize(L"a" + lastSpan->text.text + L"a", wordSpace);
		float lastWordSpaceInPixel = lastSize.y * wordSpace;
		lastSize.x -= 2 * (lastFont->GetTextSize(L"a", wordSpace).x + lastWordSpaceInPixel);

		if(	lastSpan->StyleEquals(text))
		{
			D3DXVECTOR2 newSize = lastFont->GetTextSize(L"a" + lastSpan->text.text + text.text + L"a", wordSpace);
			newSize.x -= 2 * (lastFont->GetTextSize(L"a", wordSpace).x + lastWordSpaceInPixel);
			return width + newSize.x - lastSize.x;
		}
		else
		{
			float lastWordSpaceInPixel = lastSize.y * wordSpace;
			return width + lastWordSpaceInPixel + size.x;
		}
	}
}

D3DXVECTOR2 SUITextLine::CurrentPosition()
{
	return currentPosition;
}

void SUITextLine::Lock()
{
	modificationLock.Lock();
}

void SUITextLine::Unlock()
{
	modificationLock.Unlock();
}