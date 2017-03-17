#include <stdio.h>
#include <stdlib.h>
#include "sorting_algorithms.h"

/*---------------Private Utility Prototypes---------------*/
int get_smallest (int[], int);
void switch_int_array (int[], int, int);
void heapsift_up (int[], int, int, int *, int *);
void heapsift_down (int[], int, int, int *, int *);
int* makeheap (int[], int, int *, int *);
void quick_sort_aux (int[], int, int, int *, int *);

/*---------------Sorting Functions---------------*/

/*Largest elements 'float' (switches) to the top*/
void bubble_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, j, temp;
	printf("<< Performing Bubblesort >>\n");
	for (i = size - 1; i >= 1; i--) {
		for (j = 0; j < i; j++) {
			/*if the current element is greater than the next element*/
			if ((*num_cmpr)++, list[j] > list[j + 1]) {
#if PRINT_STEPS
				print_int_array(list, size);
#endif
				switch_int_array(list, j, j + 1); (*num_exch)++; /*perform the switch*/
			}
		}
	}
}

/*Performs the bubblesort but reduces the amount of comparisons needed
by ignoring the end part of the list the algorithm knows it's sorted*/
void bubble_sort_mod (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, j, t, temp;
	printf("<< Performing Bubblesort (Modified)>>\n");
	i = size - 2;
	while (i >= 0) {
		t = 0;
		for (j = 0; j <= i; j++) {
			if ((*num_cmpr)++, list[j] > list[j + 1]) {
#if PRINT_STEPS
				print_int_array(list, size);
#endif
				switch_int_array(list, j, j + 1); (*num_exch)++; /*perform the switch*/
				t = j; /*saves last known position*/
			}
		}
		i = t - 1;
	}
}

/*Takes in a element one at a time and sorts within the list*/
void insertion_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, j, t;
	int t_list [size + 1];
	printf("<< Performing Insertion Sort >>\n");

	/*This uses a sentinel, so t_list will have all the elements of list with
	a (smallest_element - 1) appended to the front of the array at index 0*/
	t_list[0] = get_smallest(list, size) - 1;
	for (i = 0; i < size; i++)
		t_list[i + 1] = list[i];

	/*Insertion sort*/
	for (i = 2; i <= size; i++) {
#if PRINT_STEPS
		print_int_array(t_list, size);
#endif
		t = t_list[i]; (*num_exch)++;
		j = i - 1;
		while ((*num_cmpr)++, t < t_list[j]) { /*While the current is greater than prev*/
			t_list[j + 1] = t_list[j]; (*num_exch)++; /*Push the prvious to current*/
			j--; /*go back*/
		}
		t_list[j + 1] = t; (*num_exch)++; /*push t to the empty spot*/
	}

	for (i = 0; i < size; i++)
		list[i] = t_list[i + 1];
}

/*Picks biggest element and switches with the top*/
void selection_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, j, k, temp;
	printf("<< Performing Selection Sort >>\n");

	for (i = size - 1; i >= 1; i--) {
#if PRINT_STEPS
		print_int_array(list, size);
#endif
		k = 0;
		for (j = 1; j <= i; j++) {
			if ((*num_cmpr)++, list[j] > list[k]) {
				k = j;
			}
		}
		switch_int_array(list, i, k); (*num_exch)++; /*perform switch*/
	}
}

