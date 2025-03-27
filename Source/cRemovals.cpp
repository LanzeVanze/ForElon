#include "cRemovals.h"


void cRemovals::NoFlash()
{
	IMaterial *rm		= base.m_pMaterialSystem->FindMaterial( "particle\\particle_smokegrenade1", NULL );
	IMaterial *rm1		= base.m_pMaterialSystem->FindMaterial( "particle\\screenspace_fog", NULL );
	IMaterial *rm2		= base.m_pMaterialSystem->FindMaterial( "particle\\rain", NULL );
	IMaterial* rm3		= base.m_pMaterialSystem->FindMaterial( "effects\\flashbang", "ClientEffect textures" );
	IMaterial* rm4		= base.m_pMaterialSystem->FindMaterial( "effects\\flashbang_white", "ClientEffect textures" );

	if(base.m_psCvar->vis_noflash == 1 )
	{
        rm->SetMaterialVarFlag ( MATERIAL_VAR_NO_DRAW, true );
        rm1->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
        rm2->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
        rm3->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
		rm4->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
	}
	if(!base.m_psCvar->vis_noflash)
	{
        rm->SetMaterialVarFlag ( MATERIAL_VAR_NO_DRAW, false);
        rm1->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
        rm2->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
        rm3->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
		rm4->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
	}

}
void cRemovals::NoHands()
{
	IMaterial* Hands = base.m_pMaterialSystem->FindMaterial("models\\weapons\\v_models\\hands\\v_hands", "Model textures");

	if(base.m_psCvar->vis_nohands == 1 )
		Hands->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );

	if(base.m_psCvar->vis_nohands == 2 )
	{
		Hands->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
		Hands->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
	}
	if(!base.m_psCvar->vis_nohands)
	{
		Hands->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ,	false );
		Hands->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW,	false );
	}
}

void cRemovals::NoSky()
{
	if(base.m_psCvar->vis_nosky == 1 || base.m_psCvar->vis_nosky == 0)
	{
	    ConVar *xSKYBOX  = base.m_pCvar->FindVar("r_drawskybox");
	    ConVar *xSKY     = base.m_pCvar->FindVar("r_3dsky");
	    ConVar *gl_clear = base.m_pCvar->FindVar("gl_clear");
		if(base.m_psCvar->vis_nosky== 0)
		{
			xSKYBOX->SetValue(1);
			xSKY->SetValue(1);
			gl_clear->SetValue(0);
		}
		if(base.m_psCvar->vis_nosky == 1)
		{
			xSKYBOX->SetValue(0);
			xSKY->SetValue(0);
			gl_clear->SetValue(1);
		}
	}
}

void cRemovals::NoScope()
{
	if(base.m_psCvar->vis_noscope)
	{
		IMaterial* scopearc  = base.m_pMaterialSystem->FindMaterial( "sprites\\scope_arc","ClientEffect textures");
		IMaterial* scopelens = base.m_pMaterialSystem->FindMaterial( "overlays\\scope_lens","ClientEffect textures");
		scopearc->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true);
		scopelens->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
	}else{
		IMaterial* scopearc  = base.m_pMaterialSystem->FindMaterial( "sprites\\scope_arc","ClientEffect textures");
	    IMaterial* scopelens = base.m_pMaterialSystem->FindMaterial( "overlays\\scope_lens","ClientEffect textures");
		scopearc->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false);
		scopelens->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW,false );
	}
}