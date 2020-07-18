/**
 * Luong Duc Duong
 *
 * C_advance
 * queue.c
 */



#include "queue.h"


Queue initQueue() {
	return new_dllist();
}

int isEmptyQueue(Queue front) {
	return dll_empty(front);
}

void enQueue(Queue front, int v) {
	dll_append(front, new_jval_i(v));
}

int deQueue(Queue front) {
	if (isEmptyQueue(front))
		return -1;

	Dllist first = dll_first(front);
	int vertice = jval_i(first->val);
	dll_delete_node(first);

	return vertice;
}

void freeQueue(Queue front) {
	if (!isEmptyQueue(front))
		free_dllist(front);
}