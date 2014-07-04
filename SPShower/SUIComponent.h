#pragma once
#include "SRectangle.h"
#include "SUIProperties.h"
#include "SUIAnimation.h"
#include "SUIEffect.h"
#include <queue>
#include "SUIEvent.h"
#include "SUIEventHandler.h"
#include "ISV8Serializable.h"

#define  MaxLayer 255

using namespace SPEngine;

class SUIComponent;
class SUIScreen;

typedef SPPointer<SUIComponent> SUIComponentPtr;

class SUIComponent : 
	public SPTransition,
	public ISPDrawable,
	public ISPLoadable,
	public ISV8Serializable
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

	SUIEventHandlerPtr onMouseClick;
	SUIEventHandlerPtr onMouseDClick;
	SUIEventHandlerPtr onMouseDown;
	SUIEventHandlerPtr onMouseUp;
	SUIEventHandlerPtr onMouseScroll;
	SUIEventHandlerPtr onMouse;
	SUIEventHandlerPtr onMouseIn;
	SUIEventHandlerPtr onMouseOut;
	SUIEventHandlerPtr onKeyPress;
	SUIEventHandlerPtr onKeyDown;
	SUIEventHandlerPtr onKeyUp;

	SUIEventHandlerPtr catchMouseClick;
	SUIEventHandlerPtr catchMouseDClick;
	SUIEventHandlerPtr catchMouseDown;
	SUIEventHandlerPtr catchMouseUp;
	SUIEventHandlerPtr catchMouseScroll;
	SUIEventHandlerPtr catchMouse;
	SUIEventHandlerPtr catchMouseIn;
	SUIEventHandlerPtr catchMouseOut;
	SUIEventHandlerPtr catchKeyPress;
	SUIEventHandlerPtr catchKeyDown;
	SUIEventHandlerPtr catchKeyUp;
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
	bool				isAbsoluteRender;
	SPPointer<Persistent<Object>> v8Obj;
	/// @}	
	
public:
	/// @name Getter and Setter
	/// @{
	SUIScreen* GetScreen();

	SPString GetName();
	void SetName(SPString setName);

	SUIProperties GetProperties();
	SUIProperties GetTargetProperties();
	void SetProperties(SUIProperties setProperties);
	SPTexturePtr GetComponentTexture();

	/// @name Set Effect
	/// @{
	void SetRenderTarget(SPTexturePtr setTarget);
	void AddEffect(SUIEffectPtr setEffect);
	void ClearEffect();
	SUIEffectPtr GetCurrentEffect();
	void AddAnimation(SUIAnimationPtr setAnimation);
	void MergerAnimation(SUIAnimationPtr setAnimation);
	/// @}

	/// @name Set Background
	/// @{
	SPTexturePtr GetBackgroundImage();
	void SetBackgroundImage(SPTexturePtr setImage);
	D3DCOLOR GetBackgroundColor();
	void SetBackgroundColor(D3DCOLOR setColor);
	/// @}

	/// @name Set Box
	/// @{
	int GetWidth();	
	int GetHeight();
	void SetWidth(int setWidth);
	void SetHeight(int setHeight);

	void SetPosition(D3DXVECTOR2 pos);
	D3DXVECTOR2 GetPosition();
	void SetPositionX(int setX);
	void SetPositionY(int setY);

	float GetRotation();
	void SetRotation(float setRotation);	
	D3DXVECTOR2 GetRotationCenter();	
	void SetRotationCenter(D3DXVECTOR2 pos);
	void SetRotationCenterX(int setX);
	void SetRotationCenterY(int setY);
	/// @}

	/// @name Other
	/// @{
	float GetTransparency();
	void SetTransparency(float setTrans);

	float GetLayer();
	void SetLayer(float setLayer);

	int GetBackgroundX();
	void SetBackgroundX(int setX);
	
	int GetBackgroundY();
	void SetBackgroundY(int setY);
	
	SUIProperties::BackgroundMode GetBackgroundMode();
	void SetBackgroundMode(SUIProperties::BackgroundMode setMode);
	
	SUIProperties::BackgroundPosition GetBackgroundPositionMode();
	void SetBackgroundPositionMode(SUIProperties::BackgroundPosition setMode);	

	SRectangle GetBackgroundRect();
	/// @}

	/// @name AbsoluteRender
	/// @{
	void SetAbsoluteRender(bool setOn);

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
	Handle<Array> GetV8ChildComponents();
	
	/// @}
	
	
	/// @}

public:
	SUIComponent(SUIScreen* screen);
	virtual ~SUIComponent(void);

	virtual void Update(float timeDelta);
	virtual void PreDraw();
	virtual void Draw(float timeDelta);
	virtual void PostDraw();
	virtual void Load();
	virtual void Unload();
	virtual void Reload();
	virtual void HandleEvent(SUIEventPtr e);
	virtual void HandleMouseOut(SUIEventPtr e);
	virtual void HandleMouseOver(SUIEventPtr e);
	virtual void HandleMouseIn(SUIEventPtr e);
	virtual void Render(float timeDelta);
	virtual void AddChild(SUIComponentPtr setChild);
	virtual void InsertBefore(SUIComponentPtr newChild, SUIComponentPtr child);
	virtual void RemoveChild(SUIComponentPtr setChild);
	virtual void SetFather(SUIComponentPtr setFather);
	virtual SUIComponentPtr GetFather();

	void Hide();
	void Unhide();
	bool IsDisplay();
	bool IsAbsoluteRender();
	
	void PlayAnimation();
	void PlayEffect();
	virtual void Skip();

	virtual void LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
	void SaveAsImage(SPString path);
	SPTexturePtr SaveAsTexture();

protected:
	void UpdateAnimation(float timeDelta);
	void UpdateEffect(float timeDelta);

public:
	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );

	//SPString PropertiesToString();
	
};



