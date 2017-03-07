#include "myHostInfo.h"
#include "..\myLog\myLog.h"
#include "..\myException\myException.h"

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
        
    // Retrieve the host name and host address given the host name

	string hName = "www.yuchen.net";
	winLog << endl;
	winLog << "Retrieve the host name and host address given the host name:" << endl;
	winLog << "		==> the given domain name is " << hName << endl;
	
    myHostInfo hostName(hName, NAME);
	string givenHostName = hostName.getHostName();
	string givenHostAddr = hostName.getHostIPAddress();
    cout << "Server name: "  << givenHostName << endl;
    cout << "Server IP address: "  << givenHostAddr << endl;
	winLog << "		==> Name: " << givenHostName << endl;
	winLog << "		==> Address: " << givenHostAddr << endl;

    // Retrieve the host name and host address given the host address
/*
	string IPaddress = "209.86.128.254";
	winLog << endl;
	winLog << "Retrieve the host name and host address given the host address:" << endl;
	winLog << "		==> the given address is " << IPaddress << endl;

    myHostInfo hostAddress(IPaddress, ADDRESS);
	givenHostName = hostAddress.getHostName();
	givenHostAddr = hostAddress.getHostIPAddress();
    cout << "Name: " << givenHostName << endl;
    cout << "Address: " << givenHostAddr << endl;
	winLog << "		==> Name: " << givenHostName << endl;
	winLog << "		==> Address: " << givenHostAddr << endl;
    
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
*/
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
