#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "queue.h"
#include "dbug.h"

/* the work_queue holds tasks for the various threads to complete. */
struct work_queue {
  data_control control;
  queue work;
} wq;


/* I added a job number to the work node.  Normally, the work node
   would contain additional data that needed to be processed. */

typedef struct work_node {
  struct node *next;
  int jobnum;
} wnode;

/* the cleanup queue holds stopped threads.  Before a thread
   terminates, it adds itself to this list.  Since the main thread is
   waiting for changes in this list, it will then wake up and clean up
   the newly terminated thread. */

struct cleanup_queue {
  data_control control;
  queue cleanup;
} cq;

/* I added a thread number (for debugging/instructional purposes) and
   a thread id to the cleanup node.  The cleanup node gets passed to
   the new thread on startup, and just before the thread stops, it
   attaches the cleanup node to the cleanup queue.  The main thread
   monitors the cleanup queue and is the one that performs the
   necessary cleanup. */

typedef struct cleanup_node {
  struct node *next;
  int threadnum;
  pthread_t tid;
} cnode;

void *threadfunc(void *myarg) {

  wnode *mywork;
  cnode *mynode;

  mynode=(cnode *) myarg;

  pthread_mutex_lock(&wq.control.mutex);

  while (wq.control.active) {
    while (wq.work.head==NULL && wq.control.active) {
      pthread_cond_wait(&wq.control.cond, &wq.control.mutex);
    }
    if (!wq.control.active) 
      break;
    //we got something!
    mywork=(wnode *) queue_get(&wq.work);
    pthread_mutex_unlock(&wq.control.mutex);
    //perform processing...
    printf("Thread number %d processing job %d\n",mynode->threadnum,mywork->jobnum);
    free(mywork);
    pthread_mutex_lock(&wq.control.mutex);
  }

  pthread_mutex_unlock(&wq.control.mutex);

  pthread_mutex_lock(&cq.control.mutex);
  queue_put(&cq.cleanup,(node *) mynode);
  pthread_mutex_unlock(&cq.control.mutex);
  pthread_cond_signal(&cq.control.cond);
  printf("thread %d shutting down...\n",mynode->threadnum);
  return NULL;
  
}

#define NUM_WORKERS 4

int numthreads;

void join_threads(void) {
  cnode *curnode;

  printf("joining threads...\n");

  while (numthreads) {
    pthread_mutex_lock(&cq.control.mutex);

    /* below, we sleep until there really is a new cleanup node.  This
       takes care of any false wakeups... even if we break out of
       pthread_cond_wait(), we don't make any assumptions that the
       condition we were waiting for is true.  */

    while (cq.cleanup.head==NULL) {
      pthread_cond_wait(&cq.control.cond,&cq.control.mutex);
    }

    /* at this point, we hold the mutex and there is an item in the
       list that we need to process.  First, we remove the node from
       the queue.  Then, we call pthread_join() on the tid stored in
       the node.  When pthread_join() returns, we have cleaned up
       after a thread.  Only then do we free() the node, decrement the
       number of additional threads we need to wait for and repeat the
       entire process, if necessary */

      curnode = (cnode *) queue_get(&cq.cleanup);
      pthread_mutex_unlock(&cq.control.mutex);
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
    curnode=malloc(sizeof(cnode));
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
  if (control_init(&wq.control))
    dabort();
  queue_init(&wq.work);
  if (control_init(&cq.control)) {
    control_destroy(&wq.control);
    dabort();
  }
  queue_init(&wq.work);
  control_activate(&wq.control);
}

void cleanup_structs(void) {
  control_destroy(&cq.control);
  control_destroy(&wq.control);
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

  pthread_mutex_lock(&wq.control.mutex);
  for (x=0; x<1600; x++) {
    mywork=malloc(sizeof(wnode));
    if (!mywork) {
      printf("ouch! can't malloc!\n");
      break;
    }
    mywork->jobnum=x;
    queue_put(&wq.work,(node *) mywork);
  }
  pthread_mutex_unlock(&wq.control.mutex);
  pthread_cond_broadcast(&wq.control.cond);

  printf("sleeping...\n");
  sleep(2);
  printf("deactivating work queue...\n");
  control_deactivate(&wq.control);
  /* CLEANUP  */

  join_threads();
  cleanup_structs();
}
