#ifndef __CWEAPONTOOLS_H_
#define __CWEAPONTOOLS_H_
#include "sdk.h"

class cWeaponTools
{
public:
	bool IsCurWepPistol();
	bool IsCurWepSniper();
	bool IsCurWepRifle();
	bool IsAttacking(CUserCmd* cmd );
	bool IsJumping(CUserCmd* cmd );
	bool IsOnGround();
	bool IsCurWepShotGun();
	bool IsCurWepGrenade();
	bool IsCurWepKnife();
	bool IsDefusing(CUserCmd* cmd );
	bool IsCurWepKnifeOrNade();
	bool NotaWeapon();
};
#endif