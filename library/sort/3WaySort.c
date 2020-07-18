#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX 1000000


typedef struct test {
	int key;
	char keyChar[30];
}test;

void printArray(int a[], int size) {
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void exch(void *buff, int i, int j, size_t size) {
	void *swap = malloc(size);
	void *p1 = buff + i * size;
	void *p2 = buff + j * size;
	memcpy(swap, p1, size);
	memcpy(p1, p2, size);
	memcpy(p2, swap, size);
	free(swap);
}
void sort(void *buff, int l, int r, size_t size, int (*compare)(const void *, const void *)) {
	if (l > r) return;
	int i = l - 1, p = l - 1;
	int j = r, q = r;
	void *pevot = buff + r*size;
	while (1) {
		while(compare((buff + (++i)*size), pevot) < 0);
		while(compare((buff + (--j)*size), pevot) > 0) if(j == l) break;
		if (i >= j) break;
		exch(buff, i, j, size);
		if (compare((buff + i*size), pevot) == 0)
			exch(buff, i, ++p, size);
		if (compare((buff + j*size), pevot) == 0)
			exch(buff, j, --q, size);
	}
	exch(buff, i, r, size);
	j = i - 1;
	i = i + 1;
	for (int k = l; k <= p; k++) 
		exch(buff, k, j--, size);
	for (int k = r - 1; k >= q; k--) 
		exch(buff, k, i++, size);
	sort(buff, l, j, size, compare);
	sort(buff, i, r, size, compare);
}
void quickSort(int A[], int l, int r) {
	if (r <= l) return;
	int i = l, j = r + 1, pivot = A[l];
	do {
		do i++; while(A[i] < pivot);
		do j--; while(A[j] > pivot);
		if (i < j) exch(A, i, j, sizeof(int));
	} while(i < j);
	
	exch(A, j, l, sizeof(int));
	quickSort(A, l, j - 1);
	quickSort(A, j + 1, r);
}
void createArray(int **a) {
	srand(time(NULL));
	*a = (int *) malloc(MAX * sizeof(int));
	for (int i = 0; i < MAX; ++i)
	{
		*(*a + i) = rand() % 10;
	}
}
int int_Compare(const void *x,const void *y) {
	int m = *((int *)x);
	int n = *((int *)y);
	if (m == n) return 0;
	return m > n ? 1:-1;
}
int struct_Compare(const void *x, const void *y) {
	test m = *((test *)x);
	test n = *((test *)y);
	return strcmp(m.keyChar, n.keyChar);
}
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int *a1 = NULL;
	int *a2 = NULL;
	clock_t start, end;
	double cpu_time_used;

	//quick Sort
	createArray(&a2);
	start = clock();
	quickSort(a2, 0, MAX - 1);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time <quickSort> : %f\n", cpu_time_used);
	free(a2);

	//threeWaySort
	createArray(&a1);
	start = clock();
	sort(a1, 0, MAX - 1, sizeof(int), int_Compare);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("cpu time <3WaySort> : %f\n", cpu_time_used);
	free(a1);

	return 0;
}
