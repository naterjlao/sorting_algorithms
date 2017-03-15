#include <stdio.h>
#define SELECTIONSORT
#define PRINT_STEPS 1

/*---------------Sorting Prototypes---------------*/
void bubblesort (int[], int, int *, int *);
void bubblesort_mod (int[], int, int *, int *);
void insertionsort (int[], int, int *, int *);
void selectionsort (int[], int, int *, int *);
void mergesort (int[], int, int *, int *);
void heapsort (int[], int, int *, int *);
void quicksort (int[], int, int *, int *);
void nosort (int[], int, int *, int *);


/*---------------Utility Prototypes---------------*/
void print_int_array (int[], int);
int get_smallest (int[], int);
void switch_int_array (int[], int, int);
void heapsift_up (int[], int, int, int *, int *);
void heapsift_down (int[], int, int, int *, int *);
int* makeheap (int[], int, int *, int *);

/*---------------MAIN DRIVER---------------*/
int main(void) {
	int list[] = {4, 5, 6, 1, 9, 10, 2, 3, 8, 7};
	int size = sizeof(list) / sizeof(int);
	int num_cmpr = 0;
	int num_exch = 0;
	void (*sort) (int[], int, int *, int *);

#if defined BUBBLESORT
	sort = bubblesort;
#elif defined BUBBLESORT_MOD
	sort = bubblesort_mod;
#elif defined INSERTIONSORT
	sort = insertionsort;
#elif defined SELECTIONSORT
	sort = selectionsort;
#elif defined MERGESORT
	sort = mergesort;
#elif defined HEAPSORT
	sort = heapsort;
#elif defined QUICKSORT
	sort = quicksort;
#else
	sort = nosort;
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

/*---------------Sorting Functions---------------*/

/*Largest elements 'float' (switches) to the top*/
void bubblesort (int list[], int size, int *num_cmpr, int *num_exch) {
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
void bubblesort_mod (int list[], int size, int *num_cmpr, int *num_exch) {
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
void insertionsort (int list[], int size, int *num_cmpr, int *num_exch) {
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
void selectionsort (int list[], int size, int *num_cmpr, int *num_exch) {
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
void mergesort (int list[], int size, int *num_cmpr, int *num_exch) {
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
		mergesort(front, size / 2, num_cmpr, num_exch);
		mergesort(back, size / 2 + size % 2, num_cmpr, num_exch);

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
void heapsort (int list[], int size, int *num_cmpr, int *num_exch) {
	makeheap(list, size, num_cmpr, num_exch);
}

void quicksort (int list[], int size, int *num_cmpr, int *num_exch) {
	/*TODO*/
}

/*Does not do anything*/
void nosort (int list[], int size, int *num_cmpr, int *num_exch) {
	printf("<< No Sort Performed >>\n");
}


/*---------------Utility Functions---------------*/

/*Prints the array of ints*/
void print_int_array (int list[], int size) {
	int *list_p = list;
	while ((list_p - list) < size) {
		printf("%d ", *list_p);
		list_p++;
	}
	printf("\n");
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
		if () {
			/*Switch the right child and current*/
			/*Recursive call*/
		} 
		/*If the left child is less than current, do a switch*/
		else if () {
			/*Switch the left child and current*/
			/*Recursive call*/
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
	int i, heap[size];

	for (i = 0; i < size; i++) {
		heap[i] = list[i];
		heapsift_up(heap, size, i, num_cmpr, num_exch);
	}

#if PRINT_STEPS
	printf ("Heap: ");
	print_int_array(heap, size);
#endif

	return NULL;
}












