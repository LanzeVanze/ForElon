
#include <windows.h>
#include "cWeaponTools.h"
//LOLOLO; I SUX


bool cWeaponTools::IsCurWepPistol()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "pist"))
			return true;
	}
	return false;
}
bool cWeaponTools::IsCurWepSniper()
{

	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "snip"))
			return true;
	}
	return false;
}
bool cWeaponTools::IsCurWepRifle()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "rif") || strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "smg") || strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "mach"))
			return true;
	}
	return false;
}

bool cWeaponTools::IsCurWepShotGun()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "shot"))
			return true;
	}
	return false;
}

bool cWeaponTools::IsCurWepGrenade()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "eq"))
			return true;

		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "c4"))
			return true;
	}
	return false;
}

bool cWeaponTools::IsCurWepKnife()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "knife"))
			return true;
	}
	return false;
}

bool cWeaponTools::IsCurWepKnifeOrNade()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "eq") || strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "knife"))
			return true;
	}
	return false;
}

bool cWeaponTools::NotaWeapon()
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if (strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "rif")
			|| strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "pist")
			|| strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "snip")
			|| strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "smg")
			|| strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "shot")
			|| strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "mach")
			)
			return true;
	}
	return false;
}

bool cWeaponTools::IsAttacking(CUserCmd* cmd )
{
	if(cmd->buttons & IN_ATTACK)
		return true;
	return false;
}

bool cWeaponTools::IsJumping(CUserCmd* cmd )
{
	if(cmd->buttons & IN_JUMP)
		return true;
	return false;
}

bool cWeaponTools::IsOnGround()
{
	int *iMyFlAgs = (int*) ( (DWORD)base.m_pMyPlayer->BaseEnt() + (DWORD)0x2B4 );
	int iFlags = *iMyFlAgs;
	if (iFlags &FL_ONGROUND)
		return true;
	return false;
}

bool cWeaponTools::IsDefusing(CUserCmd* cmd )//defusing or planting...needed this for my anti aim
{
	C_BaseCombatWeapon* m_pCurWeapon = base.m_pUtil->GetBaseCombatActiveWeapon ( base.m_pMyPlayer->BaseEnt() );
	if (m_pCurWeapon)
	{
		if ( strstr(base.m_pModelinfo->GetModelName ( m_pCurWeapon->GetModel()), "c4") || (cmd->buttons & IN_USE))
			return true;
	}
	return false;
}


