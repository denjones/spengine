#pragma once
#include <vector>
#include "SUIText.h"
#include "SUITextLine.h"
#include "SUIComponent.h"

using namespace std;

struct SUIPadding
{
	float left;
	float right;
	float top;
	float bottom;

	SUIPadding(float top, float right, float bottom, float left)
	{
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}

	SUIPadding()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
};

class SUITextBox : public SUIComponent
{
protected:
	typedef vector<SUIText> SUITextVector;
	typedef SUITextVector::iterator SUITextIterator;
	typedef list<SUIText> SUITextList;
	typedef vector<SUITextLinePtr> SUITextBlock;

	
private:
	//SUITextVector	texts;

protected:
	SPFontPtr		defaultFont;
	SUIPadding		padding;
	float			lineSpace;
	float			wordSpace;
	D3DCOLOR		defaultColor;
	SUIEffectPtr	defaultBackEffect;
	SUIEffectPtr	defaultFrontEffect;
	SPString		punctuations;
	D3DXVECTOR2		currentPosition;
	SUITextBlock	lines;
	bool			isAutoHeight;

public:
	bool IsAutoHeight();
	void SetAutoHeight(bool on);

	float GetLineSpace();
	bool SetLineSpace(float setSpace);

	float GetWordSpace();
	bool SetWordSpace(float setSpace);

	SUIPadding GetPadding();
	bool SetPadding(SUIPadding setPadding);

	float GetPaddingTop();
	void SetPaddingTop(float setTop);

	float GetPaddingRight();
	void SetPaddingRight(float setRight);

	float GetPaddingBottom();
	void SetPaddingBottom(float setTop);

	float GetPaddingLeft();
	void SetPaddingLeft(float setRight);

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

public:
	SUITextBox(SUIScreen* screen);
	virtual ~SUITextBox(void);

	void RefreshText();
	virtual bool AddText(SUIText text);	
	virtual bool Clear();
	void NewLine();
	void AddTextDirectly(SUITextSpanPtr textSpan);
	D3DXVECTOR2 CurrentPosition();
	SUITextLinePtr CurrentLine();
	bool WillExceeded(float length);
	bool WillCurrentLineExceeded(float addedLength);
	SPString GetContent();

	virtual bool Update(float timeDelta);
	virtual bool Draw(float timeDelta);

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
	virtual Handle<Object> GetV8Obj();

private:
	bool IsPunctuation(SPString character);
	bool IsAlphabet(SPString character);
};

typedef SPPointer<SUITextBox> SUITextBoxPtr;
