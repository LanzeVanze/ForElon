#include "cWinamp.h"

HWND hwndWinamp = FindWindow("Winamp v1.x",NULL); //find the winamp window

char title[3024],*rTitle;  
char winamp[3024];

void cWinamp::Title()
{ 
    GetWindowText(hwndWinamp, title, 3024);
    rTitle = title+strlen(title)-8;
    while (rTitle >= title)
    {
        
        if (!strnicmp(rTitle,"- Winamp",8)) break;
        rTitle--;
    }
    if (rTitle >= title) rTitle--;
    while (rTitle >= title && *rTitle == ' ') rTitle--;
    *++rTitle=0;
}  

void cWinamp::drawAmp()
{

    Title();
	if(base.m_psCvar->misc_winamp)
	{
		if(hwndWinamp)
		{
			base.m_pGuiWindow->DrawWindow(500,150,250,31,"       -DZ Winamp-");
			base.m_pUtil->PrintText(500+10+(strlen(title)), 150+3, Color(255,255,255,255),"    <- Now Playing -> ");
			base.m_pUtil->PrintText(500+10, 150+8, Color(255,255,255,255), title);
		}
	}
	if(base.m_psCvar->misc_spam == 2)
	{
		if(hwndWinamp)
		{
			sprintf(winamp, "Say -::%s::-",title);
			base.m_pEngine->ClientCmd(winamp);
		}
	}
}