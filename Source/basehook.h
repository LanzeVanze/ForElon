#ifndef __BASEHOOK_H__
#define __BASEHOOK_H__

#include "sdk.h"
//=====================================
class LocalPlayer;
class CDrawLayer;
class Util;
class CConsole;
class Esp;
class cNoSpread;
class cCAimbot;
class cMenu;
class cSettings;
class cGui;
class cSoundHook;
class VisualPunchangleRemoval;
class cRadar;
class cWinamp;
class AntiAim;
class cCross;
class CvarForce;
class GuiWindow;
class WallHack;
class cWeaponTools;
class Credits;
class cRemovals;
class cAL;
struct sCvars;
//=====================================
class BaseHook
{	
public:
	BaseHook::BaseHook();
	IBaseClientDLL*			m_pClient;
	IVRenderView*			m_pRender;
	IFileSystem*			m_pFileSystem;
	IPrediction*			m_pPrediction;
	IVModelRender*			m_pModelRender;
	IClientEntityList*		m_pEntList;
	IMatSystemSurface*		m_pMatSurface;
	vgui::ISurface*			m_pSurface;
	IVEfx*					m_pEffects;
	ICvar*					m_pCvar;
	IVEngineClient*			m_pEngine;
	IEngineTrace*			m_pEnginetrace;
	IVModelInfoClient*		m_pModelinfo;
	IEngineVGui*			m_pEnginevgui;
	IVDebugOverlay*			m_pDebugOverlay;
	CInput*					m_pInput;
	CGlobalVarsBase*		m_pGlobals;
	IGameEventManager2*		m_pGameEventManager;
	IMaterialSystem*		m_pMaterialSystem;
	IPhysicsSurfaceProps*	m_pPhysicAPI;
	IStudioRender*			m_pStudioRender;
	IGameConsole*			m_pGameConsole;	
	IShadowMgr*				m_pShadowMgr;
	IGameUIFuncs*			m_pGameUIFuncs;
	IUniformRandomStream*   m_pRandom;
public:
	LocalPlayer*			m_pMyPlayer;		
	CDrawLayer*				m_pDrawzLayer;		
	Util*					m_pUtil;			
	CConsole*				m_pHl2GameConsole;	
	cNoSpread*				m_pNoSpread;		
	cMenu*					m_pMenu;	
	cCAimbot*				m_pAimbot;			
	sCvars*					m_psCvar;		
	cSettings*				m_pSettings;	
	cGui*					m_pGui;
	cSoundHook*             m_pSound;
	cRadar*                 m_pRadar;
	VisualPunchangleRemoval* m_pRecoil;
	cWinamp*				m_pWinamp;
	AntiAim*				m_pAntiAim;
	cCross*					m_pCross;
	CvarForce*				m_pForceCvar;
	WallHack*				m_pWallHack;
	cRemovals*				m_pRemovals;
	GuiWindow*				m_pGuiWindow;
	cWeaponTools*			m_pWeapon;
	Credits*				m_pCredits;
	cAL*					m_pAL;
}; 

extern BaseHook base;

class LocalPlayer
{
public:
	//=====================================
	inline IClientEntity *Ent( void ) const
	{
		return base.m_pEntList->GetClientEntity( base.m_pEngine->GetLocalPlayer() );
	}
	inline C_BaseEntity *BaseEnt( void ) const
	{
		return Ent()->GetBaseEntity();
	}
	inline IClientRenderable *RenderPlayer( void ) const
	{
		return Ent()->GetClientRenderable();
	}
	//=====================================
};

class CConsole
{
public:
	void Init( void )
	{
		DO_ONCE	
		(	
			base.m_pGameConsole = NULL;
			memset(m_szBuf, 0, sizeof(m_szBuf));
		);
		
		if( base.m_pGameConsole == NULL )
		{
			CreateInterfaceFn gameUIFactory =		(CreateInterfaceFn)GetProcAddress(	GetModuleHandle("gameui.dll"),				"CreateInterface"	);
			base.m_pGameConsole = (IGameConsole *)gameUIFactory(/*GameConsole003*/XorStr<0xA8,15,0x9503C61C>("\xEF\xC8\xC7\xCE\xEF\xC2\xC0\xDC\xDF\xDD\xD7\x83\x84\x86"+0x9503C61C).s, NULL);
			//add_log( "m_pGameConsole: [0x%.8X]", (DWORD)base.m_pGameConsole );
		}
	}
	// returns true if console has focus
	bool IsVisible ( void ){return base.m_pGameConsole->IsConsoleVisible();}
	void Activiate ( void ){base.m_pGameConsole->Activate();}
	void ColorPrint( int r, int g, int b, char* szText ){Color clr(r,g,b,255);base.m_pGameConsole->ColorPrintf(clr,szText);}
	void RandomColorPrint( char* szText ){Color clr((1 + (rand() % 254)),(1 + (rand() % 254)),(1 + (rand() % 254)),255);base.m_pGameConsole->ColorPrintf(clr,szText);}
	void Printf( const char *fmt, ... ){va_list	va_alist;va_start(va_alist, fmt);vsprintf(m_szBuf, fmt, va_alist);va_end(va_alist);/*Game console needs a \n else whatever is printed next is printed on the same line*/strcat(m_szBuf, "\n");base.m_pGameConsole->Printf(m_szBuf);}
	void ErrorPrintf( const char *fmt, ... ){va_list	va_alist;va_start(va_alist, fmt);vsprintf(m_szBuf, fmt, va_alist);va_end(va_alist);strcat(m_szBuf, "\n");Color clr(255,0,0,255);base.m_pGameConsole->ColorPrintf(clr,m_szBuf);}
	int iGetLineCount( void ){return m_iLineCount;}
private:
	// format buffer
	int	m_iLineCount;
	char m_szBuf[3064];
};


#endif