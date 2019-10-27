all: test1.x

#Executables
test1.x: test1.c sorting_algorithms.o
	gcc -g test1.c sorting_algorithms.o -o test1.x

#Object Files
sorting_algorithms.o: sorting_algorithms.c
	gcc -c sorting_algorithms.c

clean:
	rm -rf *.x *.x* a.out *.o
