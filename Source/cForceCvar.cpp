#include "cForceCvar.h"


void CvarForce::Unlock()
{
	ConVar *consistency = base.m_pCvar->FindVar( "sv_consistency" );
    ConVar *cheets = base.m_pCvar->FindVar( "sv_cheats" );
    if(consistency || cheets){

        if(consistency->IsBitSet(FCVAR_CHEAT))consistency->m_nFlags &= ~FCVAR_CHEAT;
        if(consistency->IsBitSet(FCVAR_REPLICATED))consistency->m_nFlags &= ~FCVAR_REPLICATED;
        if(consistency->IsBitSet(FCVAR_PROTECTED))consistency->m_nFlags &= ~FCVAR_PROTECTED;
        if(consistency->IsBitSet(FCVAR_SPONLY))consistency->m_nFlags &= ~FCVAR_SPONLY;
		if(cheets->IsBitSet(FCVAR_CHEAT))cheets->m_nFlags &= ~FCVAR_CHEAT;
        if(cheets->IsBitSet(FCVAR_REPLICATED))cheets->m_nFlags &= ~FCVAR_REPLICATED;
        if(cheets->IsBitSet(FCVAR_PROTECTED))cheets->m_nFlags &= ~FCVAR_PROTECTED;
        if(cheets->IsBitSet(FCVAR_SPONLY))cheets->m_nFlags &= ~FCVAR_SPONLY;
		consistency->SetValue(0);
		cheets->SetValue(1);
    }
	else{
		add_log("Cvar Bypass FAILED");
	}



}