#include <stdio.h>
#include <stdlib.h>
#include "bubblesort.h"
#include "mergesort.h"
#include "quicksort.h"
#include "analysis.h"

#if ANALYSIS
extern unsigned int ncompares = 0;
extern unsigned int nmoves = 0;
#endif

int int_compare(void *a_ptr, void *b_ptr) {
	// cast to int
	int a = *((int *) a_ptr);
	int b = *((int *) b_ptr);

	return a - b;
}

void print_int_array(int *list, size_t length) {
	size_t i = 0;

	while (i < length) {
		printf("%d ",list[i]);
		i++;
	}
	printf("\n");
}

int main() {
	int status;

	int arr[] = {6,3,4,7,8,5,1,0,2,9};

	print_int_array(&arr[0],10);
	bubblesort(arr,10,sizeof(int),int_compare,0);
	print_int_array(&arr[0],10);
	ANALYZE();
	bubblesort(arr,10,sizeof(int),int_compare,1);
	print_int_array(&arr[0],10);
	ANALYZE();

	return status;
}
