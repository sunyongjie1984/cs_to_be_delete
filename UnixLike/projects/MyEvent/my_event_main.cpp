// pthread_event.cpp : 定义控制台应用程序的入口点。
//

#include <unistd.h>
#include "my_event.h"

#define PRINT_TIMES 10

//创建一个人工自动重置事件对象
CMyEvent g_myEvent;
int g_iNum = 0;


//线程函数1
void * ThreadProc1(void *pParam)
{
	for (int i = 0; i < PRINT_TIMES; i++)
	{
		g_iNum++;
		cout<<"ThreadProc1 do print, Num = "<<g_iNum<<endl;

		//设置事件为有信号状态
		g_myEvent.Set();

		sleep(1);
	}

	return (void *)0;
}

//线程函数2
void * ThreadProc2(void *pParam)
{
	bool bRet = false;
	while ( 1 )
	{
		if ( g_iNum >= PRINT_TIMES )
		{
			break;
		}

		//以当前事件对象阻塞本线程，将其挂起
		bRet = g_myEvent.Wait();
		if ( bRet )
		{
			cout<<"ThreadProc2 do print, Num = "<<g_iNum<<endl;

			//设置事件为无信号状态
			g_myEvent.Reset();
		}
		else
		{
			cout<<"ThreadProc2 system exception"<<endl;
		}
	}

	return (void *)0;
}


int main(int argc, char* argv[])
{
	pthread_t thread1,thread2;
	pthread_attr_t attr1,attr2;


	//创建两个工作线程
	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_JOINABLE);
	if (pthread_create(&thread1,&attr1, ThreadProc1,NULL) == -1)
	{
		cout<<"Thread 1: create failed"<<endl;
	}
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr2,PTHREAD_CREATE_JOINABLE);
	if (pthread_create(&thread2,&attr2, ThreadProc2,NULL) == -1)
	{
		cout<<"Thread 2: create failed"<<endl;
	}

	//等待线程结束
	void *result;
	pthread_join(thread1,&result);
	pthread_join(thread2,&result);

	//关闭线程，释放资源
	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);

	int iWait;
	cin>>iWait;

	return 0;
}

