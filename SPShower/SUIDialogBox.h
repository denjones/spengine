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
	void SetSpeed(float setSpeed);
	float GetSpeed();
	void SetNextLineTex(SPTexturePtr setTex);
	void SetNextPageTex(SPTexturePtr setTex);
	SPTexturePtr GetNextLineTex();
	SPTexturePtr GetNextPageTex();
	bool IsDisplaying();
	bool IsDisplayAllDone();

public:
	SUIDialogBox(SUIScreen* screen);
	virtual ~SUIDialogBox(void);

	virtual void AddText(SUIText text);
	void ForceAddText(SUIText text);
	virtual void Clear();	
	void ForceClear();
	void Clean();
	virtual void Update(float timeDelta);
	virtual void Draw(float timeDelta);
	void Next();
	void Skip();
	bool IsShowNextLineTex();
	bool IsShowNextPageTex();
	void MarkTextToAdd();
	void MarkTextToClear();

	D3DXMATRIX TransformMatrixNext();
	D3DXVECTOR3 PositionNext();

	virtual void LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();

	virtual Handle<Object> GetV8Obj();
	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );

};

typedef SPPointer<SUIDialogBox> SUIDialogBoxPtr;
