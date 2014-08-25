#pragma once
#include "SRectangle.h"

#define PI 3.1415926

class SUIProperties
{
public:
	enum BackgroundMode
	{
		Positioning,
		Fill,
		FitWidth,
		FitHeight,
		FitMin,
		FitMax,
	};

	enum BackgroundPosition
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

public:
	//SPPointer<SRectangle>		rectangle;
	SPPointer<int>				x;
	SPPointer<int>				y;
	SPPointer<int>				width;
	SPPointer<int>				height;
	SPPointer<float>			rotation;
	//SPPointer<D3DXVECTOR2>		rotationCenter;
	SPPointer<float>			rotationCenterX;
	SPPointer<float>			rotationCenterY;
	SPTexturePtr				backgroundImage;
	SPPointer<D3DCOLOR>			backgroundColor;
	SPPointer<float>			transparency;	
	SPPointer<float>			layer;
	SPPointer<int>				backgroundX;
	SPPointer<int>				backgroundY;
	SPPointer<BackgroundMode>	backgroundMode;
	SPPointer<BackgroundPosition> backgroundPosition;

public:
	SUIProperties(void);
	virtual ~SUIProperties(void);

	void Init();

	void operator = (SUIProperties& target);
	static SPString BackgroundModeToString(BackgroundMode mode);
	static SPString BackgroundPositionToString(BackgroundPosition mode);
	static BackgroundMode StringToBackgroundMode(SPString modeName);
	static BackgroundPosition StringToBackgroundPosition(SPString modeName);
};

