#include "../sync/sync.h"
#include <pthread.h>
#include "Thread.h"
#include "TestThread.h"
#include "Job.h"
#include "ThreadPool.h"
#include "list.h"

#define SUMSIZE 10
#define BUFSIZE 8
int bufin=0;
int bufout=0;
int buffer[BUFSIZE];

CCondition slots_cond;
CCondition items_cond;

CThreadMutex buffer_lock;
CThreadMutex slots_lock;
CThreadMutex items_lock;

int nslots=BUFSIZE;
int producer_done =0;
int nitems=0;

void get_item(int* itemp)
{
    buffer_lock.Lock();
    *itemp=buffer[bufout];
    bufout = (bufout +1 )% BUFSIZE;
    buffer_lock.Unlock();
    return;
}

void put_item(int item)
{
    buffer_lock.Lock();
    buffer[bufin]=item;
    bufin = (bufin +1 )% BUFSIZE;
    buffer_lock.Unlock();
    return;
}

void* producer(void* arg)
{
    for(int i=0;i<=SUMSIZE;i++)
    {
	while(nslots<=0)
	{
	    printf("Wait for idle item to produce\n");
	    slots_cond.Wait();
	}
	//slots_lock.Lock();
	nslots--;
	//slots_lock.Unlock();
  
	put_item(i);
	printf("put %d into buffer\n",i);
	//items_lock.Lock();
	nitems++;
	//items_lock.Unlock();
	printf("Send signal to consume\n");
	items_cond.Signal();
    }
    return NULL;
}

void* consumer(void* arg)
{
    int myitem;
    //for(int i=0;i<SUMSIZE+100;i++)
    for(;;)
    {
	while((nitems<=0)&&!producer_done)
	{
	    printf("Wait for item\n");
	    items_cond.Wait();
	}
	if((nitems<=0)&&producer_done)
	{
	    break;
	}
	//items_lock.Lock();
	nitems--;
	//items_lock.Unlock();

	get_item(&myitem);
	printf("Get item is %d\n",myitem);
	//slots_lock.Lock();
	nslots++;
	//slots_lock.Unlock();
	slots_cond.Signal();
    }
    return NULL;
}

int main()
{
    list<CTestThread*> thrlist;
    
    //for(int i=0;i<4;i++)
    {
	CTestThread* producer= new CTestThread();
	thrlist.push_front(producer);
	producer->Start();
    }

/*
    list<CTestThread*>::iterator iter = thrlist.begin();
    while(iter != thrlist.end())
    {
	(CTestThread*)iter.Join();
	iter++;
    }
*/
 
    sleep(1);
    return 0;
}
