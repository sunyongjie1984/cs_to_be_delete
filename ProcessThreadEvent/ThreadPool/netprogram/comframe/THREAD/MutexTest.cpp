#include "../Sync.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

CThreadMutex mutex;

int myglobal=0;
void* thread_function(void* arg)
{
    int i,j=0;
    for(i=0;i<20;i++)
    {
	mutex.Lock();
	j=myglobal;
	j++;
	printf(".	%d	subthread\n",myglobal);
	fflush(stdout);
	sleep(2);
	myglobal=j;
	mutex.Unlock();	
    }
}

int main()
{
    pthread_t mythread;
    int i;
    if(pthread_create(&mythread,NULL,thread_function,NULL))
    {
	printf("error to create thread\n");
	abort();
    }
    for(i=0;i<20;i++)
    {
	mutex.Lock();
	myglobal = myglobal +1;
	mutex.Unlock();	

	printf("o	%d	parentthread\n",myglobal);
	fflush(stdout);
	sleep(1);
    }

    if(pthread_join(mythread,NULL))
    {
	printf("error joining thread!");
	abort();
    }
    printf("\nmyglobal equals %d\n",myglobal);
    exit(0);
}
