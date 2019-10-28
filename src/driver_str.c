#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bubblesort.h"
#include "mergesort.h"
#include "quicksort.h"

#define LENGTH 5
#define MAX_STRING_SIZE 40

int strcmp_wrapper(void *a_ptr, void *b_ptr) {
	return strcmp((const char *) a_ptr, (const char *) b_ptr);
}

// NOTE: input is a pointer to the first character of the
// first element of the list
void print_string_array(char *list, size_t length) {
	size_t i = 0;

	while (i < length - 1) {
		printf("%s, ", &list[i*MAX_STRING_SIZE]);
		i++;
	}
	printf("%s\n", &list[i*MAX_STRING_SIZE]);
}

int main() {
	int status;

	char arr[LENGTH][MAX_STRING_SIZE] = {
		"John",
		"Adam",
		"Richard",
		"Marcy",
		"Fiona"
	};

	print_string_array(&arr[0][0],LENGTH);
	bubblesort(arr,LENGTH,MAX_STRING_SIZE,strcmp_wrapper,0);
	print_string_array(&arr[0][0],LENGTH);	
	bubblesort(arr,LENGTH,MAX_STRING_SIZE,strcmp_wrapper,1);
	print_string_array(&arr[0][0],LENGTH);	

	return status;
}
