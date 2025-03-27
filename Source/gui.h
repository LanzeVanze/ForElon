#ifndef _GUI_H_
#define _GUI_H_
#include "sdk.h"
//===================================================================================
class cGui
{
public:
		void Border(int x,int y,int w, int h, DWORD dwBorderColor);
		void DrawGrid(int x,int y,int w,int h,int size,int color,int color2);
};

//===================================================================================
//===================================================================================
#endif