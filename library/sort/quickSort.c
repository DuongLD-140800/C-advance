#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int A[], int i, int j) {
	int swap = A[i];
	A[i] = A[j];
	A[j] = swap;

}
void printArray(int A[], int size){
	for (int i = 0; i < size; ++i)
	{
		printf("%d -", A[i]);
	}
	printf("\n");
}
void quickSort(int A[], int l, int r) {
	if (r <= l) return;
	int i = l, j = r + 1, pivot = A[l];
	do {
		do i++; while(A[i] < pivot);
		do j--; while(A[j] > pivot);
		if (i < j) swap(A, i, j);
	} while(i < j);
	
	swap(A, j, l);
	quickSort(A, l, j - 1);
	quickSort(A, j + 1, r);
}
void threeWaySort(int A[], int l, int r) {
	if (l > r) return ;
	int i = l - 1, p = l - 1;
	int j = r, q = r;
	int pivot = A[r];
	while (1) {
		while(A[++i] < pivot);
		while(A[--j] > pivot) if(j == l) break;
		if (i >= j) break;
		swap(A, i, j);
		if (A[i] == pivot) swap(A, ++p, i);
		if (A[j] == pivot) swap(A, --q, j);
	}
	swap(A, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l; k <= p; ++k)
		swap(A, k, j--);
	for (int k = r - 1; k >= q; --k)
		swap(A, k, i++);

	threeWaySort(A, l, j);
	threeWaySort(A, i, r);
}
int divideNum(int num) {
	return num / 2;
}
int main() {
	int A[10] = {1, 3, 5, 2, 6, 9, 7, 8, 9, 0};
	threeWaySort(A, 0, 9);
	printArray(A, 10);
	int (*pf)(int);
	pf = &divideNum;
	printf("%d\n", pf(9));
	return 0;
}