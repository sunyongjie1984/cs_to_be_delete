#include "..\mySocket\mySocket.h"
#include "..\myLog\myLog.h"
#include "..\myException\myException.h"
#include "..\myHostInfo\myHostInfo.h"

myLog winLog;
string serverIPAddress = "";

void readServerConfig();
void checkFileExistence(const string&);

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
	winLog << "Retrieve the localHost [CLIENT] name and address:" << endl;
	
    myHostInfo uHostAddress;
	string localHostName = uHostAddress.getHostName();
    string localHostAddr = uHostAddress.getHostIPAddress();
    cout << "Name: " << localHostName << endl;
    cout << "Address: " << localHostAddr << endl;
	winLog << "		==> Name: " << localHostName << endl;
	winLog << "		==> Address: " << localHostAddr << endl;

	// get server's information

	readServerConfig();
	winLog << endl;
	winLog << "Retrieve the remoteHost [SERVER] name and address:" << endl;
	winLog << "		==> the given address is " << serverIPAddress << endl;

    myHostInfo serverInfo(serverIPAddress,ADDRESS);
	string serverName = serverInfo.getHostName();
	string serverAddr = serverInfo.getHostIPAddress();
    cout << "Name: " << serverName << endl;
    cout << "Address: " << serverAddr << endl;
	winLog << "		==> Name: " << serverName << endl;
	winLog << "		==> Address: " << serverAddr << endl;

    // an instance of the myTcpSocket is created.  At this point a TCP 
    // socket has been created and a port has been defined.
    myTcpSocket myClient(PORTNUM);
	myClient.setLingerOnOff(true);
	myClient.setLingerSeconds(10);

	cout << myClient;
	winLog << "client configuation: " << endl;
	winLog << myClient;

    // connect to the server.
	cout   << "connecting to the server [" << serverName << "] ... " << endl;
	winLog << "connecting to the server [" << serverName << "] ... " << endl;
	myClient.connectToServer(serverAddr,ADDRESS);

	int recvBytes = 0;

	while (1)
	{
		// send message to server

		char sendmsg[MAX_MSG_LEN+1];
		memset(sendmsg,0,sizeof(sendmsg));
		cout << "[" << localHostName << ":SEND] ";
		cin.getline(sendmsg,MAX_MSG_LEN);

		string sendMsg(sendmsg);
		if ( sendMsg.compare("Bye") == 0 || sendMsg.compare("bye") == 0 ) break;

		//cout   << "[" << localHostName << ": SEND] " << sendMsg << endl;
		winLog << "[" << localHostName << ": SEND] " << sendMsg << endl;
		myClient.sendMessage(sendMsg);

		// receive message from server

		string clientMessageIn = "";
        recvBytes = myClient.recieveMessage(clientMessageIn);
		if ( recvBytes == -99 ) break;

		cout   << "[RECV:" << serverName << "]: " << clientMessageIn << endl;
		winLog << "[RECV:" << serverName << "]: " << clientMessageIn << endl;

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

void readServerConfig()
{
	string serverConfigFile = "serverConfig.txt";	
	checkFileExistence(serverConfigFile);
	ifstream serverConfig(serverConfigFile.c_str());

	// read server's IP address
	getline(serverConfig,serverIPAddress);
    //istrstream In(inLine.c_str());
    //In >> serverIPAddress;

	serverConfig.close();
}

void checkFileExistence(const string& fileName)
{
	ifstream file(fileName.c_str());
	if (!file) 
	{
		cout << "Cannot continue:" << fileName << " does NOT exist!" << endl;
		exit(1);
	}
	file.close();
}