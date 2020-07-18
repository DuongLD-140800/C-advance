/**
 * Luong Duc Duong
 *
 * C_advance
 * queue.h
 */

#ifndef _QUEUE_H
#define _QUEUE_H

#include "dllist.h"

typedef Dllist Queue;

Queue initQueue(void);
int isEmptyQueue(Queue front);
void enQueue(Queue front, int v);
int deQueue(Queue front);
void freeQueue(Queue front);


#endif /* queue.h */


