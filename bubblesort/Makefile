CC=gcc

all: driver.x driver_str.x

driver.x: driver.c bubblesort.o
	$(CC) driver.c bubblesort.o -o driver.x

driver_str.x: driver_str.c bubblesort.o
	$(CC) driver_str.c bubblesort.o -o driver_str.x

bubblesort.o: bubblesort.c bubblesort.h
	$(CC) -c bubblesort.c

clean:
	rm *.x *.out *.o
