
#include "sdk.h"

#ifndef CVAR_H
#define CVAR_H

struct sCvars
{
	float asdf;

	/*~|Aim Cvars|~*/
	float aim_smooth;
	float aim_nospread;
	float aim_norecoil;
	float aim_key;
	float aim_shoot;
	float aim_allways;
	float aim_by_distance;
	float aim_method;
	float aim_hdj;
	float aim_hitbox;
	float aim_fov;
	float aim_silent;
	float aim_thru;

	/*~|Esp Cvars|~*/
	float esp_name;
	float esp_health;
	float esp_armor;
	float esp_barrel;
	float esp_weapon;
	float esp_box;
	float esp_radar;
	float esp_sound;
	float esp_show_enemys_only;


	/*~|Vis Cvars|~*/
	float vis_noflash;
	float vis_nohands;
	float vis_xqzmodels;
	float vis_recoil;
	float vis_nosky;
	float vis_noscope;
	float vis_chams;
	float vis_crosshair;

	/*~|Misc Cvars|~*/
	float misc_autopistol;
	float misc_bunnyhop;
	float misc_anti_aim;
	float misc_spinbot;
	float misc_spam;
	float misc_winamp;



	/*~|Radar Cvars|~*/
	float radar_x;
	float radar_y;
	float radar_size;
	float radar_range;
	float radar;

};


#endif