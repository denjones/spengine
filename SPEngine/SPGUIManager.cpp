#include "StdAfx.h"
#include "SPGUIManager.h"
#include "CEGUI.h"
#include "RendererModules/Direct3D9/CEGUIDirect3D9Renderer.h"
#include "SPGame.h"

namespace SPEngine
{
	SPGUIManager::SPGUIManager(void)
	{
	}

	SPGUIManager::~SPGUIManager(void)
	{
		CEGUI::System::destroy();
	}

	bool SPGUIManager::Initialize()
	{
		return true;
	}

	bool SPGUIManager::Load()
	{
		CEGUI::System::destroy();
		CEGUI::Direct3D9Renderer& myRenderer = CEGUI::Direct3D9Renderer::create(CurrentGame()->GetDevice());

		CEGUI::System::create(myRenderer);

		// initialise the required dirs for the DefaultResourceProvider
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
			(CEGUI::System::getSingleton().getResourceProvider());

		rp->setResourceGroupDirectory("schemes", "datafiles/schemes/");
		rp->setResourceGroupDirectory("imagesets", "datafiles/imagesets/");
		rp->setResourceGroupDirectory("fonts", "datafiles/fonts/");
		rp->setResourceGroupDirectory("layouts", "datafiles/layouts/");
		rp->setResourceGroupDirectory("looknfeels", "datafiles/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", "datafiles/lua_scripts/");

		// This is only really needed if you are using Xerces and need to
		// specify the schemas location
		rp->setResourceGroupDirectory("schemas", "../datafiles/xml_schemas/");

		// set the default resource groups to be used
		CEGUI::Imageset::setDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		// setup default group for validation schemas
		CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
		if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
			parser->setProperty("SchemaDefaultResourceGroup", "schemas");	

		// create (load) the TaharezLook scheme file
		// (this auto-loads the TaharezLook looknfeel and imageset files)
		CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

		// create (load) a font.
		// The first font loaded automatically becomes the default font, but note
		// that the scheme might have already loaded a font, so there may already
		// be a default set - if we want the "Commonweath-10" font to definitely
		// be the default, we should set the default explicitly afterwards.
		CEGUI::FontManager::getSingleton().create( "DejaVuSans-10.font" );		

		return true;
	}

	bool SPGUIManager::Unload()
	{
		CEGUI::System::destroy();

		return true;
	}

	bool SPGUIManager::Update( float timeDelta )
	{
		CEGUI::System::getSingleton().injectTimePulse(timeDelta);

		return true;
	}

	bool SPGUIManager::Draw( float timeDelta )
	{
		CEGUI::System::getSingleton().renderGUI();

		return true;
	}

	bool SPGUIManager::PostDraw()
	{
		D3DXMATRIX startMat(1,0,0,0,

			0,1,0,0,

			0,0,1,0,

			0,0,0,1);

		CurrentGame()->GetDevice()->SetTransform(D3DTS_WORLD, &startMat);

		CurrentGame()->GetDevice()->SetTransform(D3DTS_VIEW, &CurrentGame()->GetCamera()->ViewMatrix());

		CurrentGame()->GetDevice()->SetTransform(D3DTS_PROJECTION, &CurrentGame()->GetCamera()->ProjectionMatrix());

		CurrentGame()->GetDevice()->SetFVF(NULL);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


		CurrentGame()->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

		CurrentGame()->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);


		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		CurrentGame()->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);


		CurrentGame()->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		CurrentGame()->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


		CurrentGame()->GetDevice()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);


		CurrentGame()->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);

		CurrentGame()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		return true;
	}

}

