//////////////////////////////////////////////////////////////////////////
/// @file		SPEngine.h the header file of basic engine header.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-30
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "resource.h"

//////////////////////////////////////////////////////////////////////////

/// @name SPGame header
/// @{
#include "SPGame.h"
#include "SPGameManager.h"
#include "SPGameFactory.h"
#include "SPComponent.h"
#include "SPComponentManager.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPWindow header
/// @{
#include "SPWindow.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPInput header
/// @{
#include "SPInputManager.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPGraphics header
/// @{
#include "SPTextureManager.h"
#include "SPSpriteManager.h"
#include "SPSpriteManager3D.h"
#include "SPLightManager.h"
#include "SPMaterialManager.h"
#include "SPFontManager.h"
#include "SPFontWriter.h"
#include "SPCamera.h"
#include "SPShaderManager.h"
#include "SPConfigManager.h"
#include "SPEffectManager.h"
#include "SPParticleSystemManager.h"
#include "SPParticleSystem3D.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPVideo header
/// @{
#include "SPVideo.h"
#include "SPVideoManager.h"
#include "SPVideoTexture.h"
/// @}

//////////////////////////////////////////////////////////////////////////


/// @name SPSound header
/// @{
#include "SPSound.h"
#include "SPSoundManager.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPHelper header
/// @{
#include "SPStringHelper.h"
#include "SPColorHelper.h"
#include "SPLogHelper.h"
#include "SPMessageHelper.h"
#include "SPFileHelper.h"
#include "SPRandomHelper.h"
#include "SPPathHelper.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPScreen header
/// @{
#include "SPBaseScreen.h"
#include "SPScreenManager.h"
/// @}

//////////////////////////////////////////////////////////////////////////

/// @name SPScript header
#include "SPV8ScriptEngine.h"

//////////////////////////////////////////////////////////////////////////

/// @name SPInterface
#include "ISPDrawable.h"
#include "ISPLoadable.h"
#include "ISPUpdatable.h"

//////////////////////////////////////////////////////////////////////////

/// @name SPStructure
#include "SPString.h"
#include "SPStringMap.h"
#include "SPComposite.h"
#include "SPFactory.h"
#include "SPPointer.h"
#include "SPTransition.h"
#include "SPSingleton.h"
#include "SPRectangle.h"

//////////////////////////////////////////////////////////////////////////

/// @name SPFile
#include "SPFileManager.h"

//////////////////////////////////////////////////////////////////////////