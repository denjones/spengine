#pragma once
#include "SUITextBox.h"

class SUIDialogBox : public SUITextBox
{
	float displaySpeed;
	float elapsedLastAddTime;
	SUITextList textsToPush;
	bool nextLine;
	bool waitingNextLine;
	bool waitingNextPage;

	SPTexturePtr nextLineTex;
	SPTexturePtr nextPageTex;

	bool isHasTextToAdd;
	bool isHasTextToClear;

public:
	bool SetSpeed(float setSpeed);
	float GetSpeed();
	bool SetNextLineTex(SPTexturePtr setTex);
	bool SetNextPageTex(SPTexturePtr setTex);
	bool IsDisplaying();
	bool IsDisplayAllDone();

public:
	SUIDialogBox(void);
	virtual ~SUIDialogBox(void);

	virtual bool AddText(SUIText text);
	bool ForceAddText(SUIText text);
	virtual bool Clear();	
	bool ForceClear();
	bool Clean();
	virtual bool Update(float timeDelta);
	virtual bool Draw(float timeDelta);
	bool Next();
	bool Skip();
	bool IsShowNextLineTex();
	bool IsShowNextPageTex();
	bool MarkTextToAdd();
	bool MarkTextToClear();

	D3DXMATRIX TransformMatrixNext();
	D3DXVECTOR3 PositionNext();

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

typedef SPPointer<SUIDialogBox> SUIDialogBoxPtr;
