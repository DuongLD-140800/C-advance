/**
 * Luong Duc Duong
 *
 * C_advance
 * stack.h
 */

#ifndef _STACK_H
#define _STACK_H


#include "dllist.h"

typedef Dllist Stack;

Stack initStack(void);
void pushStack(Stack top, int v);
int popStack(Stack top);
int peekStack(Stack top);
int isEmptyStack(Stack top);
void freeStack(Stack top);


#endif /* stack.h */


