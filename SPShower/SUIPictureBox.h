#pragma once
#include "SUIMixImage.h"
#include "SUIPictureList.h"
#include "SUIComponent.h"

class SUIPictureBox : public SUIComponent
{
public:
	enum ImageMode
	{
		Positioning,
		Fill,
		FitWidth,
		FitHeight,
		FitMin,
		FitMax,
		ResizeBox,
	};

	enum ImagePosition
	{
		Normal,
		TopLeft,
		TopRight,
		TopCenter,
		BottomLeft,
		BottomRight,
		BottomCenter,
		CenterLeft,
		CenterRight,
		CenterAll,
	};

protected:
	SUIPictureListPtr	picture;	
	D3DXVECTOR2			imagePos;
	ImageMode			fillMode;
	ImagePosition		positionMode;
	SUITransformationPtr transformation;
	SUIPictureListPtr	targetPicture;

public:
	SUIPictureBox(SUIScreen* screen);
	virtual ~SUIPictureBox(void);

	void SetImagePosition(D3DXVECTOR2 setPos);
	void SetImagePositionX(int setX);
	int GetImagePositionX();
	void SetImagePositionY(int setY);
	int GetImagePositionY();

	void SetBaseImage(SPTexturePtr base);
	void SetMixImage(SUIMixImage image);

	void SetPositionMode(ImagePosition setMode);
	ImagePosition GetPositionMode();
	void SetFillMode(ImageMode setMode);
	ImageMode GetFillMode();

	void SetTransformation(SUITransformationPtr setTrans);
	void SetPicture(SUIPictureListPtr setPicture);
	void SetTransformationTarget(SUIPictureListPtr setTarget);

	void Transform();
	SRectangle GetTexRect();
	void PreDraw();
	void Draw(float timeDelta);
	void Update(float timeDelta);
	void Load();
	void Unload();
	void Reload();

	D3DXMATRIX TransformMatrixImage();
	D3DXVECTOR3 PositionImage();
	SPRectangle ImageSrcRect();

	virtual void LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();

	static SPString FillModeToString(ImageMode mode);
	static SPString PositionModeToString(ImagePosition mode);
	static ImageMode StringToFillMode(SPString modeName);
	static ImagePosition StringToPositionMode(SPString modeName);

	virtual Handle<Object> GetV8Obj();
	virtual Handle<Object> SaveAsObj();

};

typedef SPPointer<SUIPictureBox> SUIPictureBoxPtr;

