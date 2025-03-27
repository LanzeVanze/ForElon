#include "cSettings.h"



BOOL WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, int nInteger, LPCTSTR lpFileName)
{
    TCHAR lpString[ 1024 ];
    wsprintf( lpString, "%d", nInteger );
    return WritePrivateProfileString( lpAppName, lpKeyName, lpString, lpFileName );
}

void cSettings::SaveConfigs()
{
	//WritePrivateProfileInt (	 "Cvars", "aim_hitbox", base.m_psCvar->test, szIniFile);

	 WritePrivateProfileInt (	 "Cvars", "aim_smooth", base.m_psCvar->aim_smooth, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_nospread", base.m_psCvar->aim_nospread, szIniFile);
 	 WritePrivateProfileInt (	 "Cvars", "aim_norecoil", base.m_psCvar->aim_norecoil, szIniFile);
 	 WritePrivateProfileInt (	 "Cvars", "aim_key", base.m_psCvar->aim_key, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_shoot", base.m_psCvar->aim_shoot, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_allways", base.m_psCvar->aim_allways, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_by_distance", base.m_psCvar->aim_by_distance, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_method", base.m_psCvar->aim_method, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_hdj",base.m_psCvar->aim_hdj, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_hitbox", base.m_psCvar->aim_hitbox, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_fov", base.m_psCvar->aim_fov, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_silent", base.m_psCvar->aim_silent, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "aim_thru", base.m_psCvar->aim_thru, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_name", base.m_psCvar->esp_name, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_health", base.m_psCvar->esp_health, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_armor", base.m_psCvar->esp_armor, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_show_enemys_only", base.m_psCvar->esp_show_enemys_only, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_barrel",base.m_psCvar->esp_barrel, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_weapon", base.m_psCvar->esp_weapon, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_box", base.m_psCvar->esp_box, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "esp_sound",	base.m_psCvar->esp_sound, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_noflash", base.m_psCvar->vis_noflash, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_nohands", base.m_psCvar->vis_nohands, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_xqzmodels", base.m_psCvar->vis_xqzmodels, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_recoil", 	base.m_psCvar->vis_recoil, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_nosky", base.m_psCvar->vis_nosky, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_noscope", base.m_psCvar->vis_noscope, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_chams", base.m_psCvar->vis_chams, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "vis_crosshair", base.m_psCvar->vis_crosshair, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_autopistol", 	base.m_psCvar->misc_autopistol, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_bunnyhop", base.m_psCvar->misc_bunnyhop, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_anti_aim", base.m_psCvar->misc_anti_aim , szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_spinbot", base.m_psCvar->misc_spinbot, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_spam", base.m_psCvar->misc_spam, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "radar", base.m_psCvar->radar, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "radar_x", 	base.m_psCvar->radar_x, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "radar_y",base.m_psCvar->radar_y, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "radar_size", base.m_psCvar->radar_size, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "radar_range", base.m_psCvar->radar_range, szIniFile);
	 WritePrivateProfileInt (	 "Cvars", "misc_winamp", base.m_psCvar->misc_winamp, szIniFile);
	 
}


void cSettings::LoadConfigs()
{
	base.m_psCvar->aim_smooth = GetPrivateProfileInt (		 "Cvars", "aim_smooth", 0, szIniFile);
	base.m_psCvar->aim_nospread = GetPrivateProfileInt (	 "Cvars", "aim_nospread", 0, szIniFile);
	base.m_psCvar->aim_norecoil = GetPrivateProfileInt (	 "Cvars", "aim_norecoil", 0, szIniFile);
	base.m_psCvar->aim_key = GetPrivateProfileInt (			 "Cvars", "aim_key", 0, szIniFile);
	base.m_psCvar->aim_shoot = GetPrivateProfileInt (		 "Cvars", "aim_shoot", 0, szIniFile);
	base.m_psCvar->aim_allways = GetPrivateProfileInt (		 "Cvars", "aim_allways", 0, szIniFile);
	base.m_psCvar->aim_by_distance = GetPrivateProfileInt (	 "Cvars", "aim_by_distance", 0, szIniFile);
	base.m_psCvar->aim_method = GetPrivateProfileInt (		 "Cvars", "aim_method", 0, szIniFile);
	base.m_psCvar->aim_hdj = GetPrivateProfileInt (			 "Cvars", "aim_hdj", 0, szIniFile);
	base.m_psCvar->aim_hitbox = GetPrivateProfileInt (		 "Cvars", "aim_hitbox", 0, szIniFile);
	base.m_psCvar->aim_fov = GetPrivateProfileInt		(	 "Cvars", "aim_fov", 0, szIniFile);
	base.m_psCvar->aim_silent = GetPrivateProfileInt	(	 "Cvars", "aim_silent", 0, szIniFile);
	base.m_psCvar->aim_thru = GetPrivateProfileInt		(	 "Cvars", "aim_thru", 0, szIniFile);
	base.m_psCvar->esp_name = GetPrivateProfileInt		(	 "Cvars", "esp_name", 0, szIniFile);
	base.m_psCvar->esp_health = GetPrivateProfileInt	(	 "Cvars", "esp_health", 0, szIniFile);
	base.m_psCvar->esp_armor = GetPrivateProfileInt		(	 "Cvars", "esp_armor", 0, szIniFile);
	base.m_psCvar->esp_show_enemys_only = GetPrivateProfileInt (	 "Cvars", "esp_show_enemys_only", 0, szIniFile);
	base.m_psCvar->esp_barrel = GetPrivateProfileInt	(	 "Cvars", "esp_barrel", 0, szIniFile);
	base.m_psCvar->esp_weapon = GetPrivateProfileInt	(	 "Cvars", "esp_weapon", 0, szIniFile);
	base.m_psCvar->esp_box = GetPrivateProfileInt		 (	 "Cvars", "esp_box", 0, szIniFile);
	base.m_psCvar->esp_sound = GetPrivateProfileInt		(	 "Cvars", "esp_sound", 0, szIniFile);
	base.m_psCvar->vis_noflash = GetPrivateProfileInt	(	 "Cvars", "vis_noflash", 0, szIniFile);
	base.m_psCvar->vis_nohands = GetPrivateProfileInt	 (	 "Cvars", "vis_nohands", 0, szIniFile);
	base.m_psCvar->vis_xqzmodels = GetPrivateProfileInt (	 "Cvars", "vis_xqzmodels", 0, szIniFile);
	base.m_psCvar->vis_recoil = GetPrivateProfileInt	(	 "Cvars", "vis_recoil", 0, szIniFile);
	base.m_psCvar->vis_nosky = GetPrivateProfileInt		(	 "Cvars", "vis_nosky", 0, szIniFile);
	base.m_psCvar->vis_noscope = GetPrivateProfileInt	(	 "Cvars", "vis_noscope", 0, szIniFile);
	base.m_psCvar->vis_chams = GetPrivateProfileInt		(	 "Cvars", "vis_chams", 0, szIniFile);
	base.m_psCvar->vis_crosshair = GetPrivateProfileInt (	 "Cvars", "vis_crosshair", 0, szIniFile);
	base.m_psCvar->misc_autopistol = GetPrivateProfileInt (	 "Cvars", "misc_autopistol", 0, szIniFile);
	base.m_psCvar->misc_bunnyhop = GetPrivateProfileInt (	 "Cvars", "misc_bunnyhop", 0, szIniFile);
	base.m_psCvar->misc_anti_aim = GetPrivateProfileInt (	 "Cvars", "misc_anti_aim", 0, szIniFile);
	base.m_psCvar->misc_spinbot = GetPrivateProfileInt (	 "Cvars", "misc_spinbot", 0, szIniFile);
	base.m_psCvar->misc_spam = GetPrivateProfileInt		(	 "Cvars", "misc_spam", 0, szIniFile);
	base.m_psCvar->radar = GetPrivateProfileInt			(	 "Cvars", "radar", 0, szIniFile);
	base.m_psCvar->radar_x = GetPrivateProfileInt		(	 "Cvars", "radar_x", 0, szIniFile);
	base.m_psCvar->radar_y = GetPrivateProfileInt		(	 "Cvars", "radar_y", 0, szIniFile);
	base.m_psCvar->radar_size = GetPrivateProfileInt	(	 "Cvars", "radar_size", 0, szIniFile);
	base.m_psCvar->radar_range = GetPrivateProfileInt	 (	 "Cvars", "radar_range", 0, szIniFile);
	base.m_psCvar->misc_winamp = GetPrivateProfileInt	 (	 "Cvars", "misc_winamp", 0, szIniFile);
}

char szIniFile[256];
void cSettings::GetIniFile( HMODULE hModule )
{
	GetModuleFileName( hModule, szIniFile, sizeof( szIniFile ) );
	for( int i = 0; i < ( int )strlen( szIniFile ); i++ )
	{
		if( szIniFile[ strlen( szIniFile ) - i ] == '\\' )
		{
			szIniFile[ ( strlen( szIniFile ) -  i ) + 1 ] = '\0';
			strcat( szIniFile,"configs.cfg");
			return;
		}
	}
}


char szLogFile[256];
void cSettings::LogFile( HMODULE hModule )
{
	GetModuleFileName( hModule, szLogFile, sizeof( szLogFile ) );
	for( int i = 0; i < ( int )strlen( szLogFile ); i++ )
	{
		if( szLogFile[ strlen( szLogFile ) - i ] == '\\' )
		{
			szLogFile[ ( strlen( szLogFile ) -  i ) + 1 ] = '\0';
			strcat( szLogFile,"Hack_Debug_Log.log");
			return;
		}
	}
}


//notneded
char szFont[256];
void  cSettings::GetFont( HMODULE hModule )
{
	GetModuleFileName( hModule, szFont, sizeof( szFont ) );
	for( int i = 0; i < ( int )strlen( szFont ); i++ )
	{
		if( szFont[ strlen( szFont ) - i ] == '\\' )
		{
			szFont[ ( strlen( szFont ) -  i ) + 1 ] = '\0';
			strcat( szFont,"font\\visitor1.ttf");
			return;
		}
	}
}
