/* control.c
** Copyright 2000 Daniel Robbins, Gentoo Technologies, Inc.
** Author: Daniel Robbins
** Date: 16 Jun 2000
**
** These routines provide an easy way to make any type of
** data-structure thread-aware.  Simply associate a data_control
** structure with the data structure (by creating a new struct, for
** example).  Then, simply lock and unlock the mutex, or
** wait/signal/broadcast on the condition variable in the data_control
** structure as needed.
**
** data_control structs contain an int called "active".  This int is
** intended to be used for a specific kind of multithreaded design,
** where each thread checks the state of "active" every time it locks
** the mutex.  If active is 0, the thread knows that instead of doing
** its normal routine, it should stop itself.  If active is 1, it
** should continue as normal.  So, by setting active to 0, a
** controlling thread can easily inform a thread work crew to shut
** down instead of processing new jobs.  Use the control_activate()
** and control_deactivate() functions, which will also broadcast on
** the data_control struct's condition variable, so that all threads
** stuck in pthread_cond_wait() will wake up, have an opportunity to
** notice the change, and then terminate.
*/

#include "control.h"

int control_init(data_control *mycontrol) {
/*
  if (pthread_mutex_init(&(mycontrol->mutex),NULL))
    return 1;
  if (pthread_cond_init(&(mycontrol->cond),NULL))
    return 1;
*/
  mycontrol->active=0;
  return 0;
}

int control_destroy(data_control *mycontrol) {
/*
  if (pthread_mutex_destroy(&(mycontrol->mutex)))
    return 1;
  if (pthread_cond_destroy(&(mycontrol->cond)))
    return 1;
*/
  mycontrol->active=0;
  return 0;
}
int control_activate(data_control *mycontrol) {
/*
  if (pthread_mutex_lock(&(mycontrol->mutex)))
    return 0;
*/
  mycontrol->cond.Lock();
  mycontrol->active=1;
  mycontrol->cond.Unlock();
/*
  pthread_mutex_unlock(&(mycontrol->mutex));
  pthread_cond_broadcast(&(mycontrol->cond));
*/
  return 1;
}

int control_deactivate(data_control *mycontrol) {
/*
  if (pthread_mutex_lock(&(mycontrol->mutex)))
    return 0;
*/
  mycontrol->cond.Lock();
  mycontrol->active=0;
  mycontrol->cond.Unlock();
  mycontrol->cond.SignalAll();
/*
  pthread_mutex_unlock(&(mycontrol->mutex));
  pthread_cond_broadcast(&(mycontrol->cond));
*/
  return 1;
}
