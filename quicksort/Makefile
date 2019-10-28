CC=gcc

all: driver.x driver_str.x

driver.x: driver.c quicksort.o
	$(CC) driver.c quicksort.o -o driver.x

driver_str.x: driver_str.c quicksort.o
	$(CC) driver_str.c quicksort.o -o driver_str.x

quicksort.o: quicksort.c quicksort.h
	$(CC) -c quicksort.c

clean:
	rm *.x *.out *.o
