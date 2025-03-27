#ifndef __PANELS_H__
#define __PANELS_H__

#include "sdk.h"

typedef struct 
{
	int m_iWidth;
	int m_iHeight;
} ScreenSize_t;		// used to store the screen resolution

class CDrawPanel : public vgui::Panel
{
	typedef vgui::Panel BaseClass;

	public:
	CDrawPanel( vgui::VPANEL parent );
	virtual void Paint();
};

class CDrawLayer
{
	private:
		CDrawPanel*  pDrawPanel;

	public:
		CDrawLayer ( void );
		~CDrawLayer ( void );

		void Create ( vgui::VPANEL parent );
		void Destroy( void );
};

extern ScreenSize_t sScreenSize;// struct to store the screen-size

#endif
