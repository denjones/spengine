#pragma once
#include "SUIComponentComposite.h"

class SUIList : public SUIComponentComposite
{
public:
	enum ListType
	{
		Vertacal,
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
	SUIList(void);
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
};

typedef SPPointer<SUIList> SUIListPtr;
