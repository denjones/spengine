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
		CengerRight,
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

	bool SetImagePosition(D3DXVECTOR2 setPos);
	bool SetImagePositionX(int setX);
	bool SetImagePositionY(int setY);
	bool SetBaseImage(SPTexturePtr base);
	bool SetMixImage(SUIMixImage image);
	bool SetPositionMode(ImagePosition setMode);
	bool SetFillMode(ImageMode setMode);
	bool SetTransformation(SUITransformationPtr setTrans);
	bool SetPicture(SUIPictureListPtr setPicture);
	bool SetTransformationTarget(SUIPictureListPtr setTarget);

	bool Transform();
	SRectangle GetTexRect();
	bool PreDraw();
	bool Draw(float timeDelta);
	bool Update(float timeDelta);
	bool Load();
	bool Unload();
	bool Reload();

	D3DXMATRIX TransformMatrixImage();
	D3DXVECTOR3 PositionImage();
	SPRectangle ImageSrcRect();

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

typedef SPPointer<SUIPictureBox> SUIPictureBoxPtr;

