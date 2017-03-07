#include 
#include 
#include 
#include 

int main(int argc,char *argv[])
{
	int listensock,//定义两个socket套接字，一个套接字用于监听，
		connsock; //一个套接字用于通讯

	struct sockaddr_in serveraddr; //定义网络套接字地址结构

	const char buff[] = "Hello! Welcome here!\r\n"; //定义要发送的数据缓冲区

	//创建一个用于通讯的套接口
	listensock = socket(AF_INET,SOCK_STREAM,0); //创建一个套接字，用于监听 
	//END

	//给你的套接口设定端口
	bzero(&serveraddr,sizeof(servaddr)); //地址结构清零 

	serveraddr.sin_family = AF_INET; //指定使用的通讯协议族

	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //指定接受任何连接，因为服务器不知道谁会要求连接 

	serveraddr.sin_port = htons(5000); //指定监听的端口

	bind(listensock,(sockaddr *)&serveraddr,sizeof(serveraddr)); //给套接口邦定地址 
	//END

	//使你的套接口成为一个监听套接字
	listen(listensock,1024); //开始监听 
	//END

	//启动你的套接字，这时你的程序就可以等待客户端的连接了
	connsock = accept(listensock,(sockaddr *)NULL, NULL); //建立通讯的套接字，accept函数，等待客户端程序使用connect函数的连接
	//END

	//处理客户端的连接请求
	send(connsock,buff,sizeof(buff), 0); //向客户端发送数据 
	//END

	//终止连接
	close(connsock); //关闭通讯套接字 

	close(listensock); //关闭监听套接字
	//END
}
