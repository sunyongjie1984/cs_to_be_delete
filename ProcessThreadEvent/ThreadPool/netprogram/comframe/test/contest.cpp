#include "sync.h"
#include <pthread.h>

#define SUMSIZE 10
#define BUFSIZE 8
int bufin=0;
int bufout=0;
int buffer[BUFSIZE];

int sum=0;
pthread_cond_t slots= PTHREAD_COND_INITIALIZER;
pthread_cond_t items= PTHREAD_COND_INITIALIZER;

pthread_mutex_t slot_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t item_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t buffer_lock=PTHREAD_MUTEX_INITIALIZER;

int nslots=BUFSIZE;
int producer_done =0;
int nitems=0;

void get_item(int* itemp)
{
    pthread_mutex_lock(&buffer_lock);
    *itemp=buffer[bufout];
    bufout = (bufout +1 )% BUFSIZE;
    pthread_mutex_unlock(&buffer_lock);
    return;
}

void put_item(int item)
{
    pthread_mutex_lock(&buffer_lock);
    buffer[bufin]=item;
    bufin = (bufin +1 )% BUFSIZE;
    pthread_mutex_unlock(&buffer_lock);
    return;
}

void* producer(void* arg)
{
    for(int i=0;i<=SUMSIZE;i++)
    {
	pthread_mutex_lock(&slot_lock);
	while(nslots<=0)
	    pthread_cond_wait(&slots,&slot_lock);
	nslots--;
	pthread_mutex_unlock(&slot_lock);
  
	put_item(i);
	printf("put %d into buffer\n",i);
	pthread_mutex_lock(&item_lock);
	nitems++;
	pthread_cond_signal(&items);
	pthread_mutex_unlock(&item_lock);
    }
    return NULL;
}

void* consumer(void* arg)
{
    int myitem;
    for(int i=0;i<SUMSIZE;i++)
    {
	pthread_mutex_lock(&item_lock);
	while((nitems<=0)&&!producer_done)
	    pthread_cond_wait(&items,&item_lock);
	if((nitems<=0)&&producer_done)
	{
	    pthread_mutex_unlock(&item_lock);
	    break;
	}
	nitems--;
	pthread_mutex_unlock(&item_lock);

	get_item(&myitem);
	printf("Get item is %d\n",myitem);
	pthread_mutex_lock(&slot_lock);
	nslots++;
	pthread_cond_signal(&slots);
	pthread_mutex_unlock(&slot_lock);	
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
