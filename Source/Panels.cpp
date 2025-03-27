#include "Panels.h"
#include "sdk.h"

//------------------------------
ScreenSize_t sScreenSize;	// struct to store the screen-size
//------------------------------
//----------------------------------------------------------------------------------------------------------
CDrawLayer::CDrawLayer ( void )
{
	pDrawPanel = NULL;
}

CDrawLayer::~CDrawLayer ( void )
{
	Destroy();
}

void CDrawLayer::Create( vgui::VPANEL parent )
{
	pDrawPanel = new CDrawPanel ( parent );
}

void CDrawLayer::Destroy( void )
{
	if ( pDrawPanel )
	{
		ExitProcess( 0 );
		pDrawPanel->SetParent( (vgui::Panel *)NULL );
		delete pDrawPanel;
		pDrawPanel = NULL;
	}
}

//------------------------------------------------------------------------------------------------------------------
CDrawPanel::CDrawPanel( vgui::VPANEL parent ) : BaseClass( NULL,"DrawPanel" )//nigger vui esp
{
	SetParent( parent );	// set the parent
	SetPos( 0 , 0 );			// start at the left top corner
	SetVisible( true );		// yup ... :)
	SetCursor( 0 );		// not needed
	base.m_pEngine->GetScreenSize( sScreenSize.m_iWidth, sScreenSize.m_iHeight );
	SetSize( sScreenSize.m_iWidth, sScreenSize.m_iHeight );
}

