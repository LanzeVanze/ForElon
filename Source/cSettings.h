#include "sdk.h"

#ifndef CSETTINGS_H
#define CSETTINGS_H

class cSettings
{
public:
		void SaveConfigs();
		void LoadConfigs();
		void GetIniFile( HMODULE hModule );
		void LogFile( HMODULE hModule );
		void GetFont( HMODULE hModule );
};

extern char szLogFile[256];
extern char szIniFile[256];
extern char szFont[256];
#endif
