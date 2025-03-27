#include "cAntiLeak.h"
#include "crc32.h"



bool cAL::Verified()
{ 
	//DONT TOUCH HERE -> SEE BELOW TO ADD HWIDS
	//-------------------------------------
	//-------------------------------------
	//-------------------------------------
	DWORD nSize;DWORD nSize2;int nSize3;DWORD lVolSerialNbr=0;
	char cUsername[255] = "";char cComputername[255] = "";char cComputerhost[255] = "";char sHDSerial[255] = "";
	nSize = sizeof( cUsername );nSize2 = sizeof( cComputername );nSize3 = sizeof( cComputerhost );

	GetUserName( cUsername, &nSize );
	GetComputerName( cComputername, &nSize2);

	GetVolumeInformation( "C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0);
    ultoa(lVolSerialNbr, sHDSerial, 10);


	DWORD crcComputerName = gCRC.crc32(cComputername);
	DWORD crcUserName = gCRC.crc32(cUsername);
	DWORD crcHDSer = gCRC.crc32(sHDSerial);
    DWORD HardWareID = crcComputerName+crcUserName+crcHDSer;


#define AddUser( HWID , Name )									\
	if (HardWareID == HWID)										\
	{															\
		return true;											\
	}															

	//-------------------------------------
	//-------------------------------------
	//-------------------------------------


	//Example of how to use the func->
	AddUser(831295588 , Fum1n);
	//AddUser(/*PUT THERE HWID HERE*/, /* put there name so u can remember whos hwid it is*/ );


  return false;
}