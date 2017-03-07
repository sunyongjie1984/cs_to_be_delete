/* queue.c
** Copyright 2000 Daniel Robbins, Gentoo Technologies, Inc.
** Author: Daniel Robbins
** Date: 16 Jun 2000
**
** This set of queue functions was originally thread-aware.  I
** redesigned the code to make this set of queue routines
** thread-ignorant (just a generic, boring yet very fast set of queue
** routines).  Why the change?  Because it makes more sense to have
** the thread support as an optional add-on.  Consider a situation
** where you want to add 5 nodes to the queue.  With the
** thread-enabled version, each call to queue_put() would
** automatically lock and unlock the queue mutex 5 times -- that's a
** lot of unnecessary overhead.  However, by moving the thread stuff
** out of the queue routines, the caller can lock the mutex once at
** the beginning, then insert 5 items, and then unlock at the end.
** Moving the lock/unlock code out of the queue functions allows for
** optimizations that aren't possible otherwise.  It also makes this
** code useful for non-threaded applications.
**
** We can easily thread-enable this data structure by using the
** data_control type defined in control.c and control.h.  */

#include <stdio.h>
#include "queue.h"

void queue_init(queue *myroot) {
  myroot->head=NULL;
  myroot->tail=NULL;
}

void queue_put(queue *myroot,node *mynode) {
  mynode->next=NULL;
  if (myroot->tail!=NULL)
    myroot->tail->next=mynode;
  myroot->tail=mynode;
  if (myroot->head==NULL)
    myroot->head=mynode;
}

node *queue_get(queue *myroot) {
  //get from root
  node *mynode;
  mynode=myroot->head;
  if (myroot->head!=NULL)
    myroot->head=myroot->head->next;
  return mynode;
}
