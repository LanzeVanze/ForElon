#include "SoundHook.h"

class cSoundName
{
public:
	virtual LPSTR getname();
	virtual VOID setname(LPSTR); // ?
};
/**********************************************************************************/
class cSoundInfo
{
public:
	DWORD u0;
	DWORD u1;
	DWORD Index; // ent. id
	DWORD u3;
	cSoundName *pName;
	Vector vOrigin;
	Vector vDirection;
	DWORD u11;
	DWORD u12;
	DWORD u13;
	DWORD u14;
	DWORD pitch;
};
/**********************************************************************************/
typedef struct
{
	std::string m_strSoundName;
	std::string m_strPlayerName;
	int			m_iTeam;
	int			m_iIndex;
	Vector		m_vOrigin;
	DWORD		m_dwTime;
}

/**********************************************************************************/
SoundMarker_t;
SoundMarker_t gSounds[64];
/**********************************************************************************/
typedef VOID (*StartDynamicSound_t)(cSoundInfo *);
StartDynamicSound_t pStartDynamicSound;
/**********************************************************************************/
void hk_StartDynamicSound( cSoundInfo *pSound )
{
	if( pSound && pSound->pName )
	{
		int iIndex = pSound->Index;	

		if ( iIndex < 0 || iIndex >= 64 )	
			return; 

		player_info_t pInfo; 

		if ( base.m_pEngine->GetPlayerInfo( iIndex, &pInfo ) && (iIndex != base.m_pEngine->GetLocalPlayer() ) )
		{
			SoundMarker_t& TempSound_s = gSounds[iIndex]; 

			IClientEntity* ClientEntity = base.m_pEntList->GetClientEntity( iIndex );
			if (	ClientEntity == NULL	||	ClientEntity->IsDormant() )
			return pStartDynamicSound( pSound );

			CBaseEntity* pBaseEntity = ClientEntity->GetBaseEntity();
			if (	pBaseEntity == NULL  ||	pBaseEntity->IsDormant() )
			return pStartDynamicSound( pSound );

			TempSound_s.m_strPlayerName = pInfo.name; 
			TempSound_s.m_iTeam			= *(int*) ((DWORD)pBaseEntity +(DWORD)0x90 ); 	
			TempSound_s.m_dwTime		= GetTickCount(); 		
			TempSound_s.m_vOrigin		= pSound->vOrigin; 		
			TempSound_s.m_iIndex		= iIndex; 		
			TempSound_s.m_strSoundName	= pSound->pName->getname(); 		 
		}	
		else
		{	
			SoundMarker_t& TempSound_s = gSounds[iIndex]; 

			if (strstr(pSound->pName->getname(), "c4"))
			{
				TempSound_s.m_strPlayerName = "C4"; 
				TempSound_s.m_iTeam			= 2;
			}
			else return pStartDynamicSound( pSound );
		 	
			TempSound_s.m_dwTime		= GetTickCount(); 
			TempSound_s.m_vOrigin		= pSound->vOrigin; 
			TempSound_s.m_iIndex		= iIndex; 
			TempSound_s.m_strSoundName	= pSound->pName->getname(); 	
		}
	}
	pStartDynamicSound( pSound );
}
/**********************************************************************************/
bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask ) 
			return false;
	return (*szMask) == NULL;
}
/**********************************************************************************/
DWORD dwFindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bDataCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
			return (DWORD)(dwAddress+i);

	return 0;
}
/**********************************************************************************/
void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len+5);
	DWORD dwback;

	while( VirtualProtect( src, len, PAGE_EXECUTE_READWRITE, &dwback ) == FALSE )
		Sleep( 1 );

	memcpy(jmp, src, len);	jmp += len;

	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	VirtualProtect(src, len, dwback, &dwback);

	return (jmp-len);
}
/**********************************************************************************/
void cSoundHook::HookSoundEsp()
{
	DWORD dwEngine = (DWORD)GetModuleHandle( "engine" );
	BYTE Sound_SIG[] = "\x55\x8B\xEC\x83\xE4\xF8\x81\xEC\x1C\x01\x00\x00\x8B\x0D\xD8\x43\x5C\x20\x85\xC9\x53\x56\x57";
	CHAR Sound_MSK[] = "xxxxxxxxxxxxxx????xxxxx";
	PBYTE pbStartDynamicSound = ( PBYTE )dwFindPattern( dwEngine, 0x300000, Sound_SIG, Sound_MSK );

	if(pbStartDynamicSound)
		pStartDynamicSound = ( StartDynamicSound_t ) DetourFunc( pbStartDynamicSound, ( PBYTE )hk_StartDynamicSound, 6 );
}
/**********************************************************************************/
void cSoundHook::DrawSoundEsp()
{
		for ( int i = 0; i < 64; i++ )
		{
			if ( gSounds[i].m_dwTime + 1000 < timeGetTime() )
				continue;
	
			DWORD TmColor = Color(255,255,255,100);

			if( gSounds[i].m_iTeam == 2 ) //Terrorist
			{
				TmColor = Color(255,0,0,150);
			}

			if( gSounds[i].m_iTeam == 3 )// Counter-Terrorist
			{
				TmColor = Color(0,0,255,150);
			}
			Vector vScreen;
			if ( base.m_pUtil->WorldToScreen( gSounds[i].m_vOrigin, vScreen ) )
			{
				base.m_pUtil->PrintText( vScreen.x, vScreen.y, TmColor, "%s", gSounds[i].m_strPlayerName.c_str() );
			}
		}
}