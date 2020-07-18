/**
 * Luong Duc Duong
 *
 * C_advance
 * stack.c
 */


#include "stack.h"


Stack initStack() {
	return new_dllist();
}

int isEmptyStack(Stack top) {
	return dll_empty(top);
}

void pushStack(Stack top, int v) {
	dll_prepend(top, new_jval_i(v));
}

int peekStack(Stack top) {
	if (isEmptyStack(top)) return -1;

	Stack node = dll_first(top);
	return jval_i(node->val);
}

int popStack(Stack top) {
	if (isEmptyStack(top)) return -1;

	Stack node = dll_first(top);
	int vertice = jval_i(node->val);
	dll_delete_node(node);

	return vertice;
}

void freeStack(Stack top) {
	if (!isEmptyStack(top))
		free_dllist(top);
}

