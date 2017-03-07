// 程序功能：程序读取用户输入的行发送到多播组，加入多播组的任何客户端应该显示从多播组中读到的数据。


//Project Setting -> C/C++ -> Code Generation -> 确认选中"Debug Multithreaded"


#include <process.h> //_beginthread要求

#include "Multicast.h"

using namespace std;

const char* MULTICAST_IP = "224.0.0.99"; //多播组地址
const int MULTICAST_PORT = 2002; //多播组端口

const int BUFFER_SIZE = 1024;


void do_send(void* arg); //读取用户输入并发送到多播组线程函数
void do_read(void* arg); //读物多播组数据函数
int SetOpt(CMulticast &multicast);

int main()
{
	CMulticast multicast;
	
	multicast.Initialize(AF_INET, SOCK_DGRAM, 0);
		
	if ( SetOpt(multicast) )
	{
		return 0;
	}
	
	HANDLE hHandle[2];	//	//创建了两个线程，一个读用户输入并发送，一个读多播组数据	
	hHandle[0] = (HANDLE)_beginthread(do_send,0,(void*)&multicast);
	hHandle[1] = (HANDLE)_beginthread(do_read,0,(void*)&multicast);
	
	//如果用户输入结束，程序就终止了
	WaitForSingleObject(hHandle[0], INFINITE);
	
	return 0;
}


int SetOpt(CMulticast &multicast)
{
	const int on = 1; //允许程序的多个实例运行在同一台机器上
	
	if (-1 == multicast.SetSockOpt( SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on) ) )
	{
		cout<<"Error in setsockopt(SO_REUSEADDR): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	const int routenum = 10;
	
	if (-1 == multicast.SetSockOpt( IPPROTO_IP,	IP_MULTICAST_TTL, (char*)&routenum, sizeof(routenum) ) )
	{
		cout<<"Error in setsockopt(IP_MULTICAST_TTL): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	const int loopback = 0; //禁止回馈
	
	if (-1 == multicast.SetSockOpt( IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&loopback, sizeof(loopback) ) )
	{
		cout<<"Error in setsockopt(IP_MULTICAST_LOOP): "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	sockaddr_in local;
	
	multicast.SetAddr(local, AF_INET, MULTICAST_PORT, INADDR_ANY);
	
	if( -1 == multicast.Bind((sockaddr*)(&local), sizeof(local)) )
	{		
		cout<<"Error in bind: "<<WSAGetLastError()<<endl;
		return -1;
	}
	
	ip_mreq mreq;
	
	multicast.SetMreg(mreq, INADDR_ANY, MULTICAST_IP);
	
	//加入一个多播组
	if ( -1 == multicast.SetSockOpt( IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq) ) )
	{
		cout<<"Error in setsockopt(IP_ADD_MEMBERSHIP): "<<WSAGetLastError()<<endl;
		return -1;
	}
	return 0;
}

void do_send(void* arg)
{
	CMulticast * pM = (CMulticast *)arg;
	
	char sendline[BUFFER_SIZE+1];
	
	sockaddr_in remote;
	pM->SetAddr(remote, AF_INET, MULTICAST_PORT, MULTICAST_IP);
	
	while (true) //读取用户输入知道用户输入"end"
	{
		cout<<"sender : ";
		cin.getline(sendline, BUFFER_SIZE);

		if(strncmp(sendline,"end",3)==0)
			break;
		
		//发送用户输入的数据到多播组
		pM->Send_n(sendline, BUFFER_SIZE, 0, (sockaddr*)(&remote), sizeof(remote)); 
	}
	cout<<"do_send end..."<<endl;
}

void do_read(void* arg)
{
	CMulticast * pM = (CMulticast *)arg;
	
	char buf[BUFFER_SIZE+1];
	
	sockaddr_in client;
	int clientLen;
	
	while (true) //一直读取知道主线程终止
	{
		clientLen = sizeof(client);
		memset(&client, 0, clientLen);
		
		if (pM->Rece_n(buf, BUFFER_SIZE, 0, (sockaddr*)(&clientLen), &clientLen))
		{
			continue;
		}
		cout<<"\r\nreceiver : "<<buf<<endl;
		cout<<"sender : ";
	}
	
	cout<<"do_read end..."<<endl;
}