#include "StdAfx.h"
#include "SUIBlankComponent.h"


SUIBlankComponent::SUIBlankComponent(void)
{
}


SUIBlankComponent::~SUIBlankComponent(void)
{
}

bool SUIBlankComponent::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	SUIComponent::UpdateAnimation(timeDelta);
	SUIComponent::UpdateEffect(timeDelta);

	return true;
}

bool SUIBlankComponent::Draw( float timeDelta )
{
	return true;
}

bool SUIBlankComponent::PreDraw()
{
	childTarget = SPTextureManager::GetSingleton().CreateRenderTarget(
		properties.rectangle.Width, properties.rectangle.Height, properties.backgroundColor);

	// ?
	//childTarget->Fill(0x00000000);

	SPRectangle destRect = properties.rectangle;
	destRect.X = 0;
	destRect.Y = 0;

	SPTexturePtr backgroundColorTex = SPTextureManager::GetSingleton().GetBlankWhiteTexture();

	SPSpriteManager::GetSingleton().RenderOnScreen(backgroundColorTex,
		NULL, destRect, properties.backgroundColor, 1, childTarget);

	if (properties.backgroundImage)
	{
		SPSpriteManager::GetSingleton().RenderOnScreen(properties.backgroundImage,
			NULL, GetBackgroundRect(), SPColor::White, 1, childTarget);
	}

	return true;
}

bool SUIBlankComponent::PostDraw()
{
	SPSpriteManager::GetSingleton().RenderWithRotation(
		childTarget, 
		GetCurrentEffect(), 
		D3DXVECTOR3(GetPosition().x, GetPosition().y, Depth()),
		properties.rotationCenter,
		properties.rotation,
		properties.transparency * SPColor::White,
		renderTarget);

	//childTarget = NULL;

	return true;
}

bool SUIBlankComponent::Skip()
{
	while (animations.size() > 1)
	{
		animations.pop_front();
	}

	if (animations.size() > 0)
	{
		if (animations.back())
		{
			animations.back()->Skip();
			properties = animations.back()->GetTargetPoint();
		}
	
		animations.pop_front();
	}

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

bool SUIBlankComponent::HandleEvent( SUIEventPtr e )
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

			isEventHandled = true;
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

		if (isEventHandled)
		{
			return true;
		}
		else if (inRect)
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

	return isEventHandled;
}

bool SUIBlankComponent::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIBlankComponent::SaveAsString()
{
	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(), L"SUIBC");

	return result;
}
