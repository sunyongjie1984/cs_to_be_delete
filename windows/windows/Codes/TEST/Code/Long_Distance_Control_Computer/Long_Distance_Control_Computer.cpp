// Long_Distance_Control_Computer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CommunicationTask.h"

int APIENTRY WinMain(	HINSTANCE		hInstance,
						HINSTANCE		hPrevInstance,
						LPSTR			lpCmdLine,
						int				nCmdShow	)

{
	CCommunicationTask iCommunication;

	iCommunication.StartNetWorkListenTask();

	MSG iMsg;

	while ( TRUE )
	{
		if(PeekMessage(&iMsg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&iMsg,NULL,0,0))
			{
				return iMsg.wParam;
			}

			TranslateMessage(&iMsg);
			DispatchMessage(&iMsg);
        }
		else
		{
			WaitMessage();
		}
	}
	return 0;
}


