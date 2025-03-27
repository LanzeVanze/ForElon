#include "sdk.h"


//example of use: Color(255,255,255,255);

#define Color(r,g,b,a)((DWORD)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))
#define RED(Color)	((int) ( Color >> 24) )
#define BLUE(Color)	((int) ( Color >> 8 ) & 0xFF )
#define GREEN(Color)	((int) ( Color >> 16 ) & 0xFF )
#define ALPHA(Color)	((int) Color & 0xFF )
#define RGBA(Color) RED( Color ), GREEN( Color ), BLUE( Color ), ALPHA( Color )




//These are just for quick reference.

#define Z_RED Color( 255, 0, 0, 255 )
#define Z_GREEN Color( 0, 255, 0, 255 )
#define Z_BLUE Color( 0, 0, 255, 255 )
#define Z_BLACK Color( 0, 0, 0, 255 )
#define Z_WHITE Color( 255, 255, 255, 255 )