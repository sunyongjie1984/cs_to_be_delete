#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* myfirstthread(void*)
{
    int i;
    for(i=0;i<3;i++){
        printf("This is my thread.\n");
    }
}

int main(void)
{
    pthread_t id;
    int i,ret;
    ret=pthread_create(&id,NULL,myfirstthread,NULL);
    if(ret!=0){
        printf ("Create pthread error!\n");
        exit (1);
    }
    for(i=0;i<3;i++){
        printf("This is the main process.\n");
    }
    pthread_join(id,NULL);
    return (0);
}