/*Recursive algorithm - splits the list into two parts, sort the parts and
combine together in order*/
void merge_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	if (size > 1) {
		/*split the array into two parts - if the original list is odd, the back list will
		have 1 more element*/
		int i, j, k, front[size / 2], back[size / 2 + size % 2];

		for (i = 0; i < size / 2; i++) {
			/*import the front*/
			front[i] = list[i];
			/*import the back*/
			back[i] = list[i + size / 2];
		}
		if (size % 2 == 1) back[size / 2] = list[size - 1];

#if PRINT_STEPS
		printf("SPLITTING:\n");
		printf("> size of child front: %d --->  ", (int) (sizeof(front) / sizeof(int)));
		print_int_array(front, size / 2);
		printf("> size of child back: %d --->  ", (int) (sizeof(back) / sizeof(int)));
		print_int_array(back, size / 2 + size % 2);
#endif

		/*call the function on the parts recursively - will sort the list*/
		merge_sort(front, size / 2, num_cmpr, num_exch);
		merge_sort(back, size / 2 + size % 2, num_cmpr, num_exch);

		/*merge the parts together*/
		j = 0;	/*points at the first element of the front list*/
		k = 0;	/*points at the first element of the back list*/

#if PRINT_STEPS
		printf("MERGING:\n");
		printf("> size of this list: %d\n", size);
		printf("> size of front: %d --> ", size / 2);
		print_int_array(front, size / 2);
		printf("> size of back: %d --> ", size / 2);
		print_int_array(back, size / 2 + size % 2);
#endif

		/*Merging procedure*/
		for (i = 0; i < size; i++) {
#if PRINT_STEPS
			if (j < size / 2 && k < size / 2 + size % 2) {
				printf(">> Comparing %d and %d", front[j], back[k]);
			}
#endif

			/*If both lists have elements*/
			if (j < size / 2 && k < size / 2 + size % 2) {
				if ((*num_cmpr)++, front[j] < back[k]) {
					list[i] = front[j];
					j++;
				} else {
					list[i] = back[k];
					k++;
				}
			}
			/*Else, if the back is empty, pour the front*/
			else if (j < size / 2) {
				list[i] = front[j];
				j++;
			}
			/*Else, pour the back*/
			else {
				list[i] = back[k];
				k++;
			}

#if PRINT_STEPS
			printf("\t> pushing %d\n", list[i]);
#endif
			(*num_exch)++;
		}

#if PRINT_STEPS
		printf(">>>> Formed list: ");
		print_int_array(list, size);
#endif
	}
}


/*Performs a heap sort on the list. There are two phases: creating the heap
and popping elements from a list. Does need to allocate memory.*/
void heap_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, *heap;

	heap = makeheap(list, size, num_cmpr, num_exch); /*Make the heap*/
	for (i = 0; i < size; i++) {
		list[size - i - 1] = heap[0]; /*Get the top element of the heap*/
		heap[0] = heap[size - i - 1]; /*Push the bottom element to the top of the heap*/

#if PRINT_STEPS
		printf("Performing Down Sift - Before --> ");
		print_int_array_s(heap, size - i - 1);
#endif
		heapsift_down(heap, size - i - 1, 0, num_cmpr, num_exch); /*Reorder the heap*/

#if PRINT_STEPS
		printf(" After --> ");
		print_int_array_s(heap, size - i - 1);
		printf("\n");
#endif
	}

	free(heap);
}

/*Pick the element in the middle of the list. Push the lesser element to left of the
middle element and push the greater elements to the right. Recurse with the left and right
partitions*/
void quick_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	quick_sort_aux(list, 0, size - 1, num_cmpr, num_exch);
}

/*Does not do anything*/
void no_sort (int list[], int size, int *num_cmpr, int *num_exch) {
	printf("<< No Sort Performed >>\n");
}


/*---------------Utility Functions---------------*/

/*Prints the array of ints*/
void print_int_array (int list[], int size) {
	print_int_array_s(list, size);
	printf("\n");
}

/*Prints the array of ints (w/o newline)*/
void print_int_array_s (int list[], int size) {
	int *list_p = list;
	while ((list_p - list) < size) {
		printf("%d ", *list_p);
		list_p++;
	}
}

/*Returns the smallest element*/
int get_smallest (int list[], int size) {
	int smallest, index;
	smallest = list[0];

	for (index = 0; index < size; index++) {
		if (list[index] < smallest) {
			smallest = list[index];
		}
	}

	return smallest;
}

