#include "AntiAim.h"

void AntiAim::anti_aimbot(CUserCmd* cmd) //creds to venoma
{
	if(!base.m_psCvar->misc_anti_aim
		||base.m_pWeapon->IsAttacking(cmd)
		||base.m_pWeapon->IsCurWepGrenade()
		||base.m_pWeapon->IsDefusing(cmd))
		return;



		float forward	= cmd->forwardmove; 
		float right		= cmd->sidemove; 
		float up		= cmd->upmove; 
		Vector viewforward,viewright,viewup,aimforward,aimright,aimup,vForwardNorm,vRightNorm,vUpNorm;		
		AngleVectors(cmd->viewangles, &viewforward, &viewright, &viewup);
		//------------------------------------------//
		if (base.m_psCvar->misc_anti_aim)
		{
				if (base.m_psCvar->misc_anti_aim ==  1 )
				{	 
					if (cmd->buttons &IN_LEFT||cmd->buttons &IN_MOVELEFT)		
					{	
						cmd->viewangles.x += (vec_t)225.0f;
						cmd->viewangles.y -= (vec_t)120.0f;
						cmd->viewangles.z -= (vec_t)180.0f;
					}	
					else if (cmd->buttons &IN_RIGHT||cmd->buttons &IN_MOVERIGHT)
					{
						cmd->viewangles.x += (vec_t)225.0f;
						cmd->viewangles.y += (vec_t)120.0f;
						cmd->viewangles.z += (vec_t)180.0f;
					}	
					else														
					{
						cmd->viewangles.x -= (vec_t)225.0f;
						cmd->viewangles.y -= (vec_t)120.0f;
						cmd->viewangles.z = (vec_t)fmod(-360.0f,360.0f);
					}			
				}
				if ( base.m_psCvar->misc_anti_aim == 2 )
				{	 
					if (cmd->buttons &IN_LEFT||cmd->buttons &IN_MOVELEFT)		
					{	
						cmd->viewangles.x -= (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
						cmd->viewangles.y -= (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
						cmd->viewangles.z -= (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
					}	
					else if (cmd->buttons &IN_RIGHT||cmd->buttons &IN_MOVERIGHT)
					{
						cmd->viewangles.x += (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
						cmd->viewangles.y += (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
						cmd->viewangles.z += (vec_t)(-360.0f) + ((float)rand() / RAND_MAX) * (360.0f - (-360.0f) );
					}	
					else														
					{
						cmd->viewangles.x = (vec_t)fmod(-360.0f,360.0f);
						cmd->viewangles.y = (vec_t)fmod(-360.0f,360.0f);
						cmd->viewangles.z = (vec_t)fmod(-360.0f,360.0f);
					}			
				}
		}
		AngleVectors(cmd->viewangles, &aimforward, &aimright, &aimup);
		base.m_pUtil->Normalize ( viewforward, vForwardNorm ); 
		base.m_pUtil->Normalize( viewright, vRightNorm ); 
		base.m_pUtil->Normalize( viewup, vUpNorm ); 		
		cmd->forwardmove = 	DotProduct(forward* vForwardNorm, aimforward)+DotProduct(right* vRightNorm, aimforward)+DotProduct(up* vUpNorm, aimforward); 
		cmd->sidemove = DotProduct(forward* vForwardNorm, aimright)+DotProduct(right* vRightNorm, aimright)+DotProduct(up* vUpNorm, aimright); 
		cmd->upmove = DotProduct(forward* vForwardNorm, aimup)+DotProduct(right* vRightNorm, aimup)+DotProduct(up* vUpNorm, aimup); 

}
void AntiAim::SpinViewangles(CUserCmd *cmd)//basic shitbot
{
	Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
	QAngle qAimAngles;
	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;
	float ftime = base.m_pEngine->Time();
	qAimAngles.Init(0.0f, cmd->viewangles.y, 0.0f);
	AngleVectors(qAimAngles, &viewforward, &viewright, &viewup);
	AngleVectors(cmd->viewangles, &viewforward, &viewright, &viewup);
	cmd->viewangles.y = (vec_t)(fmod(ftime / 0.1f * 360.0f,360.0f));
	qAimAngles.Init(0.0f,cmd->viewangles.y,0.0f);
	AngleVectors(qAimAngles, &aimforward, &aimright, &aimup);
	AngleVectors(cmd->viewangles, &aimforward, &aimright, &aimup);
	Vector vForwardNorm;		base.m_pUtil->Normalize ( viewforward, vForwardNorm );
	Vector vRightNorm;			base.m_pUtil->Normalize( viewright, vRightNorm );
	Vector vUpNorm;				base.m_pUtil->Normalize( viewup, vUpNorm );
	cmd->forwardmove = DotProduct(forward * vForwardNorm, aimforward) + DotProduct(right * vRightNorm, aimforward) + DotProduct(up * vUpNorm, aimforward);
	cmd->sidemove = DotProduct(forward * vForwardNorm, aimright) + DotProduct(right * vRightNorm, aimright) + DotProduct(up * vUpNorm, aimright);
	cmd->upmove = DotProduct(forward * vForwardNorm, aimup) + DotProduct(right * vRightNorm, aimup) + DotProduct(up * vUpNorm, aimup);
}
