/* queue.h
** Copyright 2000 Daniel Robbins, Gentoo Technologies, Inc.
** Author: Daniel Robbins
** Date: 16 Jun 2000
*/

typedef struct node {
  struct node *next;
} node;

typedef struct queue {
  node *head, *tail; 
} queue;

void queue_init(queue *myroot);
void queue_put(queue *myroot, node *mynode);
node *queue_get(queue *myroot);
