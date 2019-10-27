#ifndef QUICKSORT_H
#define QUICKSORT_H


int quicksort(void *list, size_t length, size_t size, int (*compare)(void *, void *), int decreasing);

#endif

