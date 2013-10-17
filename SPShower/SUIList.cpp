#include "StdAfx.h"
#include "SUIList.h"
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#include "SUIManager.h"

SUIList::SUIList(void)
{
	maxItemNum = 255;
	scrollPosition = 0;
	type = Vertacal;
	maxLength = 0;
}


SUIList::~SUIList(void)
{
}

bool SUIList::SetScrollPosition( float setPos )
{
	if (setPos < 0)
	{
		setPos = 0;
	}

	if (setPos > 1)
	{
		setPos = 1;
	}

	scrollPosition = setPos;

	return true;
}

float SUIList::GetScrollPosition()
{
	return scrollPosition;
}

bool SUIList::Update( float timeDelta )
{
	SUIComponentComposite::Update(timeDelta);

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}

	return true;
}

bool SUIList::Draw( float timeDelta )
{
	// Render children UI component.
	int currentPos = 0;
	int currentLength = 0;
	maxLength = 0;

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}

	// iter must be assigned after deletion.
	SPComposite::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			if (type == Vertacal)
			{
				maxLength += (*iter)->GetHeight();
			}
			else
			{
				maxLength += (*iter)->GetWidth();
			}

			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	// Get the target length.
	int targetLength;
	if (type == Vertacal)
	{
		targetLength = (maxLength - GetHeight()) * scrollPosition;
	}
	else
	{
		targetLength = (maxLength - GetWidth()) * scrollPosition;
	}

	int selfLength;
	if (type == Vertacal)
	{
		selfLength = GetHeight();
	}
	else
	{
		selfLength = GetWidth();
	}

	if (targetLength < 0)
	{
		targetLength = 0;
	}

	currentPos = -targetLength;


	// Loop through list item.
	iter = children.begin();
	while(iter != children.end())
	{
		int length;
		if (type == Vertacal)
		{
			length = (*iter)->GetHeight();
		}
		else
		{
			length = (*iter)->GetWidth();
		}

		// Check if target in list rectangle.
		if ((!isAbsoluteRender && currentLength + length > targetLength)
			|| ((isAbsoluteRender && currentLength >= targetLength)
			&& (isAbsoluteRender && currentLength + length < targetLength + selfLength)))
		{
			// Get the relative position.
			D3DXVECTOR2 originalPos = (*iter)->GetPosition();
			D3DXVECTOR2 realPos = (*iter)->GetPosition();

			if (type == Vertacal)
			{
				realPos.y += currentPos;
			}
			else
			{
				realPos.x += currentPos;
			}

			// Set real position and render.
			(*iter)->SetPosition(D3DXVECTOR2(realPos.x , realPos.y));
			(*iter)->Render(timeDelta);

			// Reset position.
			(*iter)->SetPosition(originalPos);

			// Update current position.
			if (type == Vertacal)
			{
				currentPos = realPos.y + (*iter)->GetHeight();
				SPComposite::ChildIterator nextIter = iter;
				nextIter++;

				if (currentPos > GetHeight() ||
					(isAbsoluteRender && nextIter != children.end() 
					&& currentPos + (*nextIter)->GetHeight() > GetHeight()))
				{
					break;
				}
			}
			else
			{
				currentPos = realPos.x + (*iter)->GetWidth();
				SPComposite::ChildIterator nextIter = iter;
				nextIter++;

				if (currentPos > GetWidth() ||
					(isAbsoluteRender && nextIter != children.end() 
					&& currentPos + (*nextIter)->GetWidth() > GetWidth()))
				{
					break;
				}
			}
		}
		else
		{
			// Update current length.
			if (type == Vertacal)
			{				
				currentLength += (*iter)->GetHeight();	
				currentPos = currentLength - targetLength;
			}
			else
			{				
				currentLength += (*iter)->GetWidth();
				currentPos = currentLength - targetLength;
			}
		}	

		iter++;
	}	

	return true;
}

bool SUIList::SetDirection( ListType setType )
{
	type = setType;

	return true;
}

SUIList::ListType SUIList::GetDirection()
{
	return type;
}

bool SUIList::SetMaxItemNum( int setNum )
{
	maxItemNum = setNum;

	return true;
}

int SUIList::GetMaxItemNum()
{
	return maxItemNum;
}

bool SUIList::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIList::SaveAsString()
{
	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIL");

	return result;
}

bool SUIList::Scroll( int delta )
{
	float deltaPos = (float)delta / (maxLength - GetHeight());

	SetScrollPosition(scrollPosition + deltaPos);

	return true;
}

bool SUIList::ClearChild()
{
	SPComposite::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			SUIManager::GetSingleton().GetCurrentScreen()->RemoveComponent((*iter)->GetName());
		}

		iter = children.erase(iter);
	}

	return true;
}

bool SUIList::HandleEvent( SUIEventPtr e )
{
	if (!e)
	{
		return true;
	}

	if (e->type == SUIEvent::None)
	{
		return true;
	}

	if(!isDisplay)
	{
		return false;
	}

	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool isEventHandled = false;

	if (inRect && e->type == SUIEvent::MouseScrollUp 
		&& scrollPosition == 0 && onMouseScrollUpMin)
	{
		onMouseScrollUpMin->Function(e);
		isEventHandled = true;
	}

	if (inRect && e->type == SUIEvent::MouseScrollDown 
		&& scrollPosition == 1 && onMouseScrollDownMax)
	{
		onMouseScrollDownMax->Function(e);
		isEventHandled = true;
	}

	if (!isEventHandled)
	{
		return SUIComponentComposite::HandleEvent(e);
	}

	return true;
}
