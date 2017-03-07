#include "mySocket.h"
#include "..\myLog\myLog.h"
#include "..\myException\myException.h"
#include "..\myHostInfo\myHostInfo.h"

myLog winLog;
int main()
{

#ifdef WINDOWS_XP

	// Initialize the winsock library
	WSADATA wsaData;
    winLog << "system started ..." << endl;
	winLog << endl << "initialize the winsock library ... ";

	try 
	{
		if (WSAStartup(0x101, &wsaData))
		{
			myException* initializationException = new myException(0,"Error: calling WSAStartup()");
			throw initializationException;
        }
	}
	catch(myException* excp)
	{
		excp->response();
		delete excp;
		exit(1);
	}
	winLog << "successful" << endl;

#endif
        
	// get local information if neither the name or the address is given

	winLog << endl;
	winLog << "Retrieve the local host name and address with no information:" << endl;
	
    myHostInfo uHostAddress;
	string localHostName = uHostAddress.getHostName();
    string localHostAddr = uHostAddress.getHostIPAddress();
    cout << "Name: " << localHostName << endl;
    cout << "Address: " << localHostAddr << endl;
	winLog << "		==> Name: " << localHostName << endl;
	winLog << "		==> Address: " << localHostAddr << endl;

	// open socket on the local host
	mySocket localSocket(1000);
	cout << localSocket;
	winLog << localSocket;

	// set linger on
	localSocket.setLingerOnOff(true);
	localSocket.setLingerSeconds(10);

	// show it again
	cout << endl << "After changing the socket settings ... " << endl;
	cout << localSocket;
	winLog << localSocket;
	
#ifdef UNIX

    // Retrieve all entries from the host name database
    myHostInfo AllHosts;
    while(AllHosts.cGetNextHost())
    {
        cout << "Name: " << AllHosts.sGetHostName() << endl;
        cout << "Address: " << AllHosts.sGetHostAddress() << endl;
    }

#endif

#ifdef WINDOWS_XP

    // Close the winsock library
	winLog << endl << "system shut down ...";		
	
	try 
	{
		if (WSACleanup())
		{
			myException* cleanupException = new myException(0,"Error: calling WSACleanup()");
			throw cleanupException;
        }
	}
	catch(myException* excp)
	{
		excp->response();
		delete excp;
		exit(1);
	}
	winLog << "successful" << endl;

#endif

    return 1;
}
