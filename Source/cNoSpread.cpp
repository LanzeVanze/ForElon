#include "cNoSpread.h"
#include "sdk.h"



#define WEAPON_NULL				0
#define WEAPON_AK47				1
#define WEAPON_AUG				2
#define WEAPON_AWP				3
#define WEAPON_DEAGLE			4
#define WEAPON_ELITES			5
#define WEAPON_FAMAS			6
#define WEAPON_FIVESEVEN		7
#define WEAPON_G3SG1			8
#define WEAPON_GALIL			9
#define WEAPON_GLOCK18			10
#define WEAPON_M249				11
#define WEAPON_M3				12
#define WEAPON_M4A1				13
#define WEAPON_MAC10			14
#define WEAPON_MP5				15
#define WEAPON_P228				16
#define WEAPON_P90				17
#define WEAPON_SCOUT			18
#define WEAPON_SG550			19  
#define WEAPON_SG552			20 
#define WEAPON_TMP				21
#define WEAPON_UMP45			22
#define WEAPON_USP45			23
#define WEAPON_XM1014			24
#define WEAPON_KNIFE			25
#define WEAPON_FLASHBANG		26 
#define WEAPON_HE_GRENADE		27
#define WEAPON_SMOKE_GRENADE	28 
#define WEAPON_C4				29


