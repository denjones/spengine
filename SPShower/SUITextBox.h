#pragma once
#include <vector>
#include "SUIText.h"
#include "SUIComponentComposite.h"

using namespace std;

class SUITextBox : public SUIComponentComposite
{
protected:
	struct TextSpan
	{
	public:
		SUIText text;
		SRectangle rect;

		TextSpan(SUIText setText, SRectangle setRect)
		{
			text = setText;
			rect = setRect;
		}
	};

	typedef vector<SUIText> SUITextVector;
	typedef SUITextVector::iterator SUITextIterator;
	typedef vector<TextSpan> TextBlock;
	typedef list<SUIText> SUITextList;

	SPFontPtr	defaultFont;
	SUITextVector texts;
	D3DXVECTOR4 padding;
	float		lineSpace;
	float		wordSpace;
	TextBlock	linesResult;
	D3DCOLOR	defaultColor;
	SUIEffectPtr defaultBackEffect;
	SUIEffectPtr defaultFrontEffect;
	SPString	punctuations;

public:
	bool SetLineSpace(float setSpace);
	bool SetWordSpace(float setSpace);
	bool SetPadding(D3DXVECTOR4 setPadding);
	SRectangle GetTextRect();
	bool SetDefaultFont(SPFontPtr setFont);
	bool SetDefaultColor(D3DCOLOR setColor);
	D3DCOLOR GetDefaultColor();
	bool SetPunctuations(SPString setPun);
	bool SetDefaultBackEffect(SUIEffectPtr setEffect);
	bool SetDefaultFrontEffect(SUIEffectPtr setEffect);
	SPFontPtr GetDefaultFont();

	D3DXMATRIX TransformMatrixText();
	D3DXVECTOR3 PositionText();
	D3DXVECTOR3 PositionTextBG();
	//add
	bool ApplyText();

public:
	SUITextBox(void);
	virtual ~SUITextBox(void);

	virtual bool AddText(SUIText text);	
	virtual bool Clear();
	virtual bool Update(float timeDelta);
	virtual bool Draw(float timeDelta);

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

typedef SPPointer<SUITextBox> SUITextBoxPtr;
