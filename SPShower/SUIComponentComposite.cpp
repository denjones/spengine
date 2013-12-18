#include "StdAfx.h"
#include "SUIComponentComposite.h"


SUIComponentComposite::SUIComponentComposite(void)
{
}


SUIComponentComposite::~SUIComponentComposite(void)
{
}

bool SUIComponentComposite::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	UpdateAnimation(timeDelta);

	UpdateEffect(timeDelta);

	SPComposite::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		(*iter)->Update(timeDelta);

		iter++;
	}
	
	return true;
}

bool SUIComponentComposite::Draw( float timeDelta )
{	
	// Render children UI component.
	SPComposite::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->Render(timeDelta);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	return true;
}

bool SUIComponentComposite::AddChild( SUIComponentPtr newChild )
{
	ChildIterator iter = children.begin();

	if (iter == children.end())
	{
		children.push_back(newChild);
		return true;
	}

	ChildIterator iterNext = iter;
	iterNext++;

	if (newChild->GetLayer() < (*iter)->GetLayer())
	{
		children.push_front(newChild);
	}
	else
	{
		while(iterNext != children.end())
		{
			if ((*iter)->GetLayer() <= newChild->GetLayer()	&& newChild->GetLayer() < (*iterNext)->GetLayer())
			{
				break;
			}

			iter++;
			iterNext++;
		}

		children.insert(iterNext, newChild);
	}

	return true;
}

bool SUIComponentComposite::PreDraw()
{
	// Create render target to be rendered by children.
	if (!isAbsoluteRender)
	{
		childTarget = SPTextureManager::GetSingleton().
			CreateRenderTarget(GetWidth(), GetHeight(), properties.backgroundColor);
	}
	else
	{
		childTarget = ChildTarget();
	}

	// A card problem ?
	//childTarget->Fill(properties.backgroundColor);

	SPRectangle destRect = properties.rectangle;
	destRect.X = 0;
	destRect.Y = 0;

	// Render background color and image.
	SPTexturePtr backgroundColorTex = SPTextureManager::GetSingleton().GetBlankWhiteTexture();	

	//SPSpriteManager::GetSingleton().RenderOnScreen(backgroundColorTex,
	//	NULL, destRect, properties.backgroundColor, 1, childTarget);
	float alpha = Alpha();
	D3DCOLOR realColor = alpha * (D3DXCOLOR)properties.backgroundColor;

	SPSpriteManager::GetSingleton().RenderWithMatrix(backgroundColorTex,
		isAbsoluteRender?GetCurrentEffect():NULL, TransformMatrixColor(), 
		D3DXVECTOR3(0,0,0), PositionColor(), realColor, childTarget);

	if (properties.backgroundImage)
	{
		D3DXVECTOR3 positionBG = PositionBG();
		//SPSpriteManager::GetSingleton().RenderOnScreen(properties.backgroundImage,
		//	NULL, GetBackgroundRect(), SPColor::White, 1, childTarget);
		SPSpriteManager::GetSingleton().RenderWithMatrix(properties.backgroundImage,
			isAbsoluteRender?GetCurrentEffect():NULL, TransformMatrixBG(),
			BackgroundSrcRect().CRect(), D3DXVECTOR3(0,0,0), positionBG, 
			alpha * (D3DXCOLOR)SPColor::White, childTarget);
	}	

	SPComposite::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->SetRenderTarget(childTarget);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	return true;
}

bool SUIComponentComposite::PostDraw()
{
	SPComposite::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->SetRenderTarget(NULL);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	if (childTarget && !isAbsoluteRender)
	{
		SPSpriteManager::GetSingleton().RenderWithRotation(
			childTarget, 
			GetCurrentEffect(), 
			D3DXVECTOR3(GetPosition().x, GetPosition().y, Depth()),
			properties.rotationCenter,
			properties.rotation,
			properties.transparency * SPColor::White,
			renderTarget);
	}

	//childTarget = NULL;

	return true;
}

