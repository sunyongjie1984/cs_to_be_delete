#include "windows.h"
#include <Winnetwk.h>



#pragma comment(lib, "Mpr.lib")



int main(void)
{
	return 0;
}


void test(void)
{
	DWORD dwResult; 
	NETRESOURCE nr; 
	//
	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	//
	dwResult = WNetAddConnection2(&nr, // NETRESOURCE from enumeration 
		(LPSTR) NULL,                  // no password 
		(LPSTR) NULL,                  // logged-in user 
		CONNECT_UPDATE_PROFILE);       // update profile with connect information 
	
	// Process errors.
	//  The local device is already connected to a network resource.
	//
	if (dwResult == ERROR_ALREADY_ASSIGNED) 
	{ 
		return; 
	}
	
	//  An entry for the local device already exists in the user profile.
	//
	else if (dwResult == ERROR_DEVICE_ALREADY_REMEMBERED) 
	{ 
		return; 
	} 
	else if(dwResult != NO_ERROR) 
	{ 
		//
		// Call an application-defined error handler.
		//
		return; 
	}
}