/*
 Luong Duc Duong
 jvalFunc.h
 */

#ifndef _JVALFUNC_H
#define _JVALFUNC_H

#include "jval.h"

void swap_gen (Jval a[], int i, int j);
void sort_gen ( Jval a[], int l, int r, int (*compare)(Jval*, Jval*) );
int search_gen ( Jval a[], int l, int r, Jval item, int (*compare)(Jval*, Jval*) );
int compare_i(Jval* a, Jval* b);
Jval* create_array_i (int n);
void print_array_i(Jval a[], int l, int r);

void swap_gen (Jval a[], int i, int j) {
	Jval swap = a[i];
	a[i] = a[j];
	a[j] = swap;
}
void print_array_i(Jval a[], int l, int r) {
	for (int i = l; i <= r; ++i)
	{
		printf("%d - ", jval_i(a[i]));
	}
	printf("\n");
}
void sort_gen ( Jval a[], int l, int r, int (*compare)(Jval*, Jval*) ){
	if (l >= r) return;
	Jval pivot = a[l];
	int i = l, j = r + 1;
	do {
		do {i++;} while (compare(&a[i], &pivot) < 0);
		do {j--;} while (compare(&a[j], &pivot) > 0);
		if (i < j) swap_gen(a, i, j); 
	} while (i < j);
	swap_gen(a, l, j);
	sort_gen(a, l, j - 1, compare);
	sort_gen(a, j + 1, r, compare);
}
int search_gen ( Jval a[], int l, int r, Jval item, int (*compare)(Jval*, Jval*) ){
	if (l > r) return -1;
	int mid = (l + r) / 2;
	if (compare(&a[mid], &item) == 0) return mid;
	else if (compare(&a[mid], &item) > 0) return search_gen(a, l, mid - 1, item, compare);
	else return search_gen(a, mid + 1, r, item, compare);
}
int compare_i(Jval *a, Jval *b) {
	int m = jval_i(*a);
	int n = jval_i(*b);
	if (m == n) return 0;
	return m > n ? 1: -1;
}
Jval* create_array_i (int n) {
	srand(time(NULL));
	Jval *newArr = (Jval *) malloc (n * sizeof(Jval));
	if (newArr == NULL) {
		printf("Memory allocated not successed !\n");
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		newArr[i] = new_jval_i(rand() % 100);
	}
	return newArr;
}
#endif /* jvalFunc.h */
