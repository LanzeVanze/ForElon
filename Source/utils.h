#ifndef __Utils_H__
#define __Utils_H__

#include "sdk.h"

class Util
{
public:
	void FontInit( void );
	bool ScreenTransform( const Vector &point, Vector &screen );
	bool WorldToScreen( const Vector &vOrigin, Vector &vScreen );
	void FillRGBA( int x, int y, int w, int h, DWORD dwColor );
	void PrintText( int x, int y, DWORD dwColor, const char *pszText, ... );
	void DrawSprite( int x, int y, DWORD dwColor, const char *pszText, ... );
	void Normalize(Vector &vIn, Vector &vOut);
	void GetWorldSpaceCenter( CBaseEntity* pBaseEnt, Vector& vWorldSpaceCenter );
	void ErasePEHeader( HMODULE hModule );
	void HideModule(HINSTANCE hModule);
	C_BaseCombatWeapon* Util::GetBaseCombatActiveWeapon ( C_BaseEntity* pEntity );
public:
	vgui::HFont m_ESPFont;
	vgui::HFont m_pSpriteFont;
};

#endif
