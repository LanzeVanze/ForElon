//#define _NOT_LOG
#include "sdk.h"

#define _Sleep Sleep
#define _CreateThread CreateThread
#define _GetModuleHandle GetModuleHandle
#define _GetProcAddress GetProcAddress
#define _CreateInterfaceFn CreateInterfaceFn


CClient		gClient;
CClient*	g_pHookedClient = new CClient;

_CreateInterfaceFn				g_AppSysFactory					= NULL;
_CreateInterfaceFn				ClientFactory					= NULL;
_CreateInterfaceFn				EngineFactory					= NULL;
_CreateInterfaceFn				PhysicFactory					= NULL;
_CreateInterfaceFn				FileSystemFactory				= NULL;
_CreateInterfaceFn				StudioFactory					= NULL;
_CreateInterfaceFn				MaterialFactory					= NULL;
_CreateInterfaceFn				VGUIFactory						= NULL;

void* AppSysFactory( const char* pszName, int* piRetnCode )
{
	void* lpReturn = g_AppSysFactory( pszName, piRetnCode );
	DO_ONCE
	(

		if( vgui::VGui_InitInterfacesList( "CLIENT", &g_AppSysFactory, 1 ) == false )
			exit(0);

		vgui::VGui_InitInterfacesList( "CLIENT", &g_AppSysFactory, 1 );
		if ( lpReturn )
		{
			if( strcmp( pszName,XorStr<0xB9,16,0x0A743513>("\xEF\xFD\xEE\xF5\xE2\xED\xCA\xB2\xA7\xA3\xA0\xA1\xF5\xF5\xF7"+0x0A743513).s ) )
			{
				base.m_pSurface	= (vgui::ISurface*)lpReturn; 
				base.m_pMatSurface			= ( IMatSystemSurface* )vgui::surface();
			}
		}
	);
	return ( void* )lpReturn;
}

int	__stdcall new_Init( _CreateInterfaceFn appSystemFactory, _CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals )
{
	g_AppSysFactory = appSystemFactory;
	base.m_pGlobals = pGlobals;
	return gClient.Init( AppSysFactory, physicsFactory, pGlobals );
}

