#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "queue.h"
#include "dbug.h"

struct work_queue {
  data_control control;
  queue work;
} wq;

typedef struct work_node {
  struct node *next;
  int jobnum;
} wnode;

struct cleanup_queue {
  data_control control;
  queue cleanup;
} cq;

typedef struct cleanup_node {
  struct node *next;
  int threadnum;
  pthread_t tid;
} cnode;

void *threadfunc(void *myarg) {

  wnode *mywork;
  cnode *mynode;

  mynode=(cnode *) myarg;

  //pthread_mutex_lock(&wq.control.mutex);
  //wq.control.cond.Lock();

  while (wq.control.active) {
    while (wq.work.head==NULL && wq.control.active) {
      //pthread_cond_wait(&wq.control.cond, &wq.control.mutex);
      wq.control.cond.Wait();
    }
    if (!wq.control.active) 
      break;
    //we got something!
    mywork=(wnode *) queue_get(&wq.work);
    //pthread_mutex_unlock(&wq.control.mutex);
    //wq.control.cond.Unlock();
    //perform processing...
    printf("Thread number %d processing job %d\n",mynode->threadnum,mywork->jobnum);
    free(mywork);
    //pthread_mutex_lock(&wq.control.mutex);
    //wq.control.cond.Lock();
  }

  //pthread_mutex_unlock(&wq.control.mutex);
  //wq.control.cond.Unlock();

  //pthread_mutex_lock(&cq.control.mutex);
  //cq.control.cond.Lock();
  queue_put(&cq.cleanup,(node *) mynode);
  //pthread_mutex_unlock(&cq.control.mutex);
  //cq.control.cond.Unlock();
  //pthread_cond_signal(&cq.control.cond);
  cq.control.cond.Signal();
  printf("thread %d shutting down...\n",mynode->threadnum);
  return NULL;
  
}

#define NUM_WORKERS 4

int numthreads;

void join_threads(void) {
  cnode *curnode;

  printf("joining threads...\n");

  while (numthreads) {
    //pthread_mutex_lock(&cq.control.mutex);
    //cq.control.cond.Lock();

    while (cq.cleanup.head==NULL) {
      //pthread_cond_wait(&cq.control.cond,&cq.control.mutex);
      cq.control.cond.Wait();
    }

      curnode = (cnode *) queue_get(&cq.cleanup);
      //pthread_mutex_unlock(&cq.control.mutex);
      cq.control.cond.Lock();
      pthread_join(curnode->tid,NULL);
      printf("joined with thread %d\n",curnode->threadnum);
      free(curnode);
      numthreads--;
  }
}


int create_threads(void) {
  int x;
  cnode *curnode;

  for (x=0; x<NUM_WORKERS; x++) {
    curnode=(cnode*)malloc(sizeof(cnode));
    if (!curnode)
      return 1;
    curnode->threadnum=x;
    if (pthread_create(&curnode->tid, NULL, threadfunc, (void *) curnode))
      return 1;
    printf("created thread %d\n",x);
    numthreads++;
  }
  return 0;
}

//
void initialize_structs(void) {
  numthreads=0;
  /*
  if (control_init(&wq.control))
    dabort();
  */
  queue_init(&wq.work);
  /*
  if (control_init(&cq.control)) {
    control_destroy(&wq.control);
    dabort();
  }
  */
  queue_init(&wq.work);
  control_activate(&wq.control);
}

void cleanup_structs(void) {
  //control_destroy(&cq.control);
  //control_destroy(&wq.control);
}


int main(void) {

  int x;
  wnode *mywork;

  initialize_structs();

  /* CREATION */
  if (create_threads()) {
    printf("Error starting threads... cleaning up.\n");
    join_threads();
    dabort();
  }

  //pthread_mutex_lock(&wq.control.mutex);
  //wq.control.cond.Lock();
  for (x=0; x<20; x++) {
    mywork=(wnode*)malloc(sizeof(wnode));
    if (!mywork) {
      //printf("ouch! can't malloc!\n");
      break;
    }
    mywork->jobnum=x;
    queue_put(&wq.work,(node *) mywork);
    printf("produce %d data!\n",x);
  }
  //pthread_mutex_unlock(&wq.control.mutex);
  //wq.control.cond.Unlock();

  //pthread_cond_broadcast(&wq.control.cond);
  wq.control.cond.SignalAll();

  printf("sleeping...\n");
  sleep(2);
  printf("deactivating work queue...\n");
  control_deactivate(&wq.control);

  join_threads();
  cleanup_structs();
}
