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
	bool			isAnonymousFont;
	SUITextList	textToAdd;

public:
	bool IsAutoHeight();
	void SetAutoHeight(bool on);

	float GetLineSpace();
	void SetLineSpace(float setSpace);

	float GetWordSpace();
	void SetWordSpace(float setSpace);

	SUIPadding GetPadding();
	void SetPadding(SUIPadding setPadding);

	float GetPaddingTop();
	void SetPaddingTop(float setTop);

	float GetPaddingRight();
	void SetPaddingRight(float setRight);

	float GetPaddingBottom();
	void SetPaddingBottom(float setTop);

	float GetPaddingLeft();
	void SetPaddingLeft(float setRight);

	SRectangle GetTextRect();

	void SetDefaultFont(SPFontPtr setFont, bool isAnonymous = false);
	SPFontPtr GetDefaultFont();

	bool IsAnonymousFont();

	void SetDefaultColor(D3DCOLOR setColor);
	D3DCOLOR GetDefaultColor();

	void SetPunctuations(SPString setPun);

	void SetDefaultBackEffect(SUIEffectPtr setEffect);
	SUIEffectPtr GetDefaultBackEffect();

	void SetDefaultFrontEffect(SUIEffectPtr setEffect);
	SUIEffectPtr GetDefaultFrontEffect();

	

	D3DXMATRIX TransformMatrixText();
	D3DXVECTOR3 PositionText();
	D3DXVECTOR3 PositionTextBG();

public:
	SUITextBox(SUIScreen* screen);
	virtual ~SUITextBox(void);

	virtual void RefreshText();
	virtual void AddText(SUIText text);	
	virtual void AddTextWithoutLock(SUIText text);	
	virtual void Clear();
	virtual void NewLine();
	//virtual bool AddTextDirectly(SUITextSpanPtr textSpan);
	D3DXVECTOR2 CurrentPosition();
	SUITextLinePtr CurrentLine();
	bool WillExceeded(float length);
	bool WillCurrentLineExceeded(float addedLength);
	SPString GetContent();

	virtual void Update(float timeDelta);
	virtual void Draw(float timeDelta);
	virtual void Unload();
	virtual void Reload();

	virtual void LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
	virtual Handle<Object> GetV8Obj();
	virtual Handle<Object> SaveAsObj();

private:
	bool IsPunctuation(SPString character);
	bool IsAlphabet(SPString character);
};

typedef SPPointer<SUITextBox> SUITextBoxPtr;
