#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

/* Mergesort Algorithm
 * - Split the array in half
 * - Apply mergesort to each partition
 * - Take the resulting partitions and arrange them to order
 * - Base case: where the array has one or zero elements
 */
int mergesort(void *list, size_t length, size_t size, int (*compare)(void *, void *), int decreasing) {

	int status_l, status_r;
	size_t i, left_i, right_i;

	// base case
	if (length <= 1)
		return 0;

	// recursive case
	// find the middle and split (left.length <= right.length)
	size_t middle_index = length / 2;
	void *left = malloc(middle_index * size);
	void *right = malloc((length - middle_index) * size);
	memcpy(left,list,middle_index * size);
	memcpy(right,(list + (middle_index * size)),((length - middle_index) * size));

	// sort the partitions
	status_l = mergesort(left,middle_index,size,compare,decreasing);
	status_r = mergesort(right,(length - middle_index),size,compare,decreasing);

	if (status_l || status_r)
		goto done;

	// shuffle back into list
	i = 0; left_i = 0; right_i = 0;
	void *left_elem = malloc(size);
	void *right_elem = malloc(size);
	while (i < length) {
		if (
			left_i < middle_index
			&& ((!decreasing && compare((left + (left_i * size)),(right + (right_i * size))) < 0)
			|| (decreasing && compare((left + (left_i * size)),(right + (right_i * size))) >= 0))
			) {
			// push left back to list
			memcpy(list + (i * size),(left + (left_i * size)),size);
			left_i++;
		} else if (
			right_i < (length - middle_index)
			&& ((!decreasing && compare((left + (left_i * size)),(right + (right_i * size))) >= 0)
			|| (decreasing && compare((left + (left_i * size)),(right + (right_i * size))) < 0))	
			) {
			// push right back into list
			memcpy(list + (i * size),(right + (right_i * size)),size);
			right_i++;
		} else {
			// push the remaining elements
			if (left_i < middle_index) {
				memcpy(list + (i * size),(left + (left_i * size)),size);
				left_i++;
			} else if (right_i < (length - middle_index)) {
				memcpy(list + (i * size),(right + (right_i * size)),size);
				right_i++;
			}
		}
		i++;
	}

done:
	if (left)
		free(left);
	if (right)
		free(right);
	if (left_elem)
		free(left_elem);
	if (right_elem)
		free(right_elem);
	return status_l == 0 ? status_r : status_l;

}

