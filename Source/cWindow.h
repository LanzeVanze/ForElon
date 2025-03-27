#include "sdk.h"

#ifndef _CWINDOW_H_
#define _CWINDOW_H_

class GuiWindow
{
public:
		void DrawWindow(int x,int y,int w,int h,char* title);
		void RoundedWindow(int x,int y, int w, int h, int r, int g, int b, int a);
};
#endif