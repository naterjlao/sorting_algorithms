CC=gcc

driver.x: driver.c quicksort.o
	$(CC) driver.c quicksort.o -o driver.x

quicksort.o: quicksort.c quicksort.h
	$(CC) -c quicksort.c

clean:
	rm *.x *.out *.o