/*
Thundaga:Source - Client Hook for Half-Life 2
NoSpread Class Credits:
Copyright (C) 2004 Paleface
Copyright (C) 2004 P47RICK
Copyright (C) 2004 Tetsuo
Copyright (C) 2004 taurine

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

cNoSpread::cNoSpread( void )
{
	m_iLastWeaponID = WEAPON_NULL;
}

int cNoSpread::GetWeaponID(const char *szWeaponName)
{
	C_BaseCombatWeapon* m_pWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );

	if ( !m_pWeapon )
		return WEAPON_NULL;

	//knife
	if ( strstr( szWeaponName, "_knife_t.mdl" ) )
		return WEAPON_KNIFE;

	if ( strstr( szWeaponName, "_knife_ct.mdl" ) )
		return WEAPON_KNIFE;

	//pistol
	if ( strstr( szWeaponName, "_pist_deagle.mdl" ) )
		return WEAPON_DEAGLE;

	if ( strstr( szWeaponName, "_pist_elite.mdl" ) )
		return WEAPON_ELITES;

	if ( strstr( szWeaponName, "_pist_fiveseven.mdl" ) )
		return WEAPON_FIVESEVEN;

	if ( strstr( szWeaponName, "_pist_glock18.mdl" ) )
		return WEAPON_GLOCK18;

	if ( strstr( szWeaponName, "_pist_p228.mdl" ) )
		return WEAPON_P228;

	if ( strstr( szWeaponName, "_pist_usp.mdl" ) )
		return WEAPON_USP45;

	//riffles
	if ( strstr( szWeaponName, "_rif_ak47.mdl" ) )
		return WEAPON_AK47;

	if ( strstr( szWeaponName, "_rif_aug.mdl" ) )
		return WEAPON_AUG;

	if ( strstr( szWeaponName, "_rif_m4a1.mdl" ) )
		return WEAPON_M4A1;

	if ( strstr( szWeaponName, "_rif_famas.mdl" ) )
		return WEAPON_FAMAS;

	if ( strstr( szWeaponName, "_rif_galil.mdl" ) )
		return WEAPON_GALIL;

	if ( strstr( szWeaponName, "_rif_sg552.mdl" ) )
		return WEAPON_SG552;

	if ( strstr( szWeaponName, "_mach_m249para.mdl" ) )
		return WEAPON_M249;

	//smg
	if ( strstr( szWeaponName, "_smg_tmp.mdl" ) )
		return WEAPON_TMP;

	if ( strstr( szWeaponName, "_smg_mac10.mdl" ) )
		return WEAPON_MAC10;

	if ( strstr( szWeaponName, "_smg_p90.mdl" ) )
		return WEAPON_P90;

	if ( strstr( szWeaponName, "_smg_ump45.mdl" ) )
		return WEAPON_UMP45;

	if ( strstr( szWeaponName, "_smg_mp5.mdl" ) )
		return WEAPON_MP5;

	//sniper
	if ( strstr( szWeaponName, "_snip_g3sg1.mdl" ) )
		return WEAPON_G3SG1;

	if ( strstr( szWeaponName, "_snip_scout.mdl" ) )
		return WEAPON_SCOUT;

	if ( strstr( szWeaponName, "_snip_sg550.mdl" ) )
		return WEAPON_SG550;

	if ( strstr( szWeaponName, "_snip_awp.mdl" ) )
		return WEAPON_AWP;

	//shotguns
	if ( strstr( szWeaponName, "_shot_xm1014.mdl" ) )
		return WEAPON_XM1014;

	if ( strstr( szWeaponName, "_shot_m3super90.mdl" ) )
		return WEAPON_M3;

	//misc
	if ( strstr( szWeaponName, "_eq_flashbang.mdl" ) )
		return WEAPON_FLASHBANG;

	if ( strstr( szWeaponName, "_eq_fraggrenade.mdl" ) )
		return WEAPON_HE_GRENADE;

	if ( strstr( szWeaponName, "_eq_smokegrenade.mdl" ) )
		return WEAPON_SMOKE_GRENADE;

	if ( strstr( szWeaponName, "_c4.mdl" ) )
		return WEAPON_C4;

	return WEAPON_NULL;
}

float cNoSpread::GetVecSpread()
{
	float flSpread = 0.0f;
	C_BaseCombatWeapon* m_pWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );

	if ( !m_pWeapon )
		return 0.0f;

	int *iMyFlAgs = (int*) ( (DWORD)base.m_pMyPlayer->BaseEnt() + (DWORD)0x2B4 );
	int iFlags = *iMyFlAgs;
	float* f_FOV = (float*)(DWORD)0x243FB3A8;
	float m_Fov = *f_FOV;
	float* AccuracyPointer = (float*) ((DWORD)m_pWeapon + 0x760);
	float m_flAccuracy = *AccuracyPointer;
	bool* m_bWeaponBitPointer = (bool*)  ((DWORD)m_pWeapon + 0x780);
	bool m_bWeaponBit = *m_bWeaponBitPointer;
	bool* m_bWeaponBitPointerPistols = (bool*)  ((DWORD)m_pWeapon + 0x778);
	bool m_bWeaponBitPistol = *m_bWeaponBitPointerPistols;
	Vector vVelocity = base.m_pMyPlayer->BaseEnt()->m_vecVelocity;

	int iSpeed = 0;

	if (vVelocity.IsLengthLessThan(1))				
		iSpeed = 0;
	else 											
		iSpeed = (int)vVelocity.Length2D();

	int iWeaponID = GetWeaponID(base.m_pModelinfo->GetModelName( m_pWeapon->GetModel() ));

	const char *strModelName = base.m_pModelinfo->GetModelName ( m_pWeapon->GetModel());

	switch(iWeaponID)//spread now
	{
	case WEAPON_NULL:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_KNIFE:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_FLASHBANG:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_HE_GRENADE:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_SMOKE_GRENADE:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_C4:
		{
			flSpread	=	0.0f;
			break;
		}
	case WEAPON_AK47:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.04 + (0.4) * (m_flAccuracy));
			else if(iSpeed > 140)
				flSpread = (0.04 + (0.07) * (m_flAccuracy));
			else
				flSpread = ((0.0275) * (m_flAccuracy));
			break;
		}
	case WEAPON_AUG:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.035 + (0.4) * (m_flAccuracy));
			else if (iSpeed > 140)
				flSpread = (0.035 + (0.07) * (m_flAccuracy));
			else 
				flSpread = ((0.02) * (m_flAccuracy));
			break;
		}
	case WEAPON_AWP:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread =  0.85;
			else if (iSpeed > 140)
				flSpread =  0.25;
			else if (iSpeed > 10)
				flSpread =  0.1;
			else if (iFlags &FL_DUCKING)
				flSpread =  0.0;
			else 
				flSpread =  0.001;

			if( m_Fov >= 80.0f )
				flSpread += 0.08;
			break;
		}
	case WEAPON_DEAGLE:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((1.5) * (1 - m_flAccuracy));
			else if(iSpeed > 5)
				flSpread = ((0.25) * (1 - m_flAccuracy));
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.115) * (1 - m_flAccuracy));
			else
				flSpread = ((0.13) * (1 - m_flAccuracy));
			break;
		}
	case WEAPON_ELITES:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((1.3) * (1 - m_flAccuracy));
			else if(iSpeed > 5)
				flSpread = ((0.175) * (1 - m_flAccuracy));
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.08) * (1 - m_flAccuracy));
			else
				flSpread = ((0.1) * (1 - m_flAccuracy));
			break;
		}
	case WEAPON_FAMAS:
        {
            if(m_bWeaponBit)
            {
                if ( iFlags & FL_ONGROUND )
                    {
                        if ( iSpeed > 140.0f )
                            return flSpread = 0.030 + (0.07) * (m_flAccuracy);
                        else
                            return flSpread = (0.020) * (m_flAccuracy);
                    }
                    else
                        return flSpread = 0.030 + (0.3) * (m_flAccuracy);
                }
                else
                {
                    if ( iFlags & FL_ONGROUND )
                    {
                        if ( iSpeed > 140.0f )
                            return flSpread = ( m_flAccuracy * 0.07f ) + 0.04f;
                        else
                            return flSpread = ( m_flAccuracy * 0.02f ) + 0.01;
                    }
                    else
                       return flSpread = ( m_flAccuracy * 0.3f ) + 0.04f;
                }
            }
            break;
	case WEAPON_FIVESEVEN:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((1.5) * (1 - m_flAccuracy));
			else if (iSpeed > 5)
				flSpread = ((0.255) * (1 - m_flAccuracy));
			else if (iFlags &FL_DUCKING)
				flSpread = ((0.075) * (1 - m_flAccuracy));
			else
				flSpread = ((0.15) * (1 - m_flAccuracy));
			break;
		}
	case WEAPON_G3SG1:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.45) * (1 - m_flAccuracy));
			else if(iSpeed > 5)
				flSpread = 0.15;
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.035) * (1 - m_flAccuracy));
			else 
				flSpread = ((0.055) * (1 - m_flAccuracy));
			
		if( m_Fov >= 80.0f )
				flSpread += 0.025;
			break;
		}
	case WEAPON_GALIL:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.04 + (0.3) * (m_flAccuracy));
			else if(iSpeed > 140)
				flSpread = (0.04 + (0.07) * (m_flAccuracy));
			else
				flSpread = ((0.0375) * (m_flAccuracy));
			break;
		}
	case WEAPON_GLOCK18:
		{
			if(m_bWeaponBitPistol)
			{
				if(!(iFlags &FL_ONGROUND))
					flSpread = ((1.2) * (1 - m_flAccuracy));
				else if(iSpeed > 5)
					flSpread = ((0.185) * (1 - m_flAccuracy));
				else if((iFlags &FL_DUCKING))
					flSpread = ((0.095) * (1 - m_flAccuracy));
				else
					flSpread = ((0.3) * (1 - m_flAccuracy));
			}
			else
			{
				if(!(iFlags &FL_ONGROUND))
					flSpread = ((1.0) * (1 - m_flAccuracy));
				else if(iSpeed > 5)
					flSpread = ((0.165) * (1 - m_flAccuracy));
				else if((iFlags &FL_DUCKING))
					flSpread = ((0.075) * (1 - m_flAccuracy));
				else
					flSpread = ((0.1) * (1 - m_flAccuracy));
			}
			break;
		}
	case WEAPON_M249:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.045 + (0.5) * (m_flAccuracy));
			else if(iSpeed > 140)
				flSpread = (0.045 + (0.095) * (m_flAccuracy));
			else
				flSpread = ((0.03) * (m_flAccuracy));
			break;
		}
	case WEAPON_M4A1:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.035 + (0.4) * (m_flAccuracy));
			else if(iSpeed > 140)
				flSpread = (0.035 + (0.07) * (m_flAccuracy));
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.095) * (1 - m_flAccuracy));
			else if(m_bWeaponBit)
				flSpread = ((0.025) * (m_flAccuracy));
			else
				flSpread = ((0.02) * (m_flAccuracy));
			break;
		}
	case WEAPON_MAC10:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.375) * (m_flAccuracy));
			else
				flSpread = ((0.03) * (m_flAccuracy));
			break;
		}
	case WEAPON_MP5:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.2) * (m_flAccuracy));
			else
				flSpread = ((0.04) * (m_flAccuracy));
			break;
		}
	case WEAPON_P228:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((1.5) * (1 - m_flAccuracy));
			else if(iSpeed > 5)
				flSpread = ((0.255) * (1 - m_flAccuracy));
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.075) * (1 - m_flAccuracy));
			else
				flSpread = ((0.15) * (1 - m_flAccuracy));
			break;
		}
	case WEAPON_P90:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.3) * (m_flAccuracy));
			else if(iSpeed > 170)
				flSpread = ((0.115) * (m_flAccuracy));
			else
				flSpread = ((0.045) * (m_flAccuracy));
			break;
		}
	case WEAPON_SCOUT:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = 0.2;
			else if(iSpeed > 170)
				flSpread = 0.075;
			else if((iFlags &FL_DUCKING))
				flSpread = 0.0;
			else
				flSpread = 0.007;

			if( m_Fov >= 80.0f )
				flSpread += 0.025;
			break;
		}
	case WEAPON_SG550:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.45) * (1 - m_flAccuracy));
			else if(iSpeed > 5)
				flSpread = 0.15;
			else if((iFlags &FL_DUCKING))
				flSpread = ((0.04) * (1 - m_flAccuracy));
			else
				flSpread = ((0.05) * (1 - m_flAccuracy));
			
	if( m_Fov >= 80.0f )
			flSpread += 0.025;
			break;
		}
	case WEAPON_SG552:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = (0.035 + (0.45) * (m_flAccuracy));
			else if(iSpeed > 140)
				flSpread = (0.035 + (0.075) * (m_flAccuracy));
			else
				flSpread = ((0.02) * (m_flAccuracy));
			break;
		} 
	case WEAPON_TMP:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.25) * (m_flAccuracy));
			else
				flSpread = ((0.03) * (m_flAccuracy));
			break;		
		}
	case WEAPON_UMP45:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.24) * (m_flAccuracy));
			else
				flSpread = ((0.04) * (m_flAccuracy));
			break;
		}
	case WEAPON_USP45:
		{
			if(m_bWeaponBitPistol)
			{
				if(!(iFlags &FL_ONGROUND))
					flSpread = ((1.3) * (1 - m_flAccuracy));
				else if(iSpeed > 5)
					flSpread = ((0.25) * (1 - m_flAccuracy));
				else if((iFlags &FL_DUCKING))
					flSpread = ((0.125) * (1 - m_flAccuracy));
				else
					flSpread = ((0.15) * (1 - m_flAccuracy));
			}
			else
			{
				if(!(iFlags &FL_ONGROUND))
					flSpread = ((1.2) * (1 - m_flAccuracy));
				else if(iSpeed > 5)
					flSpread = ((0.225) * (1 - m_flAccuracy));
				else if((iFlags &FL_DUCKING))
					flSpread = ((0.08) * (1 - m_flAccuracy));
				else
					flSpread = ((0.1) * (1 - m_flAccuracy));
			}
			break;
		}
	case WEAPON_M3:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.25) * (m_flAccuracy));
			else
				flSpread = ((0.03) * (m_flAccuracy));
			break;
		}
	case WEAPON_XM1014:
		{
			if(!(iFlags &FL_ONGROUND))
				flSpread = ((0.25) * (m_flAccuracy));
			else
				flSpread = ((0.03) * (m_flAccuracy));
			break;	
		}
	default:
		{
			flSpread = 0.0f;
			break;
		}
	}
	return flSpread;
}
void cNoSpread::GetSpreadXY( UINT seed, float *vec )
{
	int iSeed = seed &255;
	iSeed++;
	RandomSeed(iSeed);
	vec[0] = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	vec[1] = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	float flSpread = GetVecSpread();
	vec[0] *= flSpread;
	vec[1] *= flSpread;
}
void cNoSpread::GetSpreadFix( UINT seed, float *fIn, float *fOut )
{
	float forward[3], right[3], up[3], vecDir[3];
	float view[3], dest[3], spread[2];
	AngleVectors(fIn, forward, right, up);
	GetSpreadXY(seed, spread);

	vecDir[0] = forward[0] + spread[0] * right[0] + spread[1] * up[0];
	view[0] = 8192 * vecDir[0];
	vecDir[1] = forward[1] + spread[0] * right[1] + spread[1] * up[1];
	view[1] = 8192 * vecDir[1];
	vecDir[2] = forward[2] + spread[0] * right[2] + spread[1] * up[2];
	view[2] = 8192 * vecDir[2];

	VectorAngles(view, dest);
	dest[0] *= -1;
	fOut[0] = fIn[0] - dest[0];
	fOut[1] = fIn[1] - dest[1];
	fOut[2] = 0;
}
void cNoSpread::AngleVectors (const float *angles, float *forward, float *right, float *up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos( DEG2RAD( angles[YAW] ), &sy, &cy );
	SinCos( DEG2RAD( angles[PITCH] ), &sp, &cp );
	SinCos( DEG2RAD( angles[ROLL] ), &sr, &cr );

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}

	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}

	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}

void cNoSpread::VectorAngles( const float *forward, float *angles )
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		pitch = 0;
	}
	else
	{
		yaw = atan2(forward[1], forward[0]) * 180 / M_PI;
		if (yaw < 0)
			yaw += 360;
		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = atan2(forward[2], tmp) * 180 / M_PI;
	}
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
//---------------------------------------------------------
// Take a vector (direction) and another vector (spread) 
// and modify the direction to point somewhere within the 
// spread. This used to live inside FireBullets.
//---------------------------------------------------------
inline const Vector &CShotManipulator::ApplySpread( const Vector &vecSpread, float bias )
{
	// get circular gaussian spread
	float x, y, z;

	if ( bias > 1.0 )
		bias = 1.0;
	else if ( bias < 0.0 )
		bias = 0.0;

	float shotBiasMin = 1.0f;
	float shotBiasMax = 1.0f;

	// 1.0 gaussian, 0.0 is flat, -1.0 is inverse gaussian
	float shotBias = ( ( shotBiasMax - shotBiasMin ) * bias ) + shotBiasMin;

	float flatness = ( fabsf(shotBias) * 0.5 );

	do
	{
		x = RandomFloat(-1,1) * flatness + RandomFloat(-1,1) * (1 - flatness);
		y = RandomFloat(-1,1) * flatness + RandomFloat(-1,1) * (1 - flatness);
		if ( shotBias < 0 )
		{
			x = ( x >= 0 ) ? 1.0 - x : -1.0 - x;
			y = ( y >= 0 ) ? 1.0 - y : -1.0 - y;
		}
		z = x*x+y*y;
	} while (z > 1);

	m_vecResult = m_vecShotDirection + x * vecSpread.x * m_vecRight + y * vecSpread.y * m_vecUp;

	return m_vecResult;
}

void cNoSpread::GetGausSpread ( UINT seed, float *vec )
{
	// get circular gaussian spread
	float x, y, z,bias = 1.0;

	if ( bias > 1.0 )
		bias = 1.0;
	else if ( bias < 0.0 )
		bias = 0.0;


	float shotBiasMin = 1.0;
	float shotBiasMax = 1.0;

	// 1.0 gaussian, 0.0 is flat, -1.0 is inverse gaussian
	float shotBias = ( ( shotBiasMax - shotBiasMin ) * bias ) + shotBiasMin;

	float flatness = ( fabsf(shotBias) * 0.5 );

	int iSeed = seed &255;
	iSeed++;
	RandomSeed(iSeed);

	do
	{
		x = RandomFloat(-1,1) * flatness + RandomFloat(-1,1) * (1 - flatness);
		y = RandomFloat(-1,1) * flatness + RandomFloat(-1,1) * (1 - flatness);
		if ( shotBias < 0 )
		{
			x = ( x >= 0 ) ? 1.0 - x : -1.0 - x;
			y = ( y >= 0 ) ? 1.0 - y : -1.0 - y;
		}
		z = x*x+y*y;
	} while (z > 1);

	vec[0] = x;
	vec[1] = y;
}
