#include "utils.h"

void Util::FontInit( void )
{
	//font init

	m_ESPFont = base.m_pMatSurface->CreateFont();	
	base.m_pMatSurface->SetFontGlyphSet( m_ESPFont, "Ariel", 12, 450, 0, 0, 0x200 );

	m_pSpriteFont = base.m_pMatSurface->CreateFont();      
    base.m_pMatSurface->SetFontGlyphSet(m_pSpriteFont,"cs", 40, 40, 0, 0,0x100|0x200|0x080);
}

bool Util::ScreenTransform( const Vector &point, Vector &screen )
{
	float w;
	const VMatrix &worldToScreen = base.m_pEngine->WorldToScreenMatrix();
	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w		 = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}
	return behind;
}

bool Util::WorldToScreen( const Vector &vOrigin, Vector &vScreen )
{
	if( ScreenTransform(vOrigin , vScreen) == false )
	{
		int iScreenWidth, iScreenHeight;

		base.m_pEngine->GetScreenSize( iScreenWidth, iScreenHeight );
		float x = iScreenWidth / 2;
		float y = iScreenHeight / 2;
		x += 0.5 * vScreen.x * iScreenWidth + 0.5;
		y -= 0.5 * vScreen.y * iScreenHeight + 0.5;
		vScreen.x = x;
		vScreen.y = y;
		return true;
	}
	return false;
}

void Util::FillRGBA( int x, int y, int w, int h, DWORD dwColor )
{
	base.m_pMatSurface->DrawSetColor( RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor) );
	base.m_pMatSurface->DrawFilledRect( x, y, x + w, y + h );
}

void Util::PrintText( int x, int y, DWORD dwColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );

	base.m_pMatSurface->DrawColoredText( m_ESPFont, x, y, RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor), "%s", szBuffer );
}
void Util::DrawSprite( int x, int y, DWORD dwColor, const char *pszText, ... )
{
	if( pszText == NULL )
		return;

	va_list va_alist;
	char szBuffer[1024] = { '\0' };

	va_start( va_alist, pszText );
	vsprintf( szBuffer, pszText, va_alist );
	va_end( va_alist );

	base.m_pMatSurface->DrawColoredText( m_pSpriteFont, x, y, RED(dwColor), GREEN(dwColor), BLUE(dwColor), ALPHA(dwColor), "%s", szBuffer );
}


void Util::GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter )
{
	if ( pBaseEnt )
	{
		Vector vMin, vMax;
		pBaseEnt->GetRenderBounds( vMin, vMax );
		vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
		vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
	}
}
void Util::Normalize(Vector &vIn, Vector &vOut)
{
	float flLen = vIn.Length();
	if(flLen == 0)
	{
		vOut.Init(0, 0, 1);
		return;
	}
	flLen = 1 / flLen;
	vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

void Util::HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]		   // PEB
		mov eax, [eax+0Ch]		  // PEB->ProcessModuleInfo
		mov dwPEB_LDR_DATA, eax	 // Save ProcessModuleInfo

InLoadOrderModuleList:
		mov esi, [eax+0Ch]					  // ProcessModuleInfo->InLoadOrderModuleList[FORWARD]
		mov edx, [eax+10h]					  //  ProcessModuleInfo->InLoadOrderModuleList[BACKWARD]

		LoopInLoadOrderModuleList: 
		    lodsd							   //  Load First Module
			mov esi, eax		    			//  ESI points to Next Module
			mov ecx, [eax+18h]		    		//  LDR_MODULE->BaseAddress
			cmp ecx, hModule		    		//  Is it Our Module ?
			jne SkipA		    		    	//  If Not, Next Please (@f jumps to nearest Unamed Lable @@:)
		    	mov ebx, [eax]				  //  [FORWARD] Module 
		    	mov ecx, [eax+4]    		    	//  [BACKWARD] Module
		    	mov [ecx], ebx				  //  Previous Module's [FORWARD] Notation, Points to us, Replace it with, Module++
		    	mov [ebx+4], ecx			    //  Next Modules, [BACKWARD] Notation, Points to us, Replace it with, Module--
			jmp InMemoryOrderModuleList		//  Hidden, so Move onto Next Set
		SkipA:
			cmp edx, esi					    //  Reached End of Modules ?
			jne LoopInLoadOrderModuleList		//  If Not, Re Loop

