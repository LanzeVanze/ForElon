#include "VisualRecoil.h"

BYTE PunchAnglex[6] = { 0xD9, 0x86, 0xB0, 0x0B, 0x00, 0x00 };//punch x
BYTE PunchAngley[6] = { 0xD9, 0x86, 0xB4, 0x0B, 0x00, 0x00 };//punch y
BYTE PunchAnglez[6] = { 0xD9, 0x86, 0xB8, 0x0B, 0x00, 0x00 };//punch z
BYTE PunchAngleFixed[6]  = { 0xD9, 0x86, 0x48, 0x0B, 0x00, 0x00 };//punch fixed :D
DWORD Hack;

//avitamins
void VisualPunchangleRemoval::RemovePunchAngle()
{
	if(base.m_psCvar->vis_recoil)
    {
		DO_ONCE(
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192B2),&PunchAngleFixed,6,&Hack);//set new 0x48
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192BC),&PunchAngleFixed,6,&Hack);
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192C8),&PunchAngleFixed,6,&Hack);
			add_log("Visual Recoil Patched");
		)
	}
	if(!base.m_psCvar->vis_recoil)
    {
		DO_ONCE(
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192B2),&PunchAnglex,6,&Hack);//turning off and restoring old (B0, B4, B8, (XYZ) )
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192BC),&PunchAngley,6,&Hack);
			WriteProcessMemory(GetCurrentProcess(),(void*)(0x24000000 + 0x192C8),&PunchAnglez,6,&Hack);
			add_log("Visual Recoil UnPatched");
		)
	}
}


/*
//v3n0m4z
if( hSnapShot != INVALID_HANDLE_VALUE )
{
if(  Module32First( hSnapShot, &module32 ) )
{
while( Module32Next(  hSnapShot, &module32 ) )
{
if( !strcmp( module32.szModule,  "client.dll" ) )
{
if ( Main.GetTheGameMod() == GAME_COUNTER_STRIKE_SOURCE  )
{
//////////////////////////////////////////////////////////////////////////
//Visual  Recoil
recoilPatch[0] = PVOID(module32.modBaseAddr +  0x192B2);//X
recoilPatch[1] = PVOID(module32.modBaseAddr +  0x192BC);//Y
recoilPatch[2] = PVOID(module32.modBaseAddr + 0x192C8);//Z  
//////////////////////////////////////////////////////////////////////////   
void VisualPunchangleRemoval::Norecoil_6ByTePatch( PVOID Destination,PBYTE patch  )
{
DWORD dwOld =  0x0;
VirtualProtect(Destination,6,PAGE_EXECUTE_READWRITE,&dwOld);
MemCpy(Destination,patch,6);
VirtualProtect(Destination,6,dwOld,&dwOld);
}  

void VisualPunchangleRemoval::func_patch_visual_recoil()
{
if ( Main.GetTheGameMod() ==  GAME_COUNTER_STRIKE_SOURCE )
{
BYTE Patch[6] = { 0xD9, 0x86, 0x48, 0x0B,  0x00, 0x00 };
if( Main.m_pMain_Hook->recoilPatch[0] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[0],Patch);  
if( Main.m_pMain_Hook->recoilPatch[1] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[1],Patch);
if(  Main.m_pMain_Hook->recoilPatch[2] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[2],Patch);
Main.m_pCheatConsole->Printf(  "Visual Recoil Successfully Removed.");
} 

void VisualPunchangleRemoval::func_unpatch_visual_recoil()
{
if ( Main.GetTheGameMod() ==  GAME_COUNTER_STRIKE_SOURCE )
{
BYTE x[6] = { 0xD9, 0x86, 0xB0, 0x0B, 0x00,  0x00 };
BYTE y[6] = { 0xD9, 0x86, 0xB4, 0x0B, 0x00, 0x00 };
BYTE z[6] = {  0xD9, 0x86, 0xB8, 0x0B, 0x00, 0x00 };
if(  Main.m_pMain_Hook->recoilPatch[0] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[0],x);
if(  Main.m_pMain_Hook->recoilPatch[1] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[1],y);
if(  Main.m_pMain_Hook->recoilPatch[2] != 0  )Main.m_pMain_Hook->Norecoil_6ByTePatch(Main.m_pMain_Hook->recoilPatch[2],z);
Main.m_pCheatConsole->Printf(  "Visual Recoil Successfully Restored.");
}
}*/ 
