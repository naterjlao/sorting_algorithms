#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

/* Quicksort Algorithm
 * - Pick a pivot point (first, last or random element, best case: average value element)
 * - Partition the array based on pivot (lesser values before and vice versa)
 * - Recursively apply to sub list
 * - Base case: where the list has one or zero elements
 */
int quicksort(void *list, size_t length, size_t size, int (*compare)(void *, void *), int decreasing) {

	int status_l, status_r;
	size_t i, lbuf_i, rbuf_i;

	// base case
	if (length <= 1)
		return 0;

	// recursive case
	// retrieve the last element's value
	void *pivot = malloc(size);
	memcpy(pivot, (list + (size*(length-1))), size);

	// create a buffer array for left and right side values
	lbuf_i = 0;
	rbuf_i = 0;
	void *lbuffer = malloc(length * size);
	void *rbuffer = malloc(length * size);

	// iterate through the list, push values into left or right buffer
	i = 0;
	while (i < length) {
		if (!decreasing && compare((list + (size*i)),pivot) > 0
		   ||decreasing && compare((list + (size*i)),pivot) < 0) {
			// greater values
			memcpy((rbuffer + (size * rbuf_i)),(list + (size * i)),size);
			rbuf_i++;
		} else {
			// lesser or equal values
			memcpy((lbuffer + (size * lbuf_i)),(list + (size * i)),size);
			lbuf_i++;
		}
		i++;
	}


	// copy over the buffers
	memcpy(list, lbuffer, size * lbuf_i);
	memcpy((list + (size * lbuf_i)), rbuffer, size * rbuf_i);

	// cleanup
	if (pivot)
		free(pivot);
	if (lbuffer)
		free(lbuffer);
	if (rbuffer)
		free(rbuffer);

	status_l = quicksort(list, (lbuf_i-1), size, compare, decreasing);
	status_r = quicksort(list + (size * lbuf_i), rbuf_i, size, compare, decreasing);

	return status_l == 0 ? status_r : status_l;
}