/*Performs a switch on the integer array list on the index i and j*/
void switch_int_array (int list[], int i, int j) {
	int temp;

	temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

/*Sorts the heap based on the current index position. Here,
the child node moves up the heap based on if the child is greater than
it's parent. The function calls itself until it reaches a state where
it's parent is greater than itself.
The position of the parent node is defined as: floor{(i-1)/2}*/
void heapsift_up (int heap[], int size, int index, int *num_cmpr, int *num_exch) {
	if ((*num_cmpr)++, (index - 1) / 2 >= 0 && heap[index] > heap[(index - 1) / 2]) {
		switch_int_array(heap, index, (index - 1) / 2); (*num_exch)++; /*Perform switch*/
		heapsift_up(heap, size, (index - 1) / 2, num_cmpr, num_exch); /*Recursive call*/
	}
}

/*Opposite of heapsift_up the current node at index gets moved down
based on the condition that it is less than one of it's child. Here,
the current node switches with the child of the greater value. The
function calls itself until it reaches a state where the current node is
greater than both of it's children.
The position of the left child is defined as: 2i + 1
The position of the right child is defined as: 2i + 2*/
void heapsift_down (int heap[], int size, int index, int *num_cmpr, int *num_exch) {
	/*If there exist left child, then a switch is possible (at least with the left
	child)*/
	if (index * 2 + 1 < size) {
		/*If there is a right child and that child is greater than the current and
		it's sibling, switch*/
		if (index * 2 + 2 < size &&
		        heap[index * 2 + 2] > heap[index * 2 + 1] &&
		        heap[index * 2 + 2] > heap[index]) {
			(*num_cmpr)++;

			/*Switch the right child and current*/
			switch_int_array(heap, index, index * 2 + 2);

			/*Recursive call*/
			heapsift_down(heap, size, index * 2 + 2, num_cmpr, num_exch);
		}
		/*If the left child is greater than the parent, do a switch*/
		else if ((*num_cmpr)++, heap[index * 2 + 1] > heap[index]) {

			/*Switch the left child and current*/
			switch_int_array(heap, index, index * 2 + 1);

			/*Recursive call*/
			heapsift_down(heap, size, index * 2 + 1, num_cmpr, num_exch);
		}
	}
}

/*Allocates and create a heap based on the elements of the given array
list. The function will insert each element one-by-one and then call
heapsift_up on the newly added element.
A heap object is defined as a array of integers where the left child is
defined at the position 2i + 1 and the right child at 2i + 2. The parent node
can be found by taking the floor of (i-1)/2.
Therefore, given a node at position i:
left child -> 2i + 1
right child -> 2i + 2
parent -> floor{(i-1)/2}*/
int* makeheap (int list[], int size, int *num_cmpr, int *num_exch) {
	int i, *heap;
	heap = malloc(size * sizeof(int));

#if PRINT_STEPS
	printf ("<< Making Heap >>\n");
#endif

	/*Forming the heap*/
	for (i = 0; i < size; i++) {
		heap[i] = list[i];

#if PRINT_STEPS
		printf("Performing Up Sift - Before --> ");
		print_int_array_s(heap, i + 1);
#endif

		heapsift_up(heap, size, i, num_cmpr, num_exch);

#if PRINT_STEPS
		printf(" After --> ");
		print_int_array_s(heap, i + 1);
		printf("\n");
#endif
	}

#if PRINT_STEPS
	printf ("Heap: ");
	print_int_array(heap, size);
#endif

	return heap;
}

/*Performs a quicksort on the specified int array. Note that the start and end values are inclusive.
The size of the list is determined by the expression end - start + 1*/
void quick_sort_aux (int list[], int start, int end, int *num_cmpr, int *num_exch) {
	int i, j, m, temp, size;
	i = start;
	size = end - start + 1;
	m = (start + end + 1)/2;	/*Get the middle index*/

#if defined PRINT_STEPS
	printf("Performing Mergesort: Median = %d --> ", list[m]);
	print_int_array(&list[start], size);
#endif

	/*If the current element is greater than the middle element and it exists on the left side,
		push the elements to the right of it up to the middle element to the left and place the current
		element at the middle spot. Update m index but do not update current index i. (Vice versa if
		the element is less than the middle but to the right of the middle*/
	while (i <= end) {
		j = i; /*Index of the current element*/
		if ((*num_cmpr)++, i < m && list[i] > list[m]) {
			(*num_exch)++; /*Will count movement as 1 exchange*/
			while (j < m) { /*Push the current element to the middle's place*/
				switch_int_array(list, j, j + 1);
				j++;
			}
			m--; /*Move the middle index accordingly*/
		} else if ((*num_cmpr)++, i > m && list[i] < list[m]) {
			(*num_exch)++; /*Will count movement as 1 exchange*/
			while (j > m) {
				switch_int_array(list, j, j - 1);
				j--;
			}
			m++;
		} else {
			i++;
		}
	}

#if defined PRINT_STEPS
	printf("Result --> ");
	print_int_array(&list[start], size);
#endif

	/*Recursive calls on the left and right side of the median*/
	if (m - 1 > start) quick_sort_aux(list, start, m - 1, num_cmpr, num_exch);
	if (m + 1 < end) quick_sort_aux(list, m + 1, end, num_cmpr, num_exch);
}












