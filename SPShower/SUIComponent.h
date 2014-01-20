#pragma once
#include "SRectangle.h"
#include "SUIProperties.h"
#include "SUIAnimation.h"
#include "SUIEffect.h"
#include <queue>
#include "SUIEvent.h"
#include "SUIEventHandler.h"

#define  MaxLayer 255

using namespace SPEngine;

class SUIComponent;
class SUIScreen;

typedef SPPointer<SUIComponent> SUIComponentPtr;

class SUIComponent : 
	public SPTransition,
	public ISPDrawable,
	public ISPLoadable
{
protected:
	typedef list<SUIAnimationPtr> AnimationQueue;
	typedef list<SUIEffectPtr> EffectQueue;
	typedef list<SUIComponentPtr> Children;
	typedef	Children::iterator ChildIterator;

	Children children; ///< Children component list;

	/// @name Event Handlers
	/// @{
public:
	SUIEventHandlerPtr onMouseLeftClick;
	SUIEventHandlerPtr onMouseLeftDClick;
	SUIEventHandlerPtr onMouseLeftDown;
	SUIEventHandlerPtr onMouseLeftUp;

	SUIEventHandlerPtr onMouseRightClick;
	SUIEventHandlerPtr onMouseRightDClick;
	SUIEventHandlerPtr onMouseRightDown;
	SUIEventHandlerPtr onMouseRightUp;

	SUIEventHandlerPtr onMouseMiddleClick;
	SUIEventHandlerPtr onMouseMiddleDClick;
	SUIEventHandlerPtr onMouseMiddleDown;
	SUIEventHandlerPtr onMouseMiddleUp;

	SUIEventHandlerPtr onMouseScrollUp;
	SUIEventHandlerPtr onMouseScrollDown;

	SUIEventHandlerPtr catchMouseLeftClick;
	SUIEventHandlerPtr catchMouseLeftDClick;
	SUIEventHandlerPtr catchMouseLeftDown;
	SUIEventHandlerPtr catchMouseLeftUp;

	SUIEventHandlerPtr catchMouseRightClick;
	SUIEventHandlerPtr catchMouseRightDClick;
	SUIEventHandlerPtr catchMouseRightDown;
	SUIEventHandlerPtr catchMouseRightUp;

	SUIEventHandlerPtr catchMouseMiddleClick;
	SUIEventHandlerPtr catchMouseMiddleDClick;
	SUIEventHandlerPtr catchMouseMiddleDown;
	SUIEventHandlerPtr catchMouseMiddleUp;

	SUIEventHandlerPtr catchMouseScrollUp;
	SUIEventHandlerPtr catchMouseScrollDown;

	SUIEventHandlerPtr onMouse;
	SUIEventHandlerPtr onMouseIn;
	SUIEventHandlerPtr onMouseOut;

	SUIEventHandlerPtr onFocus;
	SUIEventHandlerPtr onBlur;

	SUIEventHandlerPtr onKeyPress[256];
	SUIEventHandlerPtr onKeyDown[256];
	SUIEventHandlerPtr onKeyUp[256];

	/// @}

protected:
	/// @name Properties
	/// @{
	SUIScreen*			screenBelongsTo;
	CCritSec			modificationLock;
	SPString			name;
	SUIProperties		properties;
	AnimationQueue		animations;
	SPTexturePtr		renderTarget;
	SPTexturePtr		childTarget;
	EffectQueue			effects;
	SUIComponentPtr		father;
	VariableMap			propertiesMap;
	bool				isAbsoluteRender;
	SPPointer<Persistent<Object>> v8Obj;
	/// @}	
	
public:
	/// @name Getter and Setter
	/// @{
	SUIScreen* GetScreen();

	SPString GetName();
	bool SetName(SPString setName);

	SUIProperties GetProperties();
	SUIProperties GetTargetProperties();
	bool SetProperties(SUIProperties setProperties);
	SPTexturePtr GetComponentTexture();

	/// @name Set Effect
	/// @{
	bool SetRenderTarget(SPTexturePtr setTarget);
	bool AddEffect(SUIEffectPtr setEffect);
	bool ClearEffect();
	SUIEffectPtr GetCurrentEffect();
	bool AddAnimation(SUIAnimationPtr setAnimation);
	bool MergerAnimation(SUIAnimationPtr setAnimation);
	/// @}

	/// @name Set Background
	/// @{
	SPTexturePtr GetBackgroundImage();
	bool SetBackgroundImage(SPTexturePtr setImage);
	D3DCOLOR GetBackgroundColor();
	bool SetBackgroundColor(D3DCOLOR setColor);
	/// @}

	/// @name Set Box
	/// @{
	int GetWidth();	
	int GetHeight();
	bool SetWidth(int setWidth);
	bool SetHeight(int setHeight);

	bool SetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosition();
	bool SetPositionX(int setX);
	bool SetPositionY(int setY);

	float GetRotation();
	bool SetRotation(float setRotation);	
	D3DXVECTOR2 GetRotationCenter();	
	bool SetRotationCenter(D3DXVECTOR2 pos);
	bool SetRotationCenterX(int setX);
	bool SetRotationCenterY(int setY);
	/// @}

	/// @name Other
	/// @{
	float GetTransparency();
	bool SetTransparency(float setTrans);

	float GetLayer();
	bool SetLayer(float setLayer);

	int GetBackgroundX();
	bool SetBackgroundX(int setX);
	
	int GetBackgroundY();
	bool SetBackgroundY(int setY);
	
	SUIProperties::BackgroundMode GetBackgroundMode();
	bool SetBackgroundMode(SUIProperties::BackgroundMode setMode);
	
	SUIProperties::BackgroundPosition GetBackgroundPositionMode();
	bool SetBackgroundPositionMode(SUIProperties::BackgroundPosition setMode);	

	SRectangle GetBackgroundRect();
	bool SetProperties(VariableMap args);
	/// @}

	/// @name AbsoluteRender
	/// @{
	bool SetAbsoluteRender(bool setOn);

	// Absolute position cache
	SPPointer<D3DXVECTOR3> _position;
	D3DXVECTOR3 Position();

	// Absolute background position cache
	SPPointer<D3DXVECTOR3> _positionBG;
	D3DXVECTOR3 PositionBG();

	// Absolute background color texture position cache
	SPPointer<D3DXVECTOR3> _postionColor;
	D3DXVECTOR3 PositionColor();

	// Absolute transform matrix cache
	SPPointer<D3DXMATRIX> _transformMatrix;
	D3DXMATRIX TransformMatrix();

	// Absolute color texture transform matrix cache
	SPPointer<D3DXMATRIX> _transformMatrixColor;
	D3DXMATRIX TransformMatrixColor();

	// Absolute background transform matrix cache
	SPPointer<D3DXMATRIX> _transformMatrixBG;
	D3DXMATRIX TransformMatrixBG();

	// Absolute alpha cache
	SPPointer<float> _alpha;
	float Alpha();

	// Absolute alpha cache
	SPPointer<float> _depth;
	float Depth();

	// Absolute child target
	SPTexturePtr _childTarget;
	SPTexturePtr ChildTarget();

	// Absolute Background Source Rect
	SPPointer<SPRectangle> _backgroudSrcRect;
	SPRectangle BackgroundSrcRect();

	// Absolute Cal Depth Base
	SPPointer<float> _calDepthBase;
	float CalDepth(float depth);

	// Clear caches. Must be called before next render.
	void ClearAbsoluteCache();

	virtual Handle<Object> GetV8Obj();
	
	/// @}
	
	
	/// @}

public:
	SUIComponent(SUIScreen* screen);
	virtual ~SUIComponent(void);

	virtual bool Update(float timeDelta);
	virtual bool PreDraw();
	virtual bool Draw(float timeDelta);
	virtual bool PostDraw();
	virtual bool Load();
	virtual bool Unload();
	virtual bool Reload();
	virtual bool HandleEvent(SUIEventPtr e);
	virtual bool Render(float timeDelta);
	virtual bool AddChild(SUIComponentPtr setChild);
	virtual bool RemoveChild(SUIComponentPtr setChild);
	virtual bool SetFather(SUIComponentPtr setFather);
	virtual SUIComponentPtr GetFather();

	bool Hide();
	bool Unhide();
	bool IsDisplay();
	bool IsAbsoluteRender();
	
	bool PlayAnimation();
	bool PlayEffect();
	virtual bool Skip();

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
	bool SaveAsImage(SPString path);
	SPTexturePtr SaveAsTexture();

protected:
	bool UpdateAnimation(float timeDelta);
	bool UpdateEffect(float timeDelta);
	SPString PropertiesToString();
	
};



