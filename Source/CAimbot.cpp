#include "CAimbot.h"
#include "sdk.h"

cCAimbot::cCAimbot( void )
{
	flBestDist = 99999.9f;
	m_nTarget = -1;
}

void cCAimbot::DropTarget( void )
{
	flBestDist = 99999.9f;
	m_nTarget = -1;
}


float cCAimbot::flGetDistance( int index )
{
	IClientEntity* pEntity = base.m_pEntList->GetClientEntity( index );
	if (pEntity == NULL )
		return 999999.0f;
	return flGetDistance( pEntity->GetAbsOrigin() );
}

float cCAimbot::flGetDistance( Vector vPlayer )
{
	IClientEntity* pEntity = base.m_pEntList->GetClientEntity( base.m_pEngine->GetLocalPlayer() );
	if ( pEntity == NULL )
		return 999999.0f;
	Vector vDeltaOrigin = vPlayer - pEntity->GetAbsOrigin();
	return sqrtf( vDeltaOrigin.Length() );
}

void cCAimbot::MakeVector( QAngle angle, QAngle& vector ) 
{ 
	float pitch; 
	float yaw; 
	float tmp;           
	pitch	= (float)(angle[0] * M_PI/180); 
	yaw		= (float)(angle[1] * M_PI/180); 
	tmp		= (float) cos(pitch);
	vector[0] = (float) (-tmp * -cos(yaw)); 
	vector[1] = (float) (sin(yaw)*tmp);
	vector[2] = (float) -sin(pitch);
}

void __fastcall cCAimbot::CalcAngle( Vector &src, Vector &dst, QAngle &angles )
{
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };
	double hyp = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
	angles[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
	angles[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
	angles[2] = 0.0f;
	if(delta[0] >= 0.0) { angles[1] += 180.0f; }
}

float cCAimbot::GetFov( QAngle angle, Vector src, Vector dst ) 
{ 
	QAngle ang,aim; 
	float fov; 
	CalcAngle(src, dst, ang); 
	MakeVector(angle, aim); 
	MakeVector(ang, ang);      
	float mag_s = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float mag_d = sqrt((aim[0]*aim[0]) + (aim[1]*aim[1]) + (aim[2]*aim[2])); 
	float u_dot_v = aim[0]*ang[0] + aim[1]*ang[1] + aim[2]*ang[2]; 
	fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0 / M_PI); 
	return fov; 
}
bool __fastcall cCAimbot::GetVisible( Vector& vecAbsStart, Vector& vecAbsEnd, C_BaseEntity* pBaseEnt) 
{ 
	player_info_t pinfo;
	trace_t tr;
	Ray_t ray;
	ray.Init( vecAbsStart, vecAbsEnd );
	base.m_pEnginetrace->TraceRay( ray, MASK_NPCWORLDSTATIC|CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX, NULL, &tr );
	if ( tr.fraction > 0.97f )
		return true;


	if ( tr.m_pEnt && pBaseEnt )
	{
		if(base.m_psCvar->aim_thru == 1)
			return true;

		if(base.m_psCvar->aim_thru == 2 && GetAsyncKeyState(VK_LBUTTON))
			return true;

		if ( tr.m_pEnt->index == 0 || tr.allsolid )
			return false;
		if (( base.m_pEngine->GetPlayerInfo( tr.m_pEnt->index, &pinfo )
			|| pBaseEnt->index == tr.m_pEnt->index) && tr.fraction > 0.92)
			return true;
	}
	return false;
}

bool __fastcall GetBonePosition ( int iBone, Vector& vecOrigin, QAngle qAngles, int index )
{
	if( iBone < 0 || iBone >= 20 )
		return false;
	matrix3x4_t pmatrix[MAXSTUDIOBONES];
	IClientEntity* ClientEntity = base.m_pEntList->GetClientEntity( index );
	IClientRenderable* RenderEntity =  ClientEntity->GetClientRenderable();
	if( RenderEntity->SetupBones( pmatrix, 128, BONE_USED_BY_HITBOX, base.m_pGlobals->curtime ) == false )
		return false;
	MatrixAngles( pmatrix[ iBone ], qAngles, vecOrigin );
	return true;
}

bool __fastcall GetHitboxPosition ( int iBone, Vector& vecOrigin, CBaseEntity* pBaseEnt  )
{
    matrix3x4_t pmatrix[MAXSTUDIOBONES];
    QAngle angles;
    const model_t *m_pModel = pBaseEnt->GetModel();
    if(m_pModel)
    {
        studiohdr_t *pStudioHdr = base.m_pModelinfo->GetStudiomodel( m_pModel );

        if( pBaseEnt->SetupBones( pmatrix, 128, BONE_USED_BY_HITBOX, base.m_pGlobals->curtime ) == false )
            return false;

        mstudiohitboxset_t *set =pStudioHdr->pHitboxSet( 0 );
        Vector vMin,vMax,vecPosition, vPlayer;
        QAngle angles;mstudiobbox_t* m_pHitbox = NULL;
		for(int i = 0; i < pStudioHdr->numhitboxsets;i++)
		{
			for(int r = 0; r < pStudioHdr->iHitboxCount(i); r++)
            {
				m_pHitbox = pStudioHdr->pHitbox(r, i);
                if (!m_pHitbox)
					continue;

                if(m_pHitbox->bone == iBone)
                {
                    MatrixAngles( pmatrix[ m_pHitbox->bone ], angles,vecPosition );
                    VectorTransform(m_pHitbox->bbmin, pmatrix[ m_pHitbox->bone ], vMin);
                    VectorTransform(m_pHitbox->bbmax, pmatrix[ m_pHitbox->bone ], vMax);
                    vecOrigin = (vMin + vMax) * 0.5f;
                }
             }
		 }
	}
    return true;
}


