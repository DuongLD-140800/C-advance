#include <stdio.h>
#include <stdlib.h>
#include "jvalFunc.h"
#define MAX 10

int main() {
	Jval *arr = create_array_i(MAX);
	print_array_i(arr, 0, MAX - 1);
	if (arr == NULL) return 1;
	sort_gen(arr, 0, MAX - 1, compare_i);
	print_array_i(arr, 0, MAX - 1);

	printf("\n- Enter number to find position : ");
	int key = 0; scanf("%d", &key); getchar(); 
	printf("Position \"%d\": %d\n",
			 key, search_gen(arr, 0, MAX - 1, new_jval_i(key), compare_i));
	return 0;
}

