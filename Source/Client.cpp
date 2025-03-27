#include "client.h"

void __stdcall new_HudUpdate ( bool bActive )
{

	DO_ONCE
	(	
		if(!base.m_pAL->Verified())
			exit(0);

		add_log("new_HudUpdate");
		base.m_pCredits->ConsoleCredits();
		base.m_pSound->HookSoundEsp();
		base.m_pUtil->FontInit();
		vgui::VPANEL VisualPanels = base.m_pEnginevgui->GetPanel( PANEL_INGAMESCREENS );
		base.m_pDrawzLayer->Create( VisualPanels );  
		MathLib_Init( 2.2f, 2.2f, 0.0f, 2.0f, true, true, true, true );	      
	);
	gClient.HudUpdate( bActive );
}

void __stdcall new_CreateMove ( int sequence_number, float input_sample_frametime, bool active ) 
{
	DO_ONCE( add_log("new_CreateMove"); )

	gClient.CreateMove( sequence_number , input_sample_frametime , active );
	
	if ( base.m_pInput )
	{
		CUserCmd* cmd = base.m_pInput->GetUserCmd( sequence_number );		
		QAngle* pPunchAngle = ( QAngle* )( (DWORD)base.m_pMyPlayer->BaseEnt() + 0xBB0 );

		if ( base.m_pEngine->IsInGame() )
		{
			
			
			if(base.m_psCvar->aim_allways || base.m_psCvar->aim_shoot)
				base.m_pAimbot->AimAtTarget( cmd );

			if(base.m_psCvar->aim_key == 1 && cmd->buttons & IN_ATTACK)
				base.m_pAimbot->AimAtTarget( cmd );

			if(base.m_psCvar->aim_norecoil)
			{
				cmd->viewangles.x -= (	pPunchAngle->x * base.m_psCvar->aim_norecoil	);
				cmd->viewangles.y -= (	pPunchAngle->y * base.m_psCvar->aim_norecoil	);
			}

			if(base.m_psCvar->misc_spinbot && !(base.m_pWeapon->IsAttacking(cmd)))
				base.m_pAntiAim->SpinViewangles(cmd);

			
			if(base.m_psCvar->aim_nospread == 1)
			{
				float flNew[3],flOld[3];flOld[0] = cmd->viewangles[0];flOld[1] = cmd->viewangles[1];flOld[2] = cmd->viewangles[2];
				base.m_pNoSpread->GetSpreadFix( cmd->random_seed, flOld, flNew );
				cmd->viewangles[0] += flNew[0];cmd->viewangles[1] += flNew[1];cmd->viewangles[2] += flNew[2];
			}


			if(base.m_psCvar->aim_nospread == 2 && base.m_pWeapon->IsAttacking(cmd))//only when IN_/\77/\CK
			{
				float flNew[3],flOld[3];flOld[0] = cmd->viewangles[0];flOld[1] = cmd->viewangles[1];flOld[2] = cmd->viewangles[2];
				base.m_pNoSpread->GetSpreadFix( cmd->random_seed, flOld, flNew );
				cmd->viewangles[0] += flNew[0];cmd->viewangles[1] += flNew[1];cmd->viewangles[2] += flNew[2];
			}


			if(base.m_psCvar->misc_autopistol)
			{
				if (!base.m_pWeapon->IsCurWepGrenade())
				{
					if(base.m_pWeapon->IsAttacking(cmd)&& base.m_psCvar->misc_autopistol)
					{
						static bool bAttack = false;
						if (bAttack)	cmd->buttons |=  IN_ATTACK;
						else			cmd->buttons &= ~IN_ATTACK;
						bAttack = !bAttack;
					}
				}
			}

			if(base.m_psCvar->misc_anti_aim)
				base.m_pAntiAim->anti_aimbot(cmd);

			if ( cmd->buttons & IN_JUMP && base.m_psCvar->misc_bunnyhop)//JUMP LIKE A NIGGER
			{
				if( !base.m_pWeapon->IsOnGround() )
					cmd->buttons &= ~IN_JUMP;
			}
			
		}
	}
}