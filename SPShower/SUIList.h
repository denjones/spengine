#pragma once
#include "SUIComponent.h"

class SUIList : public SUIComponent
{
public:
	enum ListType
	{
		Vertical,
		Horizontal,
	};

	SUIEventHandlerPtr onMouseScrollUpMin;
	SUIEventHandlerPtr onMouseScrollDownMax;

protected:
	ListType type;
	float scrollPosition;
	int maxItemNum;
	int maxLength;

public:
	SUIList(SUIScreen* screen);
	virtual ~SUIList(void);

	void Update(float timeDelta);
	void Draw(float timeDelta);
	void SetScrollPosition(float setPos);
	float GetScrollPosition();
	void SetDirection(ListType setType);
	ListType GetDirection();
	void Scroll(int delta);
	void SetMaxItemNum(int setNum);
	int GetMaxItemNum();
	void ClearChild();
	virtual void HandleEvent(SUIEventPtr e);

	virtual void LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();

	virtual Handle<Object> GetV8Obj();

};

typedef SPPointer<SUIList> SUIListPtr;