void cCAimbot::AimAtTarget( CUserCmd* cmd )
{ 
	if( base.m_pEngine->IsInGame() == false 
	||	base.m_pEngine->IsHLTV() == true  
	||	base.m_pMyPlayer->BaseEnt() == NULL )
		return;
	DropTarget();
	player_info_t pinfo;
	for( int index = 1; index <= base.m_pEntList->NumberOfEntities( false ); ++index )
	{
		if ( index == base.m_pEngine->GetLocalPlayer() )
			continue;
		IClientEntity* ClientEntity = base.m_pEntList->GetClientEntity( index );
		if (	ClientEntity == NULL
			||	ClientEntity->IsDormant() )
				continue;

		CBaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();
		int *lifestate = (int*) ( ( DWORD )pBaseEntity + ( DWORD )0x87 );
		if(!(*lifestate  == LIFE_ALIVE)
			||	base.m_pEngine->GetPlayerInfo( index, &pinfo ) == false
			||	pBaseEntity->GetTeamNumber() == base.m_pMyPlayer->BaseEnt()->GetTeamNumber())
			continue;


		
		//Bone aim
		if( base.m_psCvar->aim_method == 1 ){
			if(!GetBonePosition( base.m_psCvar->aim_hitbox , vPlayer, cmd->viewangles, index ))
				continue;
		}

		//Hitbox aim
		if( base.m_psCvar->aim_method == 2 ){
			if(!GetHitboxPosition( base.m_psCvar->aim_hitbox, vPlayer, pBaseEntity ))
				continue;
		}
		
		//Distance
		if(base.m_psCvar->aim_by_distance)
		{
			if ( flBestDist < flGetDistance( vPlayer) )
				continue;
			flBestDist = flGetDistance( vPlayer);
		}else{
			if(GetFov( base.m_pMyPlayer->BaseEnt()->GetAbsAngles(), base.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer ) > base.m_psCvar->aim_fov
			|| flBestDist < GetFov( base.m_pMyPlayer->BaseEnt()->GetAbsAngles(), base.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer ))
			continue;
			flBestDist = GetFov( base.m_pMyPlayer->BaseEnt()->GetAbsAngles(), base.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer );
		}

		if(!GetVisible( base.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer, pBaseEntity))
			continue;

		

		flBestDist = GetFov( base.m_pMyPlayer->BaseEnt()->GetAbsAngles(), base.m_pMyPlayer->BaseEnt()->EyePosition(), vPlayer );
		m_nTarget = index;
		Vector vDeltaOrigin = vPlayer - vPlayer;
		float fLatency = base.m_pEngine->GetNetChannelInfo()->GetLatency( FLOW_OUTGOING );
		vDeltaOrigin[0] *= fLatency;
		vDeltaOrigin[1] *= fLatency;
		vDeltaOrigin[2] += base.m_psCvar->aim_hdj; //Adjust height
		PredictedTargetPosition = vPlayer + vDeltaOrigin;
		
	}
	if( m_nTarget == -1 )	
		return;

	


	CalcAngle( base.m_pMyPlayer->BaseEnt()->EyePosition(), PredictedTargetPosition, cmd->viewangles );

	if (base.m_psCvar->aim_smooth)//from cn hack src
	{
		QAngle qCurrentView;
		base.m_pEngine->GetViewAngles( qCurrentView );
		QAngle qDelta = cmd->viewangles - qCurrentView; 
		if (qDelta[0]>180)  qDelta[0]-=360; 
		if (qDelta[1]>180)  qDelta[1]-=360; 
		if (qDelta[0]<-180) qDelta[0]+=360; 
		if (qDelta[1]<-180) qDelta[1]+=360; 
		cmd->viewangles = qCurrentView + qDelta / base.m_psCvar->aim_smooth; 
		if (cmd->viewangles[0] >  180) cmd->viewangles[0]-=360; 
		if (cmd->viewangles[1] >  180) cmd->viewangles[1]-=360; 
		if (cmd->viewangles[0] < -180) cmd->viewangles[0]+=360; 
		if (cmd->viewangles[1] < -180) cmd->viewangles[1]+=360;  
	}

	if(!base.m_psCvar->aim_silent)
		base.m_pEngine->SetViewAngles( cmd->viewangles );

	if(base.m_psCvar->aim_shoot){

		static bool bAttack = false;
		if (bAttack)	cmd->buttons |=  IN_ATTACK;
		else			cmd->buttons &= ~IN_ATTACK;
		bAttack = !bAttack;

	}

	DropTarget();
}