InMemoryOrderModuleList:
		mov eax, dwPEB_LDR_DATA		  //  PEB->ProcessModuleInfo
		mov esi, [eax+14h]			   //  ProcessModuleInfo->InMemoryOrderModuleList[START]
		mov edx, [eax+18h]			   //  ProcessModuleInfo->InMemoryOrderModuleList[FINISH]

		LoopInMemoryOrderModuleList: 
			lodsd
			mov esi, eax
			mov ecx, [eax+10h]
			cmp ecx, hModule
			jne SkipB
				mov ebx, [eax] 
				mov ecx, [eax+4]
				mov [ecx], ebx
				mov [ebx+4], ecx
				jmp InInitializationOrderModuleList
		SkipB:
			cmp edx, esi
			jne LoopInMemoryOrderModuleList

InInitializationOrderModuleList:
		mov eax, dwPEB_LDR_DATA				    //  PEB->ProcessModuleInfo
		mov esi, [eax+1Ch]						 //  ProcessModuleInfo->InInitializationOrderModuleList[START]
		mov edx, [eax+20h]						 //  ProcessModuleInfo->InInitializationOrderModuleList[FINISH]

		LoopInInitializationOrderModuleList: 
			lodsd
			mov esi, eax		
			mov ecx, [eax+08h]
			cmp ecx, hModule		
			jne SkipC
				mov ebx, [eax] 
				mov ecx, [eax+4]
				mov [ecx], ebx
				mov [ebx+4], ecx
				jmp Finished
		SkipC:
			cmp edx, esi
			jne LoopInInitializationOrderModuleList

		Finished:
			popfd;
			popad;
	}
}

#define MakePtr( cast, ptr, addValue )( cast )( ( DWORD )( ptr ) + ( DWORD )( addValue ) )
void Util::ErasePEHeader( HMODULE hModule )
{
	IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER*)hModule;
	IMAGE_NT_HEADERS *pNTHeader = NULL;
	DWORD dwOld;
	if(IsBadReadPtr(hModule,sizeof(IMAGE_DOS_HEADER)))
		return;
	if(pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return;
	pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)(pDosHeader) + (DWORD)(pDosHeader->e_lfanew));
	if(IsBadReadPtr(pNTHeader,sizeof(IMAGE_NT_HEADERS)))
		return;
	if(pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return;
	if(VirtualProtect((LPVOID)pDosHeader,pNTHeader->OptionalHeader.SizeOfHeaders,PAGE_EXECUTE_READWRITE,&dwOld))
	{
		memset((LPVOID)pDosHeader,0,pNTHeader->OptionalHeader.SizeOfHeaders);
		VirtualProtect((LPVOID)pDosHeader,pNTHeader->OptionalHeader.SizeOfHeaders,dwOld,new DWORD);
	}
}



//-------------------------------------------------------------------------------------------------------------------------//
C_BaseCombatWeapon* Util::GetBaseCombatActiveWeapon ( C_BaseEntity* pEntity )
{
	C_BaseCombatWeapon* hResult = NULL;
	__asm
	{
		MOV  EAX, pEntity;
		MOV  EDI, EAX;
		MOV  EAX, DWORD PTR DS :[EDI];
		MOV  ECX, EDI;
		CALL DWORD PTR DS :[EAX+0x2C8]
		mov  hResult, EAX;
	}
	return hResult;
}

//-------------------------------------------------------------------------------------------------------------------------------------//