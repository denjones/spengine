#include "StdAfx.h"
#include "SUIList.h"
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#include "SUIManager.h"
#include "SV8ScriptManager.h"

SUIList::SUIList(SUIScreen* screen) : SUIComponent(screen)
{
	maxItemNum = 255;
	scrollPosition = 0;
	type = Vertical;
	maxLength = 0;
}


SUIList::~SUIList(void)
{
}

void SUIList::SetScrollPosition( float setPos )
{
	modificationLock.Lock();

	if (setPos < 0)
	{
		setPos = 0;
	}

	if (setPos > 1)
	{
		setPos = 1;
	}

	scrollPosition = setPos;

	modificationLock.Unlock();
}

float SUIList::GetScrollPosition()
{
	return scrollPosition;
}

void SUIList::Update( float timeDelta )
{
	SUIComponent::Update(timeDelta);

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton()->GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}
}

void SUIList::Draw( float timeDelta )
{
	// Render children UI component.
	int currentPos = 0;
	int currentLength = 0;
	maxLength = 0;

	// Keep list in size.
	while(children.size() > maxItemNum)
	{
		children.front()->SetFather(NULL);
		SUIManager::GetSingleton()->GetCurrentScreen()->RemoveComponent(children.front()->GetName());
		children.pop_front();
	}

	// iter must be assigned after deletion.
	SUIComponent::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			if (type == Vertical)
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
	if (type == Vertical)
	{
		targetLength = (maxLength - GetHeight()) * scrollPosition;
	}
	else
	{
		targetLength = (maxLength - GetWidth()) * scrollPosition;
	}

	int selfLength;
	if (type == Vertical)
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
		if (type == Vertical)
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

			if (type == Vertical)
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
			if (type == Vertical)
			{
				currentPos = realPos.y + (*iter)->GetHeight();
				SUIComponent::ChildIterator nextIter = iter;
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
				SUIComponent::ChildIterator nextIter = iter;
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
			if (type == Vertical)
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
}

void SUIList::SetDirection( ListType setType )
{
	modificationLock.Lock();
	type = setType;
	modificationLock.Unlock();
}

SUIList::ListType SUIList::GetDirection()
{
	return type;
}

void SUIList::SetMaxItemNum( int setNum )
{
	modificationLock.Lock();
	maxItemNum = setNum;
	modificationLock.Unlock();
}

int SUIList::GetMaxItemNum()
{
	return maxItemNum;
}

void SUIList::LoadFromString( SPString stringStream )
{
}

SPString SUIList::SaveAsString()
{
	//SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIL");

	//return result;

	return L"";
}

void SUIList::Scroll( int delta )
{
	float deltaPos = (float)delta / (maxLength - GetHeight());
	SetScrollPosition(scrollPosition + deltaPos);
}

void SUIList::ClearChild()
{
	modificationLock.Lock();

	SUIComponent::ChildIterator iter = children.begin();

	// Calculate max length.
	while(iter != children.end())
	{
		if (*iter)
		{
			SUIManager::GetSingleton()->GetCurrentScreen()->RemoveComponent((*iter)->GetName());
		}

		iter = children.erase(iter);
	}

	modificationLock.Unlock();
}

void SUIList::HandleEvent( SUIEventPtr e )
{
	//if (!e)
	//{
	//	return true;
	//}

	//if (e->type == SUIEvent::None)
	//{
	//	return true;
	//}

	//if(!isDisplay)
	//{
	//	return false;
	//}

	//bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	//bool isEventHandled = false;

	//if (inRect && e->type == SUIEvent::MouseScrollUp 
	//	&& scrollPosition == 0 && onMouseScrollUpMin)
	//{
	//	onMouseScrollUpMin->Function(e);
	//	isEventHandled = true;
	//}

	//if (inRect && e->type == SUIEvent::MouseScrollDown 
	//	&& scrollPosition == 1 && onMouseScrollDownMax)
	//{
	//	onMouseScrollDownMax->Function(e);
	//	isEventHandled = true;
	//}

	//if (!isEventHandled)
	//{
	//	return SUIComponent::HandleEvent(e);
	//}

	//return true;

	SUIComponent::HandleEvent(e);
}

Handle<Object> SUIList::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetScrollTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}

Handle<Object> SUIList::SaveAsObj()
{
	Handle<Object> result = SUIComponent::SaveAsObj();
	result->Set(SPV8ScriptEngine::SPStringToString(L"type"), SPV8ScriptEngine::SPStringToString(L"scroll"));
	return result;
}
