#include "cWindow.h"


void GuiWindow::RoundedWindow(int x,int y, int w, int h, int r, int g, int b, int a)
{

    base.m_pMatSurface->DrawColoredCircle( x + 5, y + 5, 5.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + 5, 4.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + 5, 3.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + 5, 2.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + 5, 1.0f, r,g,b,a);

    base.m_pMatSurface->DrawColoredCircle( x + w - 10, y + 10, 5.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 10, y + 10, 4.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 10, y + 10, 3.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 10, y + 10, 2.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 10, y + 10, 1.0f, r,g,b,a);

    base.m_pMatSurface->DrawColoredCircle( x + 5, y + h -5, 5.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + h -5, 4.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + h -5, 3.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + h -5, 2.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + 5, y + h -5, 1.0f, r,g,b,a);

    base.m_pMatSurface->DrawColoredCircle( x + w - 5, y + h -5, 5.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 5, y + h -5, 4.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 5, y + h -5, 3.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 5, y + h -5, 2.0f, r,g,b,a);
    base.m_pMatSurface->DrawColoredCircle( x + w - 5, y + h -5, 1.0f, r,g,b,a);

    base.m_pMatSurface->DrawSetColor( r,g,b,a );
    base.m_pMatSurface->DrawFilledRect( x, y + 5, x + w, y + h - 5 );
    base.m_pMatSurface->DrawFilledRect( x + 5, y, x + w - 5, y + 5 );
    base.m_pMatSurface->DrawFilledRect( x + 5, y + h - 5, x + w - 5, y + h );
}
void GuiWindow::DrawWindow(int x,int y,int w,int h,char* title)
{
	
	//// Title Box
	//base.m_pGuiWindow->RoundedWindow(x,y-20,w,20,1,1,1,255);
	base.m_pUtil->FillRGBA( x, y-20, w, 20,Color( 1,1,1, 255 ));

	//Grid
	base.m_pGui->DrawGrid(x,y-20,w-2,18,1,Color(1,1,1,255),Color(169,221,61,15));

	//Gradient
	base.m_pUtil->FillRGBA( x, y-20, w, 1,	Color( 76,76,78, 200 ));
	base.m_pUtil->FillRGBA( x, y-19, w, 1,Color( 100,100,100, 190 ));
	base.m_pUtil->FillRGBA( x, y-18, w, 1,Color( 100,100,100, 180 ));
	base.m_pUtil->FillRGBA( x, y-17, w, 1,Color( 100,100,100, 170 ));
	base.m_pUtil->FillRGBA( x, y-16, w, 1,Color( 100,100,100, 160 ));
	base.m_pUtil->FillRGBA( x, y-15, w, 1,Color( 100,100,100, 150 ));
	base.m_pUtil->FillRGBA( x, y-14, w, 1,Color( 100,100,100, 140 ));
	base.m_pUtil->FillRGBA( x, y-13, w, 1,Color( 100,100,100, 130 ));
	base.m_pUtil->FillRGBA( x, y-12, w, 1,Color( 100,100,100, 120 ));
	base.m_pUtil->FillRGBA( x, y-11, w, 1,Color( 100,100,100, 110 ));




	//Main body
	//base.m_pGuiWindow->RoundedWindow(x,y+5,w,h,1,1,1,255);
	base.m_pUtil->FillRGBA( x, y+5, w, h,Color(1,1,1, 255 ));

	//Grid
	base.m_pGui->DrawGrid(x,y+5,w-2,h-2,1,Color(1,1,1,255),Color(169,221,61,15));

	float CenterX = x + w - 6;
	float CenterY = y - 14;

	base.m_pUtil->FillRGBA(CenterX, CenterY, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX - 1, CenterY + 1, 1, 1,Color(30,1,1,255));
    base.m_pUtil->FillRGBA(CenterX - 2, CenterY + 2, 1, 1,Color(30,1,1,255));
    base.m_pUtil->FillRGBA(CenterX - 3, CenterY + 3, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX - 1, CenterY - 1, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX - 2, CenterY - 2, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX - 3, CenterY - 3, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 1, CenterY + 1, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 2, CenterY + 2, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 3, CenterY + 3, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 1, CenterY - 1, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 2, CenterY - 2, 1, 1,Color(30,1,1,255));
	base.m_pUtil->FillRGBA(CenterX + 3, CenterY - 3, 1, 1,Color(30,1,1,255));

	//Top down gradient
	base.m_pUtil->FillRGBA( x, y+6, w, 1,Color( 100,100,100, 95 ));
	base.m_pUtil->FillRGBA( x, y+7, w, 1,Color( 100,100,100, 90 ));
	base.m_pUtil->FillRGBA( x, y+8, w, 1,Color( 100,100,100, 85 ));
	base.m_pUtil->FillRGBA( x, y+9, w, 1,Color( 100,100,100, 80 ));
	base.m_pUtil->FillRGBA( x, y+10, w, 1,Color( 100,100,100, 75 ));
	base.m_pUtil->FillRGBA( x, y+11, w, 1,Color( 100,100,100, 70 ));
	base.m_pUtil->FillRGBA( x, y+12, w, 1,Color( 100,100,100, 65 ));
	base.m_pUtil->FillRGBA( x, y+13, w, 1,Color( 100,100,100, 60 ));
	base.m_pUtil->FillRGBA( x, y+14, w, 1,Color( 100,100,100, 55 ));
	base.m_pUtil->FillRGBA( x, y+15, w, 1,Color( 100,100,100, 50 ));
	base.m_pUtil->FillRGBA( x, y+16, w, 1,Color( 100,100,100, 45 ));
	base.m_pUtil->FillRGBA( x, y+17, w, 1,Color( 100,100,100, 40 ));
	base.m_pUtil->FillRGBA( x, y+18, w, 1,Color( 100,100,100, 35 ));
	base.m_pUtil->FillRGBA( x, y+19, w, 1,Color( 100,100,100, 30 ));
	base.m_pUtil->FillRGBA( x, y+20, w, 1,Color( 100,100,100, 25 ));
	base.m_pUtil->FillRGBA( x, y+21, w, 1,Color( 100,100,100, 20 ));
	base.m_pUtil->FillRGBA( x, y+22, w, 1,Color( 100,100,100, 15 ));
	base.m_pUtil->FillRGBA( x, y+23, w, 1,Color( 100,100,100, 10 ));
	base.m_pUtil->FillRGBA( x, y+24, w, 1,Color( 100,100,100, 5 ));
	base.m_pUtil->FillRGBA( x, y+25, w, 1,Color( 100,100,100, 1 ));

	


	//Bottom up gradient
	base.m_pUtil->FillRGBA( x, y+5+h-1, w, 1,Color( 100,100,100, 95 ));
	base.m_pUtil->FillRGBA( x, y+5+h-2, w, 1,Color( 100,100,100, 90 ));
	base.m_pUtil->FillRGBA( x, y+5+h-3, w, 1,Color( 100,100,100, 85 ));
	base.m_pUtil->FillRGBA( x, y+5+h-4, w, 1,Color( 100,100,100, 80 ));
	base.m_pUtil->FillRGBA( x, y+5+h-5, w, 1,Color( 100,100,100, 75 ));
	base.m_pUtil->FillRGBA( x, y+5+h-6, w, 1,Color( 100,100,100, 70 ));
	base.m_pUtil->FillRGBA( x, y+5+h-7, w, 1,Color( 100,100,100, 65));
	base.m_pUtil->FillRGBA( x, y+5+h-8, w, 1,Color( 100,100,100, 60 ));
	base.m_pUtil->FillRGBA( x, y+5+h-9, w, 1,Color( 100,100,100, 55 ));
	base.m_pUtil->FillRGBA( x, y+5+h-10, w, 1,Color( 100,100,100, 50 ));
	base.m_pUtil->FillRGBA( x, y+5+h-11, w, 1,Color( 100,100,100, 45 ));
	base.m_pUtil->FillRGBA( x, y+5+h-12, w, 1,Color( 100,100,100, 40 ));
	base.m_pUtil->FillRGBA( x, y+5+h-13, w, 1,Color( 100,100,100, 35));
	base.m_pUtil->FillRGBA( x, y+5+h-14, w, 1,Color( 100,100,100, 30 ));
	base.m_pUtil->FillRGBA( x, y+5+h-15, w, 1,Color( 100,100,100, 25 ));
	base.m_pUtil->FillRGBA( x, y+5+h-16, w, 1,Color( 100,100,100, 20 ));
	base.m_pUtil->FillRGBA( x, y+5+h-17, w, 1,Color( 100,100,100, 15 ));
	base.m_pUtil->FillRGBA( x, y+5+h-18, w, 1,Color( 100,100,100, 10 ));
	base.m_pUtil->FillRGBA( x, y+5+h-19, w, 1,Color( 100,100,100, 5 ));
	base.m_pUtil->FillRGBA( x, y+5+h-20, w, 1,Color( 100,100,100, 1 ));


	//Borders
	base.m_pGui->Border( x, y+5, w, h,Color(169,221,61,110));
	base.m_pGui->Border( x, y-20, w, 20,Color(169,221,61,110));

	//Title
	base.m_pUtil->PrintText(x,y-17,Color(169,221,61,255),title);

//	base.m_pGui->Border( x, y+3, w+1, h+1,Color(255,255,255,60));
	//base.m_pGui->Border( x, y-21, w, 21,Color(255,255,255,60));
}
