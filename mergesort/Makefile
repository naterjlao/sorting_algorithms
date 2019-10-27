CC=gcc

driver.x: driver.c mergesort.o
	$(CC) driver.c mergesort.o -o driver.x

mergesort.o: mergesort.c mergesort.h
	$(CC) -c mergesort.c

clean:
	rm *.x *.out *.o
