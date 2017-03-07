#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "queue.h"
#include "dbug.h"
#include <time.h>


/* the work_queue holds tasks for the various threads to complete. */
struct work_queue {
  data_control control;
  queue work;
} work_queue;


/* I added a job number to the work node.  Normally, the work node
   would contain additional data that needed to be processed. */

typedef struct work_node {
  struct node *next;
  int jobnum;
} work_node;

/* the cleanup queue holds stopped threads.  Before a thread
   terminates, it adds itself to this list.  Since the main thread is
   waiting for changes in this list, it will then wake up and clean up
   the newly terminated thread. */

struct cleanup_queue {
  data_control control;
  queue cleanup;
} clean_queue;

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
} clean_node;

//
void *threadfunc(void *myarg) {

  work_node *mywork;
  clean_node *mynode;

  mynode=(clean_node *) myarg;

  pthread_mutex_lock(&work_queue.control.mutex);

  while (work_queue.control.active) {
    while (work_queue.work.head==NULL && work_queue.control.active) {
      pthread_cond_wait(&work_queue.control.cond, &work_queue.control.mutex);
    }
    if (!work_queue.control.active) 
      break;
    //we got something!
    mywork=(work_node *) queue_get(&work_queue.work);
    pthread_mutex_unlock(&work_queue.control.mutex);
    //perform processing...
    printf("Thread number %d processing job %d\n",mynode->threadnum,mywork->jobnum);
    free(mywork);
    pthread_mutex_lock(&work_queue.control.mutex);
  }

  pthread_mutex_unlock(&work_queue.control.mutex);

  pthread_mutex_lock(&clean_queue.control.mutex);
  queue_put(&clean_queue.cleanup,(node *) mynode);
  pthread_mutex_unlock(&clean_queue.control.mutex);

  pthread_cond_signal(&clean_queue.control.cond);
  printf("thread %d shutting down...\n",mynode->threadnum);
  return NULL;
  
}

#define NUM_WORKERS 4

int numthreads;

void join_threads(void) {
  clean_node *curnode;

  printf("joining threads...\n");

  while (numthreads) {
    pthread_mutex_lock(&clean_queue.control.mutex);

    /* below, we sleep until there really is a new cleanup node.  This
       takes care of any false wakeups... even if we break out of
       pthread_cond_wait(), we don't make any assumptions that the
       condition we were waiting for is true.  */

    while (clean_queue.cleanup.head==NULL) {
      pthread_cond_wait(&clean_queue.control.cond,&clean_queue.control.mutex);
    }

    /* at this point, we hold the mutex and there is an item in the
       list that we need to process.  First, we remove the node from
       the queue.  Then, we call pthread_join() on the tid stored in
       the node.  When pthread_join() returns, we have cleaned up
       after a thread.  Only then do we free() the node, decrement the
       number of additional threads we need to wait for and repeat the
       entire process, if necessary */

      curnode = (clean_node *) queue_get(&clean_queue.cleanup);
      pthread_mutex_unlock(&clean_queue.control.mutex);
      pthread_join(curnode->tid,NULL);
      printf("joined with thread %d\n",curnode->threadnum);
      free(curnode);
      numthreads--;
  }
}


int create_threads(void) {
  int x;
  clean_node *curnode;

  for (x=0; x<NUM_WORKERS; x++) {
    curnode=(clean_node*)malloc(sizeof(clean_node));
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
  if (control_init(&work_queue.control))
    dabort();
  queue_init(&work_queue.work);
  if (control_init(&clean_queue.control)) {
    control_destroy(&work_queue.control);
    dabort();
  }
  queue_init(&clean_queue.work);
  control_activate(&work_queue.control);
}

void cleanup_structs(void) {
  control_destroy(&clean_queue.control);
  control_destroy(&work_queue.control);
}


int main(void) {

  int x;
  work_node *mywork;

  initialize_structs();

  /* CREATION */
  
  if (create_threads()) {
    printf("Error starting threads... cleaning up.\n");
    join_threads();
    dabort();
  }

  pthread_mutex_lock(&work_queue.control.mutex);
  for (x=0; x<20; x++) {
    mywork=(work_node*)malloc(sizeof(work_node));
    if (!mywork) {
      printf("ouch! can't malloc!\n");
      break;
    }
    mywork->jobnum=x;
    queue_put(&work_queue.work,(node *) mywork);
  }
  pthread_mutex_unlock(&work_queue.control.mutex);

  pthread_cond_broadcast(&work_queue.control.cond);

  printf("sleeping...\n");
  //nanosleep(2,0);
  printf("deactivating work queue...\n");
  control_deactivate(&work_queue.control);
  /* CLEANUP  */

  join_threads();
  cleanup_structs();
}
