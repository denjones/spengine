#include "StdAfx.h"
#include "SScreen.h"
#include "SUIBlankComponent.h"
#include "SUIManager.h"
#include "SUIEffectManager.h"
#include "SUITextBox.h"
#include "SUIPictureBox.h"


SScreen::SScreen(void)
{
	sampleComponent = NULL;
}

SScreen::~SScreen(void)
{
}

bool SScreen::Initialize()
{
	return true;
}

bool SScreen::Load()
{
	SUIManager::GetSingleton().CreateScreen(L"top", new SUIScreen());
	//SUIManager::GetSingleton().CreateScreen(L"sicily", new SUIScreen());
	//SUIManager::GetSingleton().FocusScreen(L"sicily");
	SUIManager::GetSingleton().FocusScreen(L"top");
	SPFontManager::GetSingleton().CreateFont(L"test", 30, 0, 700, 10, false, L"黑体");

	SUITransformationPtr trans = new SUITransformation();
	trans->Load(L"trans_01.tf");
	trans->SetTime(5);
	SUITransformationPtr transScreen = new SUITransformation();
	transScreen->Load(L"trans_01.tf");
	transScreen->SetTime(20);

	//SUIManager::GetSingleton().GetCurrentScreen()->GetComponent("global_root")->SetBackgroundColor(SPColor::Black);	

	SUIEffectPtr effect					= NULL;
	sampleComponent						= new SUIComponentComposite();
	SUIComponentCompositePtr top		= new SUIComponentComposite();
	SUIPictureBoxPtr bg					= new SUIPictureBox();
	SUIAnimationPtr	animation			= new SUIAnimation();
	SUIAnimationPtr	animation2			= new SUIAnimation();
	SUITextBoxPtr	textBlockChild	= new SUITextBox();
	SUIMixModePtr mask					= new SUIMixMode();
	SUIPictureBoxPtr picture			= new SUIPictureBox();
	SUIPictureBoxPtr bg2				= new SUIPictureBox();
	
	SUIManager::GetSingleton().GetScreen(L"top")->GetComponent(L"global_root")->AddChild(top);	
	//SUIManager::GetSingleton().GetScreen(L"sicily")->GetComponent(L"global_root")->AddChild(bg2);
	
	effect = LoadSetEffect(effect);

	top->SetName(L"top");	
	//top->AddEffect(effect);
	top->AddEffect(NULL);
	//top->AddChild(bg);
	top->AddChild(sampleComponent);
	//top->AddChild(picture);
	top->SetLayer(1);
	top->SetWidth(800);
	top->SetHeight(600);
	SUIManager::GetSingleton().GetScreen(L"top")->AddComponent(top);
	
	bg->SetBaseImage(SPTextureManager::GetSingleton().GetTexture(L"bg_01.jpg"));
	bg->SetName(L"bg");
	bg->SetFillMode(SUIPictureBox::ResizeBox);
	bg->SetLayer(2);
	//bg2->SetBaseImage(SPTextureManager::GetSingleton().GetTexture(L"sicily.jpg"));
	bg2->SetName(L"bg2");
	bg2->SetFillMode(SUIPictureBox::Positioning);
	bg2->SetWidth(800);
	bg2->SetHeight(600);
	bg2->SetPositionMode(SUIPictureBox::CenterAll);
	
	sampleComponent->SetBackgroundColor(SPColor::AliceBlue);
	sampleComponent->SetBackgroundColor(0);
	//sampleComponent->SetBackgroundImage(SPTextureManager::GetSingleton().GetTexture(L"st_01.png"));
	sampleComponent->SetPosition(D3DXVECTOR2(0, 0));
	sampleComponent->SetHeight(300);
	sampleComponent->SetWidth(600);
	sampleComponent->SetName(L"sample");
	sampleComponent->SetLayer(4);
	sampleComponent->AddChild(textBlockChild);
	//sampleComponent->AddAnimation(animation);
	//sampleComponent->AddAnimation(animation2);
	SUIManager::GetSingleton().GetScreen(L"top")->AddComponent(sampleComponent);	
	

	// Set animation.
	SUIProperties properties = sampleComponent->GetProperties();
	//properties.rotation = 2 * PI;
	properties.rotationCenter = D3DXVECTOR2(300, 100);
	properties.rectangle = SRectangle(300, 100, 200, 400);
	//properties.backgroundColor = SPColor::Green;
	//properties.transparency = 0.2;	
	animation->SetStartPoint(sampleComponent->GetProperties());
	animation->SetEndPoint(properties);
	animation->SetTime(5);	

	SUIProperties properties2 = sampleComponent->GetProperties();
	properties2.rotation = 2 * PI;
	properties2.rotationCenter = D3DXVECTOR2(300, 100);
	properties2.rectangle = SRectangle(10, 10, 200, 200);
	properties2.backgroundColor = D3DXCOLOR(0,0,0,0);
	properties2.transparency = 0.99;
	animation2->SetEndPoint(properties2);
	animation2->SetTime(5);
	
	textBlockChild->SetBackgroundColor(0xff000000);
	textBlockChild->SetPosition(D3DXVECTOR2(10, 10));
	textBlockChild->SetHeight(400);
	textBlockChild->SetWidth(400);
	textBlockChild->SetLayer(5);
	//add text
	SPFontPtr font1 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 
		30, 0, FW_BOLD, 5, false, L"consolas");
	wstring text1 = L"Hello Lily. How are you?";
	SPFontPtr font2 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 
		20, 0, FW_BOLD, 5, false, L"黑体");
	wstring text2 = L"你好莉莉，近来怎样？";
	SPFontPtr font3 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 
		20, 0, FW_BOLD, 5, false, L"Courier New");
	wstring text3 = L"Let's go for dinner. How this can be doneo?";
	SPFontPtr font4 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 
		30, 0, FW_BOLD, 5, false, L"微软雅黑");
	wstring text4 = L"一起去吃晚饭吧。这怎么可能";

	wstring punctuations = 
		L"/.,\';][=-)(*&^%$#@!~`\"?><:}{？》《“：}{|+——）（*&……%￥#@！~】【’；、。，";
	SUIText line1(text1, font1);
	SUIText line2(text2, font2);
	SUIText line3(text3, font3);
	SUIText line4(text4, font4);

	textBlockChild->AddText(line1);
	textBlockChild->AddText(line2);
	textBlockChild->AddText(line3);
	textBlockChild->AddText(line4);
	//
	textBlockChild->ApplyText();
	//SPFontManager::GetSingleton().SetSizeRate(1);
	
	mask->Load(L"mix_mask.mm");
	SUIMixImage maskImage;
	maskImage.MixMode = mask;
	maskImage.Image = SPTextureManager::GetSingleton().GetTexture(L"mask_st_02.jpg");
	maskImage.Layer = 1;
	
	SUIPictureListPtr transPicture = new SUIPictureList();
	transPicture->SetBaseImage(SPTextureManager::GetSingleton().GetTexture(L"st_03.png"));

	picture->SetBaseImage(SPTextureManager::GetSingleton().GetTexture(L"st_02.jpg"));
	picture->SetMixImage(maskImage);
	picture->SetPosition(D3DXVECTOR2(100, 0));
	picture->SetFillMode(SUIPictureBox::ResizeBox);
	picture->SetPositionMode(SUIPictureBox::Normal);
	picture->SetTransformationTarget(transPicture);
	picture->SetTransformation(trans);
	picture->SetLayer(3);
	SUIManager::GetSingleton().GetScreen(L"top")->AddComponent(picture);

	picture->Transform();

	//SUIManager::GetSingleton().SwitchToScreen("sicily", transScreen);

	return true;
}

