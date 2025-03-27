#include "basehook.h"

BaseHook	base;

BaseHook::BaseHook()
{
	base.m_pHl2GameConsole =			new CConsole();
	base.m_pDrawzLayer =				new CDrawLayer();
	base.m_pMyPlayer =					new LocalPlayer();
	base.m_pUtil =						new Util();	
	base.m_pAimbot =					new cCAimbot();
	base.m_pNoSpread =					new cNoSpread();
	base.m_psCvar =						new	sCvars();
	base.m_pMenu =                      new cMenu();
	base.m_pSettings =                  new cSettings();
	base.m_pGui =						new cGui();
	base.m_pSound =                     new cSoundHook();
	base.m_pRadar =                     new cRadar();
	base.m_pRecoil =					new VisualPunchangleRemoval();
	base.m_pWinamp =					new cWinamp();
	base.m_pCross =						new cCross();
	base.m_pAntiAim =					new AntiAim();
	base.m_pRemovals =					new cRemovals();
	base.m_pWallHack =					new WallHack();
	base.m_pForceCvar =					new CvarForce();
	base.m_pGuiWindow =					new GuiWindow();
	base.m_pWeapon =					new cWeaponTools();
	base.m_pCredits =					new Credits();
	base.m_pAL =						new cAL;
}