DWORD WINAPI dwCreateHook( LPVOID )
{
	while( FindWindow( "Valve001", NULL ) == NULL )
		Sleep( 10 );

	while( GetModuleHandle( "client.dll" ) == NULL)
		Sleep( 10 );

	ClientFactory		=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("client.dll"),				"CreateInterface"	);
	EngineFactory		=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("engine.dll"),				"CreateInterface"	);
	PhysicFactory		=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("vphysics.dll"),			"CreateInterface"	);
	FileSystemFactory	=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("FileSystem_Steam.dll"),	"CreateInterface"	);
	StudioFactory		=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("StudioRender.dll"),		"CreateInterface"	);
	MaterialFactory		=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("MaterialSystem.dll"),		"CreateInterface"	);
	VGUIFactory			=		(_CreateInterfaceFn)	_GetProcAddress(		_GetModuleHandle("vguimatsurface.dll"),		"CreateInterface"	);


	if( base.m_pClient == NULL )
	{
		base.m_pClient = (IBaseClientDLL*)ClientFactory( CLIENT_DLL_INTERFACE_VERSION , NULL );
		if( base.m_pClient )
		{
			DWORD dwOld			= NULL;
			DWORD dwOld1		= NULL;
			DWORD dwOld2		= NULL;

			PDWORD* m_pdwClient = (PDWORD*)ClientFactory( CLIENT_DLL_INTERFACE_VERSION , NULL );

			if ( m_pdwClient )
			{
				memcpy( (void*) &gClient,(void*)*m_pdwClient , sizeof (CClient) );
				g_pHookedClient = (CClient*)*m_pdwClient;
				if( g_pHookedClient )
				{
					if( VirtualProtect( (LPVOID)&g_pHookedClient->Init, 4, PAGE_EXECUTE_READWRITE, &dwOld ) )
						g_pHookedClient->Init = &new_Init;

					if( VirtualProtect( (LPVOID)&g_pHookedClient->CreateMove, 4, PAGE_EXECUTE_READWRITE, &dwOld1 ) )
						g_pHookedClient->CreateMove = &new_CreateMove;

					if( VirtualProtect( (LPVOID)&g_pHookedClient->HudUpdate, 4, PAGE_EXECUTE_READWRITE, &dwOld2 ) )
						g_pHookedClient->HudUpdate = &new_HudUpdate;

					if ( base.m_pInput == NULL )
					{
						PDWORD pdwAddress = ( PDWORD ) ((( DWORD ) gClient.CreateMove ) + 0x20 );
						PDWORD pdwTable = ( PDWORD ) *pdwAddress;
						base.m_pInput = ( CInput* ) *pdwTable;
					}
					if( base.m_pPrediction == NULL )
						base.m_pPrediction = (IPrediction*)ClientFactory(XorStr<0xB2,21,0x2EB94818>("\xE4\xF0\xD8\xDC\xD3\xD9\xCC\xE9\xC8\xDE\xD8\xD4\xDD\xCB\xA9\xAE\xAC\xF3\xF4\xF4"+0x2EB94818).s, NULL);	
					if( base.m_pEntList == NULL )
						base.m_pEntList = (IClientEntityList*)ClientFactory(XorStr<0x4B,21,0x5AE1D2F4>("\x1D\x0F\x21\x27\x2A\x3E\x25\x17\x3D\x20\x3C\x22\x2E\x14\x30\x29\x2F\x6C\x6D\x6D"+0x5AE1D2F4).s, NULL);
				}
			}
		}
	}
	if( base.m_pEngine == NULL )
		base.m_pEngine = (IVEngineClient*)EngineFactory(XorStr<0x8F,17,0xA30624DD>("\xD9\xD5\xFF\xF5\xFA\xFA\xF0\xD5\xFB\xF1\xFC\xF4\xEF\xAC\xAC\xAC"+0xA30624DD).s, NULL);
	if( base.m_pEnginevgui == NULL )
		base.m_pEnginevgui = (IEngineVGui*)EngineFactory(XorStr<0x19,15,0x902ED4F1>("\x4F\x5F\x75\x7B\x74\x70\x7A\x76\x66\x57\x4A\x14\x15\x17"+0x902ED4F1).s, NULL);
	if( base.m_pEnginetrace == NULL )
		base.m_pEnginetrace = (IEngineTrace*)EngineFactory(XorStr<0x3B,21,0x0E67DC6F>("\x7E\x52\x5A\x57\x51\x25\x15\x30\x22\x27\x20\x05\x2B\x21\x2C\x24\x3F\x7C\x7D\x7D"+0x0E67DC6F).s, NULL);
	if( base.m_pEffects == NULL )
		base.m_pEffects = (IVEfx*)EngineFactory(XorStr<0xE4,18,0xEACC4256>("\xB2\xA0\x88\x80\x81\x87\x8F\xAE\x8A\x8B\x8B\x8C\x84\x82\xC2\xC3\xC5"+0xEACC4256).s, NULL);
	if( base.m_pStudioRender == NULL )
		base.m_pStudioRender = (IStudioRender *)StudioFactory(STUDIO_RENDER_INTERFACE_VERSION, NULL);
	if( base.m_pFileSystem == NULL )
		base.m_pFileSystem = (IFileSystem*)FileSystemFactory(XorStr<0x10,15,0xC84390E7>("\x46\x57\x7B\x7F\x71\x46\x6F\x64\x6C\x7C\x77\x2B\x2D\x2F"+0xC84390E7).s, NULL);
	if( base.m_pRender == NULL )
		base.m_pRender = (IVRenderView*)EngineFactory(XorStr<0x09,21,0x600A7C11>("\x5F\x4F\x65\x6B\x64\x60\x6A\x42\x74\x7C\x77\x71\x67\x40\x7E\x7D\x6E\x2A\x2A\x2E"+0x600A7C11).s, NULL);
	if( base.m_pPhysicAPI == NULL )
		base.m_pPhysicAPI = (IPhysicsSurfaceProps *)PhysicFactory(VPHYSICS_SURFACEPROPS_INTERFACE_VERSION, NULL);
	if( base.m_pCvar == NULL )
		base.m_pCvar = (ICvar *)EngineFactory(VENGINE_CVAR_INTERFACE_VERSION, NULL);
	if( base.m_pModelRender == NULL )
		base.m_pModelRender = (IVModelRender*)EngineFactory(XorStr<0xB3,16,0x6732F784>("\xE5\xF1\xDB\xD1\xDE\xD6\xDC\xF7\xD4\xD8\xD8\xD2\x8F\xF1\xF3"+0x6732F784).s, NULL);
	if( base.m_pMaterialSystem == NULL )
		base.m_pMaterialSystem = (IMaterialSystem*)MaterialFactory(XorStr<0x77,19,0xC549E0C4>("\x21\x35\x18\x0E\x1E\x0E\x14\x1F\x13\xD3\xF8\xF1\xF7\xE1\xE8\xB6\xB0\xBE"+0xC549E0C4).s, NULL);
	if( base.m_pModelinfo == NULL )
		base.m_pModelinfo	= (IVModelInfoClient*)EngineFactory(XorStr<0x0F,20,0x4A40A445>("\x59\x5D\x7E\x76\x76\x78\x5C\x78\x71\x77\x5A\x76\x72\x79\x73\x6A\x2F\x10\x12"+0x4A40A445).s, NULL );
	if( base.m_pDebugOverlay == NULL )
		base.m_pDebugOverlay = (IVDebugOverlay*)EngineFactory(XorStr<0x11,17,0xA54434BF>("\x47\x56\x76\x76\x60\x71\x58\x6E\x7C\x68\x77\x7D\x64\x2E\x2F\x13"+0xA54434BF).s, NULL );
	if( base.m_pGameEventManager == NULL )	
		base.m_pGameEventManager = (IGameEventManager2*) EngineFactory(XorStr<0xCE,21,0x1BADB9A7>("\x89\x8E\x9D\x94\x97\x85\x91\x9B\x82\x84\x95\x98\x94\x9A\x9B\x98\x8C\xEF\xD0\xD3"+0x1BADB9A7).s, NULL );
	if( base.m_pShadowMgr == NULL )
		base.m_pShadowMgr = ( IShadowMgr* )EngineFactory( ENGINE_SHADOWMGR_INTERFACE_VERSION, NULL );
	if( base.m_pGameUIFuncs == NULL )
		base.m_pGameUIFuncs = ( IGameUIFuncs* )EngineFactory( VENGINE_GAMEUIFUNCS_VERSION, NULL );
	if( base.m_pRandom == NULL )
		base.m_pRandom = ( IUniformRandomStream* )EngineFactory( VENGINE_CLIENT_RANDOM_INTERFACE_VERSION, NULL );

	LOG(base.m_pGameUIFuncs);
	LOG(base.m_pShadowMgr);
	return 0;
}


BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH  )
	{

		base.m_pSettings->GetIniFile((HMODULE)hinstDLL);
		base.m_pSettings->LogFile((HMODULE)hinstDLL);
		CreateThread(0,0, dwCreateHook ,0,0, 0);
		if(((PIMAGE_DOS_HEADER)(hinstDLL))->e_magic == IMAGE_DOS_SIGNATURE)//apply teh proofens
		{
			base.m_pUtil->HideModule((HMODULE)hinstDLL);
			base.m_pUtil->ErasePEHeader((HMODULE)hinstDLL);
		}
	}
	return TRUE;
}

void __cdecl add_log(const char * fmt, ...)
{
#ifndef _NOT_LOG
	va_list va_alist;
	char logbuf[256];
	FILE * fp;
	struct tm * current_tm;
	time_t current_time;

	time (&current_time);
	current_tm = localtime (&current_time);

	sprintf (logbuf, "[%02d:%02d:%02d] ", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);

	va_start (va_alist, fmt);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
	va_end (va_alist);

	if ( (fp = fopen ( szLogFile, "a")) != NULL )
	{
		fprintf ( fp, "%s\n", logbuf );
		fclose (fp);
	}
#endif
}