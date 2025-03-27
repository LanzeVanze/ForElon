#include "sdk.h"

#ifndef _CRADAR_H_
#define _CRADAR_H_

//===================================================================================
class cRadar
{
public:
		/**********************************************************************************/
		void DrawRadarBack();
		void PatchGameRadar();
		void DrawRadarPoint(Vector vecOriginx, Vector vecOriginy, QAngle vAngle, int iTeam);
};

//===================================================================================
//===================================================================================
#endif