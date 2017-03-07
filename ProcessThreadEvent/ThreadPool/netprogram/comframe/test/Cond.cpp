#include "sync.h"
#include <pthread.h>

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
	    slots_cond.Wait();
	//slots_lock.Lock();
	nslots--;
	//slots_lock.Unlock();
  
	put_item(i);
	printf("put %d into buffer\n",i);
	//items_lock.Lock();
	nitems++;
	//items_lock.Unlock();
	items_cond.Signal();
    }
    return NULL;
}

void* consumer(void* arg)
{
    int myitem;
    for(int i=0;i<SUMSIZE;i++)
    {
	while((nitems<=0)&&!producer_done)
	    items_cond.Wait();
	if((nitems<=0)&&producer_done)
	{
	    //items_cond.Unlock();
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
    pthread_t producerid;
    pthread_t consumerid;
    
    pthread_create(&producerid,NULL,producer,NULL);
    pthread_create(&consumerid,NULL,consumer,NULL);

    pthread_join(producerid,NULL);
    pthread_join(consumerid,NULL);
    return 0;
}
