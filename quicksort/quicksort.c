#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"


void swap(void *a, void *b, size_t size) {
	void *buffer = malloc(size);

	memcpy(buffer,a,size);
	memcpy(a,b,size);
	memcpy(b,buffer,size);

	free(buffer);
}


/* Quicksort Algorithm
 * - Pick a pivot point (first, last or random element, best case: average value element)
 * - Partition the array based on pivot (lesser values before and vice versa)
 * - Recursively apply to sub list
 * - Base case: where the list has one or zero elements
 */
int quicksort(void *list, size_t length, size_t size, int (*compare)(void *, void *), int decreasing) {
	int status = 0;

	// base case
	if (length <= 1)
		goto done;

	// recursive case
	// retrieve the last element's value
	void *pivot = malloc(size);
	malloc(pivot, (list + (size*(length-1))), size);

	// create a buffer array for all greater values
	size_t buf_i = 0;
	void *buffer = malloc(length * size);

	// iterate through the list, push all greater values in buffer and shift array as needed
	size_t i = 0;
	while (i < length - 1) {
		if (compare((list + (size*i)),pivot) > 0) {
			memcpy((buffer + (size*buf_i)),(list + (size*i)),size);
			buffer_i++;
			// TODO shift array backwards
		}
		i++;
	}

	// copy over the buffer to the back of the pivot
	// TODO

done:
	if (pivot)
		free(pivot);
	if (buffer)
		free(buffer);
	return status;
}

