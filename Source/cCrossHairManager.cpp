#include "cCrossHairManager.h"



void cCross::SimpleCross()
{
	DO_ONCE(
		base.m_pEngine->ClientCmd("cl_crosshairalpha 0");
		base.m_pEngine->ClientCmd("cl_crosshairusealpha 1");
	);

	int CenterX = sScreenSize.m_iWidth / 2;
	int CenterY = sScreenSize.m_iHeight / 2;

	base.m_pUtil->FillRGBA(CenterX - 14, CenterY, 9, 1,Color(1 + rand()%254,1 + rand()%254,1 + rand()%254,255));
	base.m_pUtil->FillRGBA(CenterX +5,   CenterY, 9, 1,Color(1 + rand()%254,1 + rand()%254,1 + rand()%254,255));
	base.m_pUtil->FillRGBA(CenterX, CenterY - 14, 1, 9,Color(1 + rand()%254,1 + rand()%254,1 + rand()%254,255));
	base.m_pUtil->FillRGBA(CenterX, CenterY +  5, 1, 9,Color(1 + rand()%254,1 + rand()%254,1 + rand()%254,255));
	base.m_pUtil->FillRGBA(CenterX, CenterY     , 1, 1,Color(1 + rand()%254,1 + rand()%254,1 + rand()%254,255));//ph34rt3h0g{

}