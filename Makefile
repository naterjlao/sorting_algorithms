sorting_algorithms.x: sorting_algorithms.c
	gcc -g sorting_algorithms.c -o sorting_algorithms.x

clean:
	rm -rf *.x *.x* a.out
