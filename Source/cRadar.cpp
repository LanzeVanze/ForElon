#include "cRadar.h"

void cRadar::PatchGameRadar()
{
///todo?
}
void cRadar::DrawRadarBack()
{
	int centerx = base.m_psCvar->radar_x;
	int centery = base.m_psCvar->radar_y;
	int size    = base.m_psCvar->radar_size;
	size -= 10; 
	base.m_pGuiWindow->DrawWindow( centerx-size, centery-size, 2*size,2*size,/*                    - Dz Radar -*/XorStr<0x73,33,0xA5EF870E>("\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xAA\xA8\xCD\xF0\xAB\xDE\xEC\xEA\xEE\xE2\xB1\xBF"+0xA5EF870E).s);
	base.m_pUtil->FillRGBA( centerx, centery - size ,1,2*size,Color(30,30,30,70));
	base.m_pUtil->FillRGBA( centerx - size, centery ,2*size,1,Color(30,30,30,70));
}

void  cRadar::DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, QAngle vAngle, int iTeam)
{
	float dx  = vecOriginx.x - vecOriginy.x;
	float dy  = vecOriginx.y - vecOriginy.y;
	float flAngle = vAngle.y;
	float yaw = (flAngle) * (M_PI/180.0);
	float mainViewAngles_CosYaw = cos(yaw);
	float mainViewAngles_SinYaw = sin(yaw);
	float x =  dy*(-mainViewAngles_CosYaw)  + dx*mainViewAngles_SinYaw;
	float y =  dx*(-mainViewAngles_CosYaw)  - dy*mainViewAngles_SinYaw;
	float range = base.m_psCvar->radar_size * base.m_psCvar->radar_range;
	if(fabs(x)>range || fabs(y)>range)
	{ 
		if(y>x)
		{
			if(y>-x) {
				x = range*x/y;
				y = range;
			}  else  {
				y = -range*y/x; 
				x = -range; 
			}
		} else {
			if(y>-x) {
				y = range*y/x; 
				x = range; 
			}  else  {
				x = -range*x/y;
				y = -range;
			}
		}
	}
	int ScreenX = base.m_psCvar->radar_x + int( x/range*float(base.m_psCvar->radar_size));
	int ScreenY = base.m_psCvar->radar_y + int( y/range*float(base.m_psCvar->radar_size));
	base.m_pUtil->FillRGBA( ScreenX-1, ScreenY-1,4,4, iTeam);
}