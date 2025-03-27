#include "gui.h"


void cGui::Border(int x,int y,int w, int h, DWORD dwBorderColor)
{
	base.m_pUtil->FillRGBA( x-1, y-1, w+2, 1 ,dwBorderColor); //top
	base.m_pUtil->FillRGBA( x-1, y, 1, h-1 ,dwBorderColor );	//left
	base.m_pUtil->FillRGBA( x+w, y, 1, h-1 ,dwBorderColor);	//right
    base.m_pUtil->FillRGBA( x-1, y+h-1, w+2, 1 ,dwBorderColor); //bottom
}

void cGui::DrawGrid(int x,int y,int w,int h,int size,int color,int color2)
{
	int s	= size;
	int s1	= s+1;
	int s2	= s-1;
	for(int v=x;v<=x+w-s2;v+=s1)
	{
		base.m_pUtil->FillRGBA(  v, y, s, h,color);
		base.m_pUtil->FillRGBA(v+s, y, s, h,color2);
	}
	for(v=y;v<=y+h-s2;v+=s1)
	{
		base.m_pUtil->FillRGBA(x,  v, w, s,color);
		base.m_pUtil->FillRGBA(x,v+s, w, s,color2);
	}
}