#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bubblesort.h"


/* Performs an in-place bubble sort to the list
 * Params:
 * -list: pointer to the first element of array to be sorted
 * -length: number of elements in list
 * -size: number of bytes per element in list
 * -compare: function pointer to the comparison function
 * -decreasing: set to 0 if sorting ascending, set to 1 if sorting decrementing
 * Returns:
 * -0: if successful
 * -nonzero: if not successful
 */
int bubblesort(void *list, size_t length, size_t size, int (*compare)(void *, void *), int decreasing){
	int status = 0;

	// create a buffer for element swaps
	void *buffer = malloc(size);

	// negates the output of compare() to reduce code redundacy
	int sign = decreasing ? -1 : 0;

	size_t i;
	size_t displacement;
	int sorted = 0;
	while (!sorted) {
		
		// assume sorted until a swap has been performed
		sorted = 1;

		// traverse through the array, find un ordered pairs
		i = 0;
		while (i < length - 1) {

			displacement = i * size;
			// if a pair is found, swap
			if ((!decreasing && 0 < compare(list+displacement,list+displacement+size)) 
				|| (decreasing && 0 > compare(list+displacement,list+displacement+size))) {
				sorted = 0;														// the array is found to be unsorted
				memcpy(buffer,(list+displacement),size);						// push first element to buffer
				memcpy((list+displacement),(list+displacement+size),size);		// push second element to first element
				memcpy((list+displacement+size),buffer,size);					// push buffer to second element
			}

			i++;
		}	
	}

	return status;
}