bool SScreen::Unload()
{
	return true;
}

bool SScreen::Update( float timeDelta )
{
	sampleComponent->PlayAnimation();
	sampleComponent->PlayEffect();
	SUIComponentPtr top = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(L"top");
	
	if (top)
	{
		top->PlayEffect();
	}

	SUIManager::GetSingleton().Update(timeDelta);

	return true;
}

bool SScreen::Draw( float timeDelta )
{
	SPFontPtr font = SPFontManager::GetSingleton().GetFont(L"test");

	/*SPFontWriter::GetSingleton().Write(font, NULL, 
		SPStringHelper::ToWString(timeDelta),
		D3DXVECTOR2(200,160), SPColor::LightBlue, 0, 0, NULL );

	SPFontWriter::GetSingleton().Write(font, NULL, 

		SPStringHelper::ToString(sampleComponent->GetTransparency()),
		D3DXVECTOR2(200,140), SPColor::Blue, 0, NULL );*/

	SUIManager::GetSingleton().Draw(timeDelta);

	return true;
}

SUIEffectPtr SScreen::LoadSetEffect( SUIEffectPtr effect )
{
	//effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_mask_soft.ef", 
	//	SPTextureManager::GetSingleton().GetTexture("mask_040.png"));

	//effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_grayvalue.ef", 
	//	NULL);

	/*effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_mosaic.ef", 
	NULL);*/

	//effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_mosaicAll.ef", 
	//NULL);

	/*effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_relievo.ef", 
	NULL);*/

	//effect = SUIEffectManager::GetSingleton().CreateEffect(
	//	"mask_1", "effect_mask_zigzag.ef", NULL);

	effect = SUIEffectManager::GetSingleton().CreateEffect( L"effect_watercolor.ef");

	effect->SetTexture(1, SPTextureManager::GetSingleton().GetTexture(L"mask_025.png"));
	effect->SetFloat("waterPower", 4);

	//effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_spacial_laplace.ef", 
	//	NULL);

	/*effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_frequency_gauss.ef", 
	NULL);*/

	/*effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_spacial_pencilFilter.ef", 
	NULL);*/

	//effect = SUIEffectManager::GetSingleton().CreateEffect("mask_1", "effect_posure.ef", 
	//	NULL);

	effect->SetTime(20);
	effect->SetLevel(4);
	effect->SetType(SUITransition::Normal);
	return effect;
}

