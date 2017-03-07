#include "..\mySocket\mySocket.h"
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
	winLog << "Retrieve the local host name and address:" << endl;
	
    myHostInfo uHostAddress;
	string localHostName = uHostAddress.getHostName();
    string localHostAddr = uHostAddress.getHostIPAddress();
	cout << "------------------------------------------------------" << endl;
	cout << "	My local host information:" << endl;
	cout << "		Name:    " << localHostName << endl;
    cout << "		Address: " << localHostAddr << endl;
	cout << "------------------------------------------------------" << endl;

	winLog << "		==> Name: " << localHostName << endl;
	winLog << "		==> Address: " << localHostAddr << endl;

	// open socket on the local host
	myTcpSocket myServer(PORTNUM);
	cout << myServer;
	winLog << "server configuation: " << endl;
	winLog << myServer;

    myServer.bindSocket();
	cout   << endl << "server finishes binding process... " << endl;
	winLog << endl << "server finishes binding process... " << endl;
	
	myServer.listenToClient();
	cout   << "server is listening to the port ... " << endl;
	winLog << "server is listening to the port ... " << endl;

    // wait to accept a client connection.  
	// processing is suspended until the client connects
	cout   << "server is waiting for client connecction ... " << endl;
	winLog << "server is waiting for client connnection ... " << endl;

    myTcpSocket* client;    // connection dedicated for client communication
    string clientHost;      // client name etc. 
    client = myServer.acceptClient(clientHost);
        
    cout   << endl << "==> A client from [" << clientHost << "] is connected!" << endl << endl;
	winLog << endl << "==> A client from [" << clientHost << "] is connected!" << endl << endl;

	while(1)
	{
		string clientMessageIn = "";
		
		// receive from the client

        int numBytes = client->recieveMessage(clientMessageIn);
		if ( numBytes == -99 ) break;

		cout   << "[RECV:" << clientHost << "]: " << clientMessageIn << endl;
		winLog << "[RECV:" << clientHost << "]: " << clientMessageIn << endl;

		// send to the clien

		char sendmsg[MAX_MSG_LEN+1];
		memset(sendmsg,0,sizeof(sendmsg));
		cout << "[" << localHostName << ":SEND] ";
		cin.getline(sendmsg,MAX_MSG_LEN);

		if ( numBytes == -99 ) break;
		string sendMsg(sendmsg);
		if ( sendMsg.compare("Bye") == 0 || sendMsg.compare("bye") == 0 )
			break;
		//cout   << "[" << localHostName << ": SEND] " << sendMsg << endl;
		winLog << "[" << localHostName << ": SEND] " << sendMsg << endl;
	
		client->sendMessage(sendMsg);
    }

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