bool SUIComponentComposite::Reload()
{
	return Load();
}

bool SUIComponentComposite::Load()
{
	return true;
}

bool SUIComponentComposite::Unload()
{
	childTarget = NULL;
	renderTarget = NULL;

	return true;
}

bool SUIComponentComposite::Skip()
{
	while (animations.size() > 0)
	{
		if (animations.front() && !animations.front()->CanSkip())
		{
			//animations.front()->SetStartPoint(properties);
			//properties = animations.front()->GetCurrentPoint();

			break;
		}
		else if (animations.front() && animations.size() == 1)
		{
			properties = animations.front()->GetTargetPoint();
		}

		animations.pop_front();
	}

	//if (animations.size() > 0)
	//{
	//	if (animations.back())
	//	{
	//		animations.back()->Skip();
	//		properties = animations.back()->GetTargetPoint();
	//	}

	//	animations.pop();
	//}

	while (effects.size() > 1)
	{
		effects.pop_front();
	}

	if (effects.size() > 0)
	{
		if (effects.back())
		{
			effects.back()->Skip();
		}
		else
		{
			effects.pop_front();
		}		
	}

	return true;
}

bool SUIComponentComposite::HandleEvent( SUIEventPtr e )
{
	if (!e)
	{
		return true;
	}

	if (e->type == SUIEvent::None)
	{
		return true;
	}

	if(!isDisplay || !properties.transparency)
	{
		return false;
	}

	bool isEventHandled = false;
	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool lastInRect =  properties.rectangle.IsPointInRect(
		e->positionX - e->movementX, e->positionY - e->movementY);

	if (e->type == SUIEvent::MouseMove)
	{
		if ((!inRect || !SPInputManager::GetSingleton().GetMouse()->IsWithinWindow()) 
			&& lastInRect)
		{
			if (onMouseOut)
			{
				onMouseOut->Function(e);
			}

			//isEventHandled = true;
		}
		else if (inRect	&& lastInRect)
		{
			if (onMouse)
			{
				onMouse->Function(e);
			}

			//isEventHandled = true;
		}
		else if (inRect && !lastInRect)
		{
			if (onMouseIn)
			{
				onMouseIn->Function(e);
			}

			//isEventHandled = true;
		}
		
	}
	else
	{
		isEventHandled = false;

		if (e->type == SUIEvent::KeyDown)
		{
			if (onKeyDown[e->button])
			{
				isEventHandled = true;
				onKeyDown[e->button]->Function(e);
			}
		}

		if (e->type == SUIEvent::KeyPress)
		{
			if (onKeyPress[e->button])
			{
				isEventHandled = true;
				onKeyPress[e->button]->Function(e);
			}
		}

		if (e->type == SUIEvent::KeyUp)
		{
			if (onKeyUp[e->button])
			{
				isEventHandled = true;
				onKeyUp[e->button]->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseClick)
		{
			if (e->button == 0 && catchMouseLeftClick)
			{
				isEventHandled = true;
				catchMouseLeftClick->Function(e);
			}

			if (e->button == 2 && catchMouseMiddleClick)
			{
				isEventHandled = true;
				catchMouseMiddleClick->Function(e);
			}

			if (e->button == 1 && catchMouseRightClick)
			{
				isEventHandled = true;
				catchMouseRightClick->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseDClick)
		{
			if (e->button == 0 && catchMouseLeftDClick)
			{
				isEventHandled = true;
				catchMouseLeftDClick->Function(e);
			}

			if (e->button == 2 && catchMouseMiddleDClick)
			{
				isEventHandled = true;
				catchMouseMiddleDClick->Function(e);
			}

			if (e->button == 1 && catchMouseRightDClick)
			{
				isEventHandled = true;
				catchMouseRightDClick->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseDown)
		{
			if (e->button == 0 && catchMouseLeftDown)
			{
				isEventHandled = true;
				catchMouseLeftDown->Function(e);
			}

			if (e->button == 2 && catchMouseMiddleDown)
			{
				isEventHandled = true;
				catchMouseMiddleDown->Function(e);
			}

			if (e->button == 1 && catchMouseRightDown)
			{
				isEventHandled = true;
				catchMouseRightDown->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseUp)
		{
			if (e->button == 0 && catchMouseLeftUp)
			{
				isEventHandled = true;
				catchMouseLeftUp->Function(e);
			}

			if (e->button == 2 && catchMouseMiddleUp)
			{
				isEventHandled = true;
				catchMouseMiddleUp->Function(e);
			}

			if (e->button == 1 && catchMouseRightUp)
			{
				isEventHandled = true;
				catchMouseRightUp->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseScrollUp)
		{
			if (catchMouseScrollUp)
			{
				isEventHandled = true;
				catchMouseScrollUp->Function(e);
			}
		}

		if (e->type == SUIEvent::MouseScrollDown)
		{
			if (catchMouseScrollDown)
			{
				isEventHandled = true;
				catchMouseScrollDown->Function(e);
			}
		}

		if (!isEventHandled && inRect)
		{			
			isEventHandled = true;

			if (e->type == SUIEvent::MouseClick)
			{
				if (e->button == 0 && onMouseLeftClick)
				{
					onMouseLeftClick->Function(e);
				}

				if (e->button == 2 && onMouseMiddleClick)
				{
					onMouseMiddleClick->Function(e);
				}

				if (e->button == 1 && onMouseRightClick)
				{
					onMouseRightClick->Function(e);
				}
			}

			if (e->type == SUIEvent::MouseDClick)
			{
				if (e->button == 0 && onMouseLeftDClick)
				{
					onMouseLeftDClick->Function(e);
				}

				if (e->button == 2 && onMouseMiddleDClick)
				{
					onMouseMiddleDClick->Function(e);
				}

				if (e->button == 1 && onMouseRightDClick)
				{
					onMouseRightDClick->Function(e);
				}
			}

			if (e->type == SUIEvent::MouseDown)
			{
				if (e->button == 0 && onMouseLeftDown)
				{
					onMouseLeftDown->Function(e);
				}

				if (e->button == 2 && onMouseMiddleDown)
				{
					onMouseMiddleDown->Function(e);
				}

				if (e->button == 1 && onMouseRightDown)
				{
					onMouseRightDown->Function(e);
				}
			}

			if (e->type == SUIEvent::MouseUp)
			{
				if (e->button == 0 && onMouseLeftUp)
				{
					onMouseLeftUp->Function(e);
				}

				if (e->button == 2 && onMouseMiddleUp)
				{
					onMouseMiddleUp->Function(e);
				}

				if (e->button == 1 && onMouseRightUp)
				{
					onMouseRightUp->Function(e);
				}
			}

			if (e->type == SUIEvent::MouseScrollUp)
			{
				if (onMouseScrollUp)
				{
					onMouseScrollUp->Function(e);
				}
			}

			if (e->type == SUIEvent::MouseScrollDown)
			{
				if (onMouseScrollDown)
				{
					onMouseScrollDown->Function(e);
				}
			}
		}		
	}

	if (isEventHandled || e->type == SUIEvent::MouseMove)
	{
		e->positionX -= properties.rectangle.X;
		e->positionY -= properties.rectangle.Y;

		Children::reverse_iterator iter = children.rbegin();

		while(iter != children.rend())
		{
			if (*iter)
			{
				if((*iter)->HandleEvent(e))
				{
					break;
				}
			}
			iter++;
		}

		e->positionX += properties.rectangle.X;
		e->positionY += properties.rectangle.Y;
	}	

	return isEventHandled;
}

bool SUIComponentComposite::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIComponentComposite::SaveAsString()
{
	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(), L"SUICC");

	return result;
}
