#ifndef _SDK_H_
#define _SDK_H_
#define CLIENT_DLL


#pragma comment ( lib, "SDK/ImportLibrarys/vstdlib.lib" )
#pragma comment ( lib, "SDK/ImportLibrarys/vgui_controls.lib" )

//disable shit error
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )

extern char DllPath[2048];

#define DO_ONCE( arg )				\
	static bool UnIqUe_ONC3 = false;\
	if( UnIqUe_ONC3 == false )\
{									\
	UnIqUe_ONC3 = true;				\
	arg								\
}


#define HOOK_CLIENT( x ) \
	MEMORY_BASIC_INFORMATION mb##x; \
	VirtualQuery( ( LPVOID )&g_pHookedClient->##x, &mb##x, sizeof( mb##x ) ); \
	VirtualProtect( mb##x.BaseAddress, mb##x.RegionSize, PAGE_EXECUTE_READWRITE, &mb##x.Protect ); \
	g_pHookedClient->##x = &n##x; \
	VirtualProtect( mb##x.BaseAddress, mb##x.RegionSize, mb##x.Protect, NULL ); \
	FlushInstructionCache( GetCurrentProcess( ), ( LPCVOID )&g_pHookedClient->##x, sizeof( DWORD ) );


//win32
#include <windows.h>
#include <tlhelp32.h>
#include <winsock.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#include <istream>
#include <string.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)
#include <Security.h>
#include <shlwapi.h>

//hack files (game sdk)
#include "SDK/cdll_int.h"
#include "SDK/iprediction.h"
#include "SDK/cl_dll/imessagechars.h"
#include "SDK/cl_dll/iclientmode.h"
#include "SDK/cl_dll/cliententitylist.h"
#include "SDK/cl_dll/cdll_client_int.h"
#include "SDK/cl_dll/cbase.h"
#include "SDK/bone_setup.h"
#include "SDK/cl_dll/c_baseanimating.h"
#include "SDK/cl_dll/c_basecombatweapon.h"
#include "SDK/cl_dll/c_baseplayer.h"
#include "SDK/cl_dll/enginesprite.h"
#include "SDK/icliententitylist.h"
#include "SDK/engine/ivmodelrender.h"
#include "SDK/engine/ivdebugoverlay.h"
//#include "SDK/engine/iserverplugin.h"
#include "SDK/materialsystem/imaterialsystemstub.h"
#include "SDK/engine/ivmodelinfo.h"
#include "SDK/ienginevgui.h"
#include "SDK/vgui/IClientPanel.h"
#include "SDK/vgui/IPanel.h"
#include "SDK/vgui/ISurface.h"
#include "SDK/vgui_controls/Panel.h"
#include "SDK/engine/IEngineTrace.h"
#include "SDK/IGameUIFuncs.h"
#include "SDK/VGuiMatSurface/IMatSystemSurface.h"
#include "SDK/input.h"
#include "SDK/game_shared/usermessages.h"
#include "SDK/game_shared/basecombatweapon_shared.h"
#include "SDK/game_shared/takedamageinfo.h"
#include "SDK/dlight.h"
#include "SDK/iefx.h" 
#include "SDK/igameevents.h"
#include "SDK/materialsystem/itexture.h"
#include "SDK/materialsystem/IMaterialVar.h"
#include "SDK/vgui/ILocalize.h"
#include "SDK/view_shared.h"
#include "SDK/cl_dll/iviewrender.h"
#include "SDK/cl_dll/viewrender.h"
#include "SDK/cl_dll/game_controls/commandmenu.h"//ovmap
#include "SDK/istudiorender.h"
#include "SDK/cl_dll/hudelement.h"
#include "SDK/GameUI/IGameConsole.h"
#include "SDK/icvar.h"
#include "SDK/tier1/convar.h"
#include "SDK/inetchannelinfo.h"

#include <tchar.h>

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)

#define	HIDEHUD_WEAPONSELECTION		( 1<<0 )	// Hide ammo count & weapon selection
#define	HIDEHUD_FLASHLIGHT			( 1<<1 )
#define	HIDEHUD_ALL					( 1<<2 )
#define HIDEHUD_HEALTH				( 1<<3 )	// Hide health & armor / suit battery
#define HIDEHUD_PLAYERDEAD			( 1<<4 )	// Hide when local player's dead
#define HIDEHUD_NEEDSUIT			( 1<<5 )	// Hide when the local player doesn't have the HEV suit
#define HIDEHUD_MISCSTATUS			( 1<<6 )	// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
#define HIDEHUD_CHAT				( 1<<7 )	// Hide all communication elements (saytext, voice icon, etc)
#define	HIDEHUD_CROSSHAIR			( 1<<8 )	// Hide crosshairs
#define	HIDEHUD_VEHICLE_CROSSHAIR	( 1<<9 )	// Hide vehicle crosshair
#define HIDEHUD_INVEHICLE			( 1<<10 )
#define HIDEHUD_SCOPE				( 1<<11 )

//cred to pato for these macros, and the whole color code thing


//like dll main
void add_log(const char * fmt, ...);

#define LOG( x ) add_log("%s [0x%X]", #x, x );


extern CreateInterfaceFn g_AppSysFactory;

#define M_RADPI 57.295779513082f
#define SQUARE( a ) a*a
#include "cXorString.h"
//Cheat Header
#include "basehook.h"
#include "client.h"
#include "Panels.h"
#include "utils.h"
#include "CAimbot.h"
#include "Colour.h"
#include "cCvars.h"
#include "cNoSpread.h"
#include "cMenu.h"
#include "cSettings.h"
#include "gui.h"
#include "SoundHook.h"
#include "cRadar.h"
#include "VisualRecoil.h"
#include "AntiAim.h"
#include "cWinamp.h"
#include "cCrossHairManager.h"
#include "cRemovals.h"
#include "cWallHack.h"
#include "cWindow.h"
#include "cForceCvar.h"
#include "cWeaponTools.h"
#include "Credits.h"
#include "cAntiLeak.h"
#endif