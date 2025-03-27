#include "cWallHack.h"



void WallHack::XQZ()
{

	IMaterial* TTeam1 = base.m_pMaterialSystem->FindMaterial("models\\player\\t_arctic\\t_arctic", "Model textures");
    IMaterial* TTeam2 = base.m_pMaterialSystem->FindMaterial("models\\player\\t_guerilla\\t_guerilla", "Model textures");
    IMaterial* TTeam3 = base.m_pMaterialSystem->FindMaterial("models\\player\\t_leet\\t_leet", "Model textures");
    IMaterial* TTeam4 = base.m_pMaterialSystem->FindMaterial("models\\player\\t_phoenix\\t_phoenix", "Model textures");
    IMaterial* CTeam1 = base.m_pMaterialSystem->FindMaterial("models\\player\\ct_gign\\ct_gign", "Model textures");
    IMaterial* CTeam2 = base.m_pMaterialSystem->FindMaterial("models\\player\\ct_gsg9\\ct_gsg9", "Model textures");
    IMaterial* CTeam3 = base.m_pMaterialSystem->FindMaterial("models\\player\\ct_sas\\ct_sas", "Model textures");
    IMaterial* CTeam4 = base.m_pMaterialSystem->FindMaterial("models\\player\\ct_urban\\ct_urban", "Model textures");

    if(base.m_psCvar->vis_xqzmodels)
    {
        TTeam1->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true);
        TTeam2->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true);
        CTeam1->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true);
        CTeam2->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
        TTeam3->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
        TTeam4->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
        CTeam3->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
        CTeam4->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, true );
	}
	if(!base.m_psCvar->vis_xqzmodels)
    {
        TTeam1->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false);
        TTeam2->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false);
        CTeam1->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false);
        CTeam2->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
        TTeam3->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
        TTeam4->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
        CTeam3->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
        CTeam4->SetMaterialVarFlag( MATERIAL_VAR_IGNOREZ, false );
    }

}

void WallHack::Asus()
{





/*
Texture: DE_DUST/DOOR011
] bind "p" "impulse 107"
Texture: **studio**
Texture: **studio**
Texture: DE_DUST/DOOR011
Texture: **studio**
Texture: **studio**
Texture: DE_DUST/SITEBWALL11B
Wally   killed Irwin with ak47.
Texture: DE_DUST/SITEBWALL12B
Texture: DE_DUST/SITEBWALL01A
Texture: DE_DUST/SITEBWALL01A
Texture: DE_DUST/STONEWALL02B
Wally   killed Brandon with ak47.
Texture: DE_DUST/DUMLTRYCRSD2
Texture: **studio**
Texture: DE_DUST/STONEWALL02B
Texture: DE_DUST/TEMPLEWALL03B
Texture: DE_DUST/TEMPLEWALL03B
Texture: DE_DUST/STONEWALL02C


*/


}