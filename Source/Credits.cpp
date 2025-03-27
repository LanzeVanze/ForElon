#include "Credits.h"


void Credits::ConsoleCredits()
{
	base.m_pHl2GameConsole->Init();

	if( !base.m_pHl2GameConsole->IsVisible() )
		base.m_pHl2GameConsole->Activiate();

	base.m_pHl2GameConsole->RandomColorPrint("/////////////////////////////////\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//[ D E T E C T I O N Z E R 0 ]//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("/////////////////////////////////\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//|v3n0m4 - P47R!CK - Tetsuo  |//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//|H1web - Holz - Siodine     |//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//|Anubis82 - Boecke - Wav    |//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//|aVitamin - TURiOL - JaVeX  |//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("//|s0beit - Takedown - Mattdog|//\n" );
	base.m_pHl2GameConsole->RandomColorPrint("/////////////////////////////////\n" );
}

