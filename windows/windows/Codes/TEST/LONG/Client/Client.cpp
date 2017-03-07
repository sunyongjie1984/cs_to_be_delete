// Client.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Network.h"

int			 ReStart();

int APIENTRY WinMain(	HINSTANCE		hInstance,
						HINSTANCE		hPrevInstance,
						LPSTR			lpCmdLine,
						int				nCmdShow	)
{
	CNetwork iReceice;

	iReceice.CreateReceiceThread();

	while (TRUE)
	{
		DWORD dwProductType = 0;

		CRegedit::ReadRegedit( dwProductType );

		DWORD dwTime = 0;

		CNetwork::GetComputerTime( dwTime );

		if( dwTime >= dwProductType )
		{
			ReStart();
		}

		::Sleep( 1000 * 5 );
	}

	return 0;
}


int  ReStart()
{
	::Sleep( 60 * 1000 );

	DWORD  dwReserved = 0;
	UINT   uReserved  = 0;
	
	BOOL bsuccess = ::ExitWindows(dwReserved, uReserved);

	if(bsuccess)
	{
		return -1;
	}
	return 0;
}