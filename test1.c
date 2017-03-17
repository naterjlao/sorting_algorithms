#include <stdio.h>
#include <stdlib.h>
#include "sorting_algorithms.h"
#define BUBBLE_SORT 1
#define BUBBLE_SORT_MOD 2
#define INSERTION_SORT 3
#define SELECTION_SORT 4
#define MERGE_SORT 5
#define HEAP_SORT 6
#define QUICK_SORT 7

/*Change these:*/
#define SORT_TYPE 6
#define PRINT_STEPS 1

/*---------------MAIN DRIVER---------------*/
int main(void) {
	int list[] = {4, 10, 6, 1, 9, 5, 2, 3, 8, 7};
	int size = sizeof(list) / sizeof(int);
	int num_cmpr = 0;
	int num_exch = 0;
	void (*sort) (int[], int, int *, int *);

#if SORT_TYPE == 1
	sort = bubble_sort;
#elif SORT_TYPE == 2
	sort = bubble_sort_mod;
#elif SORT_TYPE == 3
	sort = insertion_sort;
#elif SORT_TYPE == 4
	sort = selection_sort;
#elif SORT_TYPE == 5
	sort = merge_sort;
#elif SORT_TYPE == 6
	sort = heap_sort;
#elif SORT_TYPE == 7
	sort = quick_sort;
#else
	sort = no_sort;
#endif

	/*Display starting state*/
	printf("Before:\n");
	print_int_array(list, size);

	/*Perform the sort*/
	sort(list, size, &num_cmpr, &num_exch);

	/*Display results*/
	printf("After:\n");
	print_int_array(list, size);
	printf("Number of Comprisons: %d\nNumber of Exchanges: %d\n",
	       num_cmpr, num_exch);

	return 0;
}