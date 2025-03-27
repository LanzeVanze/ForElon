#include "sdk.h"
#include "cMenu.h"

bool bMenu = false;

float menu1,menu2,menu3,menu4,menu5,menu6,menu7,menu11,menu12,menu13,menu15,menu1337,rofls;
struct a_menu{char title[1000];float* value;float min;float max;float step;};
int menuIndex = 0;int menuItems = 0;a_menu amenu[150];

int cMenu::AddMenuEntry(int n, char title[1000], float* value, float min, float max, float step)
{
	strcpy( amenu[n].title,title);
	amenu[n].value = value;
	amenu[n].min = min;
	amenu[n].max = max;
	amenu[n].step = step;
	return (n+1);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void cMenu::InitializeMenu()
{
	//LOG("cMenu::InitializeMenu()");
	int i = 0;

	if(!menu1)
		i = AddMenuEntry(i, "[+] Aimbot", &menu1, 0, 1, 1);

	if(menu1){
	i = AddMenuEntry(i, "[-] Aimbot", &menu1, 0, 1, 1);
	i = AddMenuEntry(i, "    Aim Allways", &base.m_psCvar->aim_allways, 0, 1, 1);
	i = AddMenuEntry(i, "    Aim Key", &base.m_psCvar->aim_key, 0, 1, 1);
	i = AddMenuEntry(i, "    Auto Shoot", &base.m_psCvar->aim_shoot, 0, 1, 1);
	i = AddMenuEntry(i, "    Aim Thru", &base.m_psCvar->aim_thru, 0, 2, 1);
	i = AddMenuEntry(i, "    Aim Spot", &base.m_psCvar->aim_hitbox, 0, 16, 1);

	if(!menu11)  
		i = AddMenuEntry(i, "    [+] Tweaking", &menu11, 0, 1, 1);

	if(menu11){
		i = AddMenuEntry(i, "    [-] Tweaking", &menu11, 0, 1, 1);
		i = AddMenuEntry(i, "		 Aim Method", &base.m_psCvar->aim_method, 1, 2, 1);
		i = AddMenuEntry(i, "        Target Method", &base.m_psCvar->aim_by_distance, 0, 1, 1);

		if(base.m_psCvar->aim_by_distance == 0)
		i = AddMenuEntry(i, "        Fov", &base.m_psCvar->aim_fov, 0, 360, 1);

		i = AddMenuEntry(i, "        h_adjust", &base.m_psCvar->aim_hdj, 0, 10, 0.1f);
		i = AddMenuEntry(i, "        Aim Smooth", &base.m_psCvar->aim_smooth, 0, 10, 0.1f);

	}

	}

	if(!menu2)
		i = AddMenuEntry(i, "[+] Global ESP", &menu2, 0, 1, 1);

	if(menu2){
	i = AddMenuEntry(i, "[-] Global ESP", &menu2, 0, 1, 1);


	i = AddMenuEntry(i, "    NameTags", &base.m_psCvar->esp_name, 0, 1, 1);
	i = AddMenuEntry(i, "    WeaponTags", &base.m_psCvar->esp_weapon, 0, 2, 1);
	i = AddMenuEntry(i, "    HealthTags", &base.m_psCvar->esp_health, 0, 2, 1);
	i = AddMenuEntry(i, "    ArmorTags", &base.m_psCvar->esp_armor, 0, 2, 1);
	i = AddMenuEntry(i, "    BarrelHack", &base.m_psCvar->esp_barrel, 0, 1, 1);
	i = AddMenuEntry(i, "    BoundingBoxes", &base.m_psCvar->esp_box, 0, 1, 1);
	i = AddMenuEntry(i, "    SoundESP", &base.m_psCvar->esp_sound, 0, 1, 1);
	i = AddMenuEntry(i, "    -*Show Enemys Only*-", &base.m_psCvar->esp_show_enemys_only, 0, 1, 1);
	}

	if(!menu3)
		i = AddMenuEntry(i, "[+] No Spread", &menu3, 0, 1, 1);

	if(menu3){
	i = AddMenuEntry(i, "[-] No Spread", &menu3, 0, 1, 1);
	i = AddMenuEntry(i, "    No Recoil", &base.m_psCvar->aim_norecoil, 0, 3, 0.1f);
	i = AddMenuEntry(i, "    No Spread", &base.m_psCvar->aim_nospread, 0, 2, 1);
	i = AddMenuEntry(i, "    No Visual Recoil", &base.m_psCvar->vis_recoil, 0, 1, 1);
	}

	if(!menu7)
		i = AddMenuEntry(i, "[+] Radar", &menu7, 0, 1, 1);

	if(menu7){
	i = AddMenuEntry(i, "[-] Radar", &menu7, 0, 1, 1);
	i = AddMenuEntry(i, "    Radar", &base.m_psCvar->radar, 0, 1, 1);
	i = AddMenuEntry(i, "    Radar X", &base.m_psCvar->radar_x, 0, 1000, 1);
	i = AddMenuEntry(i, "    Radar Y", &base.m_psCvar->radar_y, 0, 1000, 1);
	i = AddMenuEntry(i, "    Radar Size", &base.m_psCvar->radar_size, 30, 300, 1);
	i = AddMenuEntry(i, "    Radar Range", &base.m_psCvar->radar_range, 0, 50, 1);
	}

	if(!menu4)
		i = AddMenuEntry(i, "[+] Removals", &menu4, 0, 1, 1);

	if(menu4){
		i = AddMenuEntry(i, "[-] Removals", &menu4, 0, 1, 1);

		i = AddMenuEntry(i, "    NoFlash/Smoke", &base.m_psCvar->vis_noflash, 0, 1, 1);
		i = AddMenuEntry(i, "    NoHands", &base.m_psCvar->vis_nohands, 0, 2, 1);
		i = AddMenuEntry(i, "    NoSky", &base.m_psCvar->vis_nosky, 0, 1, 1);
		i = AddMenuEntry(i, "    NoSc(+)pe", &base.m_psCvar->vis_noscope, 0, 1, 1);

	}

	if(!menu5)
		i = AddMenuEntry(i, "[+] Visual", &menu5, 0, 1, 1);


	if(menu5){
		i = AddMenuEntry(i, "[-] Visual", &menu5, 0, 1, 1);
		i = AddMenuEntry(i, "    Chams", &base.m_psCvar->vis_chams, 0, 1, 1);
		i = AddMenuEntry(i, "    CrossHair", &base.m_psCvar->vis_crosshair, 0, 1, 1);
		i = AddMenuEntry(i, "    XQZ WallHack", &base.m_psCvar->vis_xqzmodels, 0, 1, 1);
	}

	if(!menu6)
		i = AddMenuEntry(i, "[+] Other", &menu6, 0, 1, 1);

	if(menu6){
	i = AddMenuEntry(i, "[-] Other", &menu6, 0, 1, 1);
	i = AddMenuEntry(i, "    Winamp", &base.m_psCvar->misc_winamp, 0, 2, 1);
	i = AddMenuEntry(i, "    Auto Pistol", &base.m_psCvar->misc_autopistol, 0, 1, 1);
	i = AddMenuEntry(i, "    Bunny Hop", &base.m_psCvar->misc_bunnyhop, 0, 1, 1);
	i = AddMenuEntry(i, "    Spin Hack", &base.m_psCvar->misc_spinbot, 0, 1, 1);
	i = AddMenuEntry(i, "    Anti-Aim", &base.m_psCvar->misc_anti_aim, 0, 2, 1);

	}

	menuItems = i;
}
//******************************
//Graphical
//******************************

void cMenu::MenuDrawing()
{

	if (GetAsyncKeyState(VK_INSERT) & 1) bMenu = !bMenu;

	if (!bMenu) 
		return;

	float menu_x = 100;
	float menu_y = 300;
	float menu_w = 210;

	KeyMenuEvent();
    int i = menuItems;

	base.m_pGuiWindow->DrawWindow(menu_x-10,menu_y-8,menu_w,12 + (14*i) ,"                       DZ HooK v0.5");

	for(int i=0;i<menuItems;i++)
	if( i!=menuIndex)//unselected menu item.
	{
		base.m_pUtil->PrintText( menu_x,menu_y+2 + (14*i)+2,Color(255,255,255,255),amenu[i].title);
		base.m_pUtil->PrintText( menu_x+50,menu_y+2 + (14*i)+2, Color(255,255,255,255),"                                       %2.2f", amenu[i].value[0] );
	}
	else//selected menu item.
	{
		base.m_pUtil->PrintText( menu_x,menu_y+2 + (14*i)+2,Color(169,221,61,255),amenu[i].title);
		base.m_pUtil->PrintText( menu_x+50,menu_y+2 + (14*i)+2,Color(169,221,61,255),"                                       %2.2f", amenu[i].value[0] );
	}
}
void cMenu::KeyMenuEvent()
{
	if( GetAsyncKeyState(VK_HOME) & 1)
	{
		if( menuIndex>0 ) menuIndex--;
		else menuIndex = menuItems - 1;
	}
	else if( GetAsyncKeyState(VK_END) & 1)
	{
		if( menuIndex<menuItems-1 ) menuIndex++;
		else menuIndex = 0;
	}
	else if( GetAsyncKeyState(VK_DELETE) & 1)
	{
		if( amenu[menuIndex].value )
		{
			amenu[menuIndex].value[0] -= amenu[menuIndex].step;
			if( amenu[menuIndex].value[0] < amenu[menuIndex].min )
				amenu[menuIndex].value[0] = amenu[menuIndex].max;
		}
	}
	else if( GetAsyncKeyState(VK_NEXT) & 1)
	{
		if( amenu[menuIndex].value )
		{
			amenu[menuIndex].value[0] += amenu[menuIndex].step;
			if( amenu[menuIndex].value[0] > amenu[menuIndex].max )
				amenu[menuIndex].value[0] = amenu[menuIndex].min;
		}
	}
}