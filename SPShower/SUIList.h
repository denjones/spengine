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

	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool SetScrollPosition(float setPos);
	float GetScrollPosition();
	bool SetDirection(ListType setType);
	ListType GetDirection();
	bool Scroll(int delta);
	bool SetMaxItemNum(int setNum);
	int GetMaxItemNum();
	bool ClearChild();
	virtual bool HandleEvent(SUIEventPtr e);

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();

	virtual Handle<Object> GetV8Obj();

};

typedef SPPointer<SUIList> SUIListPtr;