void DrawEsp()
{
	if ( !base.m_pMyPlayer->BaseEnt() )
		return;

	if(base.m_psCvar->radar)
		base.m_pRadar->DrawRadarBack();

	player_info_t pInfo;	
	Vector vScreen;		
	Vector vWorldPosition;
	Vector vPlayerHead;	

	for ( int index = 0; index < base.m_pEntList->GetHighestEntityIndex(); index++  )
	{
		if ( index == base.m_pEngine->GetLocalPlayer() )
			continue;


						

		IClientEntity* ClientEntity = base.m_pEntList->GetClientEntity( index );

		if (	ClientEntity == NULL
			||	ClientEntity->IsDormant() )
			continue;

		CBaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();

		if (	pBaseEntity == NULL 
			||	pBaseEntity->IsDormant() )
			continue;

		int *iTeamIndex = (int*) ((DWORD)pBaseEntity +(DWORD)0x90 );
		int *lifestate = (int*) ( ( DWORD )pBaseEntity + ( DWORD )0x87 );
		int *pdwArmor =  (int*) (	(DWORD)pBaseEntity + (DWORD)0x1018 );

		DWORD dwGetTeamColor =  Color(255,255,255,255);

		if ( base.m_pAimbot->GetVisible( base.m_pMyPlayer->BaseEnt()->EyePosition(), pBaseEntity->EyePosition(), pBaseEntity) )//visible
		{
			if( *iTeamIndex == 2 )
				dwGetTeamColor = Color(255,0,0,255);

			if( *iTeamIndex == 3 )
				dwGetTeamColor = Color(0,0,255,255);
		}
		else
		{
			if( *iTeamIndex == 2 )
				dwGetTeamColor = Color(255,255,0,255);

			if( *iTeamIndex == 3 )
				dwGetTeamColor = Color(0,255,0,255);
		}


		if ( base.m_pEngine->GetPlayerInfo( index, &pInfo ) )
		{
			if(*lifestate  == LIFE_ALIVE)
			{
				if(base.m_psCvar->radar)
					base.m_pRadar->DrawRadarPoint( pBaseEntity->GetAbsOrigin(),  base.m_pMyPlayer->BaseEnt()->GetAbsOrigin(), base.m_pMyPlayer->BaseEnt()->GetAbsAngles(), dwGetTeamColor);
			}
		}

		base.m_pUtil->GetWorldSpaceCenter( pBaseEntity , vWorldPosition );
		if ( base.m_pUtil->WorldToScreen( vWorldPosition, vScreen ) )
		{
			if ( base.m_pEngine->GetPlayerInfo( index, &pInfo ) )
			{
				
				int *pdwHealth = (int*) ( (DWORD)pBaseEntity + (DWORD)0xDA4 );
				
				if( *lifestate  == LIFE_ALIVE )
				{
					if(base.m_psCvar->esp_show_enemys_only == 1 && pBaseEntity->GetTeamNumber() == base.m_pMyPlayer->BaseEnt()->GetTeamNumber()/*enemy*/)
						continue;

					if ( base.m_pUtil->WorldToScreen( pBaseEntity->EyePosition(), vPlayerHead ) )
					{
						if(base.m_psCvar->esp_box)
						{
							base.m_pMatSurface->DrawSetColor( RGBA(dwGetTeamColor) );
							base.m_pMatSurface->DrawOutlinedRect( vPlayerHead.x - 20, vPlayerHead.y - 20, vPlayerHead.x + 20, vPlayerHead.y + 60 );
						}
					}

					if(base.m_psCvar->esp_name)//O RLY
						base.m_pUtil->PrintText( vScreen.x-2, vScreen.y, dwGetTeamColor, "%s", pInfo.name );

					if(base.m_psCvar->esp_health == 1)
						base.m_pUtil->PrintText( vScreen.x+5, vScreen.y + 16 , dwGetTeamColor, "%i", *pdwHealth );

					if(base.m_psCvar->esp_health == 2){
						base.m_pUtil->FillRGBA( vScreen.x+3, vScreen.y + 16 , 33.3, 2, Color(255,0,0,255) );
						base.m_pUtil->FillRGBA( vScreen.x+3, vScreen.y + 16 , *pdwHealth / 3, 2, Color(1,255,1,255) );
					}

					if(base.m_psCvar->esp_armor == 1)
						base.m_pUtil->PrintText( vScreen.x+5, vScreen.y + 20 , dwGetTeamColor, "%i", *pdwArmor );

					if(base.m_psCvar->esp_armor == 2){
						base.m_pUtil->FillRGBA( vScreen.x+3, vScreen.y + 20 , 33.3, 2, Color(255,0,0,255) );
						base.m_pUtil->FillRGBA( vScreen.x+3, vScreen.y + 20 , *pdwArmor / 3, 2, Color(1,228,255,255) );
					}

					if(base.m_psCvar->esp_barrel)//LOL
					{
						float flYaw, flPitch, flRoll = 0.0f;
						Vector vecDir;
						QAngle qView;

						__asm
						{
							mov eax,pBaseEntity;
							add eax,0x101C;
							mov eax,[eax];
							mov flYaw,eax;
							mov eax,pBaseEntity;
							add eax,0x101C;
							add eax,4;
							mov eax,[eax];		
							mov flPitch,eax;
						}
						qView.x = flYaw;
						qView.y = flPitch;
						qView.z = flRoll;
						AngleVectors( qView, &vecDir );
						vecDir = vecDir * 8192 + pBaseEntity->EyePosition();
						base.m_pDebugOverlay->AddLineOverlay( pBaseEntity->EyePosition(), vecDir,RED( dwGetTeamColor ), GREEN( dwGetTeamColor ), BLUE( dwGetTeamColor ),  false, 0.07f );
					}
					color32* Model = (color32*)((DWORD)pBaseEntity  + (DWORD)0x58 );//yet again v3n0m4 owns me
					if(base.m_psCvar->vis_chams)
					{
						if (*iTeamIndex == 3)//nigger ct
						{
							Model->r = (byte)0;
							Model->g = (byte)0;
							Model->b = (byte)255;
							Model->a = (byte)255;
						}
						if (*iTeamIndex == 2)//nigger terrior
						{
							Model->r = (byte)255;
							Model->g = (byte)0;
							Model->b = (byte)0;
							Model->a = (byte)255;
						}
					}else{//Else they look normal- 255,255,255,255 = NO EFFECT
							Model->r = (byte)255;
							Model->g = (byte)255;
							Model->b = (byte)255;
							Model->a = (byte)255;
					}

					C_BaseCombatWeapon* m_pWeapon = base.m_pUtil->GetBaseCombatActiveWeapon( pBaseEntity );
					if ( m_pWeapon )
					{
						const char* szWeapon = base.m_pModelinfo->GetModelName ( m_pWeapon->GetModel( ) );
						char pWeapon[100];
						char pWeaponPrint[100];
						strcpy( pWeapon, szWeapon );
						if(base.m_psCvar->esp_weapon == 1)
						{
							if ( strstr( pWeapon, "w_pist_usp.mdl" ) )						
								strcpy( pWeaponPrint, "a" );
							else if ( strstr( pWeapon, "w_pist_usp_silencer.mdl" ) )
								strcpy( pWeaponPrint, "a" );
							else if ( strstr( pWeapon, "w_rif_ak47.mdl" ) )					
								strcpy( pWeaponPrint, "b" );
							else if ( strstr( pWeapon, "w_pist_glock18.mdl" ) )				
								strcpy( pWeaponPrint, "c" );
							else if ( strstr( pWeapon, "w_smg_tmp.mdl" ) )					
								strcpy( pWeaponPrint, "d" );
							else if ( strstr( pWeapon, "w_rif_aug.mdl" ) )					
								strcpy( pWeaponPrint, "e" );
							else if ( strstr( pWeapon, "w_pist_deagle.mdl" ) )				
								strcpy( pWeaponPrint, "f" );
							else if ( strstr( pWeapon, "w_eq_fraggrenade.mdl" ) )				
								strcpy( pWeaponPrint, "h" );
							else if ( strstr( pWeapon, "w_eq_fraggrenade_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "h" );
							else if ( strstr( pWeapon, "w_eq_flashbang_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "g" );
							else if ( strstr( pWeapon, "w_eq_flashbang.mdl" ) )				
								strcpy( pWeaponPrint, "g" );
							else if ( strstr( pWeapon, "w_snip_g3sg1.mdl" ) )					
								strcpy( pWeaponPrint, "i" );
							else if ( strstr( pWeapon, "w_knife_ct.mdl" ) )					
								strcpy( pWeaponPrint, "j" );
							else if ( strstr( pWeapon, "w_knife_t.mdl" ) )					
								strcpy( pWeaponPrint, "j" );
							else if ( strstr( pWeapon, "w_shot_m3super90.mdl" ) )				
								strcpy( pWeaponPrint, "k" );
							else if ( strstr( pWeapon, "w_smg_mac10.mdl" ) )					
								strcpy( pWeaponPrint, "l" );
							else if ( strstr( pWeapon, "w_smg_p90.mdl" ) )					
								strcpy( pWeaponPrint, "m" );
							else if ( strstr( pWeapon, "w_snip_scout.mdl" ) )					
								strcpy( pWeaponPrint, "n" );
							else if ( strstr( pWeapon, "w_snip_sg550.mdl" ) )					
								strcpy( pWeaponPrint, "o" );
							else if ( strstr( pWeapon, "w_eq_smokegrenade.mdl" ) )			
								strcpy( pWeaponPrint, "p" );
							else if ( strstr( pWeapon, "w_eq_smokegrenade_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "p" );
							else if ( strstr( pWeapon, "w_smg_ump45.mdl" ) )					
								strcpy( pWeaponPrint, "q" );
							else if ( strstr( pWeapon, "w_snip_awp.mdl" ) )					
								strcpy( pWeaponPrint, "r" );
							else if ( strstr( pWeapon, "w_pist_elite.mdl" ) )					
								strcpy( pWeaponPrint, "s" );
							else if ( strstr( pWeapon, "w_pist_elite_dropped.mdl" ) )			
								strcpy( pWeaponPrint, "s" );
							else if ( strstr( pWeapon, "w_rif_famas.mdl" ) )					
								strcpy( pWeaponPrint, "t" );
							else if ( strstr( pWeapon, "w_pist_fiveseven.mdl" ) )				
								strcpy( pWeaponPrint, "u" );
							else if ( strstr( pWeapon, "w_rif_galil.mdl" ) )					
								strcpy( pWeaponPrint, "v" );
							else if ( strstr( pWeapon, "w_rif_m4a1_silencer.mdl" ) )			
								strcpy( pWeaponPrint, "w" );
							else if ( strstr( pWeapon, "w_rif_m4a1.mdl" ) )					
								strcpy( pWeaponPrint, "w" );
							else if ( strstr( pWeapon, "w_smg_mp5.mdl" ) )					
								strcpy( pWeaponPrint, "x" );
							else if ( strstr( pWeapon, "w_pist_p228.mdl" ) )					
								strcpy( pWeaponPrint, "y" );
							else if ( strstr( pWeapon, "w_mach_m249para.mdl" ) )				
								strcpy( pWeaponPrint, "z" );
							else if ( strstr( pWeapon, "w_rif_sg552.mdl" ) )					
								strcpy( pWeaponPrint, "A" );
							else if ( strstr( pWeapon, "w_c4.mdl" ) )							
								strcpy( pWeaponPrint, "C" );
							else if ( strstr( pWeapon, "w_c4_planted.mdl" ) )
								strcpy( pWeaponPrint, "I" );
							else if ( strstr( pWeapon, "w_shot_xm1014.mdl" ) )
								strcpy( pWeaponPrint, "B" );
							else if ( strstr( pWeapon, "w_defuser.mdl" ))
								strcpy( pWeaponPrint, "G" );
							base.m_pUtil->DrawSprite( vScreen.x-32, vScreen.y+25, dwGetTeamColor," %s ", pWeaponPrint );
						}
						if(base.m_psCvar->esp_weapon == 2)
						{
							if ( strstr( pWeapon, "w_pist_usp.mdl" ) )						
								strcpy( pWeaponPrint, "USP" );
							else if ( strstr( pWeapon, "w_pist_usp_silencer.mdl" ) )
								strcpy( pWeaponPrint, "USP-Silenced" );
							else if ( strstr( pWeapon, "w_rif_ak47.mdl" ) )					
								strcpy( pWeaponPrint, "Ak-47" );
							else if ( strstr( pWeapon, "w_pist_glock18.mdl" ) )				
								strcpy( pWeaponPrint, "Glock 18" );
							else if ( strstr( pWeapon, "w_smg_tmp.mdl" ) )					
								strcpy( pWeaponPrint, "tMp" );
							else if ( strstr( pWeapon, "w_rif_aug.mdl" ) )					
								strcpy( pWeaponPrint, "Aug" );
							else if ( strstr( pWeapon, "w_pist_deagle.mdl" ) )				
								strcpy( pWeaponPrint, "DeagLe" );
							else if ( strstr( pWeapon, "w_eq_fraggrenade.mdl" ) )				
								strcpy( pWeaponPrint, "FragGrenade" );
							else if ( strstr( pWeapon, "w_eq_fraggrenade_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "FragGrenade" );
							else if ( strstr( pWeapon, "w_eq_flashbang_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "FlashGrenade" );
							else if ( strstr( pWeapon, "w_eq_flashbang.mdl" ) )				
								strcpy( pWeaponPrint, "FlashGrenade" );
							else if ( strstr( pWeapon, "w_snip_g3sg1.mdl" ) )					
								strcpy( pWeaponPrint, "g3sg1" );
							else if ( strstr( pWeapon, "w_knife_ct.mdl" ) )					
								strcpy( pWeaponPrint, "knife" );
							else if ( strstr( pWeapon, "w_knife_t.mdl" ) )					
								strcpy( pWeaponPrint, "knife" );
							else if ( strstr( pWeapon, "w_shot_m3super90.mdl" ) )				
								strcpy( pWeaponPrint, "m3 super 90" );
							else if ( strstr( pWeapon, "w_smg_mac10.mdl" ) )					
								strcpy( pWeaponPrint, "Uzi" );
							else if ( strstr( pWeapon, "w_smg_p90.mdl" ) )					
								strcpy( pWeaponPrint, "p90" );
							else if ( strstr( pWeapon, "w_snip_scout.mdl" ) )					
								strcpy( pWeaponPrint, "scout" );
							else if ( strstr( pWeapon, "w_snip_sg550.mdl" ) )					
								strcpy( pWeaponPrint, "sg550" );
							else if ( strstr( pWeapon, "w_eq_smokegrenade.mdl" ) )			
								strcpy( pWeaponPrint, "smokegrenade" );
							else if ( strstr( pWeapon, "w_eq_smokegrenade_thrown.mdl" ) )		
								strcpy( pWeaponPrint, "smokegrenade" );
							else if ( strstr( pWeapon, "w_smg_ump45.mdl" ) )					
								strcpy( pWeaponPrint, "ump45" );
							else if ( strstr( pWeapon, "w_snip_awp.mdl" ) )					
								strcpy( pWeaponPrint, "-AWP-" );
							else if ( strstr( pWeapon, "w_pist_elite.mdl" ) )					
								strcpy( pWeaponPrint, "Dualies" );
							else if ( strstr( pWeapon, "w_pist_elite_dropped.mdl" ) )			
								strcpy( pWeaponPrint, "Dualies" );
							else if ( strstr( pWeapon, "w_rif_famas.mdl" ) )					
								strcpy( pWeaponPrint, "Famas" );
							else if ( strstr( pWeapon, "w_pist_fiveseven.mdl" ) )				
								strcpy( pWeaponPrint, "FiveSeven" );
							else if ( strstr( pWeapon, "w_rif_galil.mdl" ) )					
								strcpy( pWeaponPrint, "Galil" );
							else if ( strstr( pWeapon, "w_rif_m4a1_silencer.mdl" ) )			
								strcpy( pWeaponPrint, "m4a1 silenced" );
							else if ( strstr( pWeapon, "w_rif_m4a1.mdl" ) )					
								strcpy( pWeaponPrint, "m4a1" );
							else if ( strstr( pWeapon, "w_smg_mp5.mdl" ) )					
								strcpy( pWeaponPrint, "mp5" );
							else if ( strstr( pWeapon, "w_pist_p228.mdl" ) )					
								strcpy( pWeaponPrint, "p228" );
							else if ( strstr( pWeapon, "w_mach_m249para.mdl" ) )				
								strcpy( pWeaponPrint, "m249" );
							else if ( strstr( pWeapon, "w_rif_sg552.mdl" ) )					
								strcpy( pWeaponPrint, "sg552" );
							else if ( strstr( pWeapon, "w_c4.mdl" ) )							
								strcpy( pWeaponPrint, "C4" );
							else if ( strstr( pWeapon, "w_c4_planted.mdl" ) )
								strcpy( pWeaponPrint, "C4" );
							else if ( strstr( pWeapon, "w_shot_xm1014.mdl" ) )
								strcpy( pWeaponPrint, "auto shottie" );
							else if ( strstr( pWeapon, "w_defuser.mdl" ))
								strcpy( pWeaponPrint, "defusing" );
							base.m_pUtil->PrintText( vScreen.x+5, vScreen.y+25, dwGetTeamColor," %s ", pWeaponPrint );
						}
					}
				}
			}
		}
	}
}


void CDrawPanel::Paint( void ) 
{


	DO_ONCE( add_log("CDrawPanel::Paint"); 
			 base.m_pSettings->LoadConfigs(); 
	);

	base.m_pForceCvar->Unlock();


	if (   !base.m_pEngine->IsConnected()
		|| !base.m_pEngine->IsInGame()
		|| !base.m_pMyPlayer->BaseEnt() 
		|| base.m_pEngine->Con_IsVisible() 
		|| base.m_pEngine->IsLevelMainMenuBackground())
		return;

		base.m_pModelRender->RemoveAllDecalsFromAllModels();
	if(base.m_psCvar->vis_xqzmodels)	
		base.m_pWallHack->XQZ();

	if(base.m_psCvar->vis_noflash)
		base.m_pRemovals->NoFlash();

	if(base.m_psCvar->vis_nohands)
		base.m_pRemovals->NoHands();

	if(base.m_psCvar->vis_nosky)
		base.m_pRemovals->NoSky();

	if(base.m_psCvar->esp_sound)
		base.m_pSound->DrawSoundEsp();


	DrawEsp();

	if(base.m_psCvar->vis_crosshair)
		base.m_pCross->SimpleCross();

	base.m_pMenu->InitializeMenu();
	base.m_pMenu->MenuDrawing();

	if(GetAsyncKeyState(VK_INSERT) &1 )
		base.m_pSettings->SaveConfigs();



	/*
	int sw;
	int sh;
	base.m_pGameUIFuncs->GetDesktopResolution(sw,sh);
	base.m_pUtil->PrintText(500,500,Color(255,0,0,255),"%i x %i",sw,sh);*/

	

	base.m_pRecoil->RemovePunchAngle();
}