int main(int argc,char **argv) 
{ 
	char recvbuff[100]; //定义要接收的数据缓冲区

	int sockfd;//定义一个socket套接字，用于通讯

	struct sockaddr_in serveraddr; //定义网络套接字地址结构

	if(argc != 2)
	{
		printf("Usage: echo ip地址");
		exit(0);
	}

	//创建一个用于通讯的套接口
	sockfd = socket(AF_INET,SOCK_STREAM,0); //创建一个套接字
	//END

	//通过设置套接口地址结构，我们说明，客户端要与之通讯的服务器的IP地址和端口.
	bzero(&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family = AF_INET; //指定使用的通讯协议族

	serveraddr.sin_port = htons(5000);//指定要连接的服务器的端口

	inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
	//END

	//调用connect函数来连接服务器
	connect(sockfd,(sockaddr *)&serveraddr,sizeof(serveraddr)); //连接服务器
	//END

	//发送或者接收数据，一般使用send和recv函数调用来实现
	recv(sockfd,recvbuff,sizeof(recvbuff),0); //接收服务器的数据

	printf("%s\n",recvbuff); //打印接收到的数据
	//END

	//终止连接
	close(sockfd); //关闭套接字
	//END
}
