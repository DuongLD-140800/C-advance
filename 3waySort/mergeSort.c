#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(void *buff, size_t size, int l, int m, int r, int (*compare)(void const *, void const *)) {
    void *tmp = NULL;
    tmp = malloc ((r - l + 1) * size);
    if (tmp == NULL) {
        fprintf(stderr, "Malloc failed");
        exit(-1);
    }
    char *tempL = NULL, *tempR = NULL, *temp = NULL;
    int i = l, j = m + 1, k = 0;
    /*
    	i Left    j Right     k tmp
    */
    while (i <= m && j <= r) {
        tempL = (void *) (buff + i * size);
        tempR = (void *) (buff + j * size);
        temp  = (void *) (tmp + k * size);
        if (compare(tempL, tempR) >= 0) {
            memcpy(temp, tempR, size);
            j++; k++;
        } else {
            memcpy(temp, tempL, size);
            i++; k++;
        }
    }
    while (i <= m) {
        tempL = (void *) (buff + i * size);
        temp = (void *) (tmp + k * size);
        memcpy(temp, tempL, size);
        i++; k++;
    }
    while (j <= r) {
        tempR = (void *) (buff + j * size);
        temp = (void *) (tmp + k * size);
        memcpy(temp, tempR, size);
        j++; k++;
    }
    for (i = 0; i <= r - l; i++)
        memcpy(buff + (i + l)*size, tmp + i*size, size);
    free(tmp);
}
void mergeSort(void *buff, size_t size, int l, int r, int (*compare)(void const *, void const *)) {
	if (l >= r) return;
	int mid = (l + r) / 2;
	mergeSort(buff, size, l, mid, compare);
	mergeSort(buff, size, mid + 1, r, compare);
	merge(buff, size, l, mid, r, compare);
}