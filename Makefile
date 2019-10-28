INC=include
SRC=src
BIN=bin
CC=gcc
MV_OBJ=mv *.o $(BIN)

all: $(BIN)/driver.x $(BIN)/driver_str.x

$(BIN)/driver.x: $(SRC)/driver.c $(BIN)/bubblesort.o $(BIN)/mergesort.o $(BIN)/quicksort.o
	$(CC) $(SRC)/driver.c $(BIN)/bubblesort.o $(BIN)/mergesort.o $(BIN)/quicksort.o -o $(BIN)/driver.x -I $(INC)

$(BIN)/driver_str.x: $(SRC)/driver_str.c $(BIN)/bubblesort.o $(BIN)/mergesort.o $(BIN)/quicksort.o
	$(CC) $(SRC)/driver_str.c $(BIN)/bubblesort.o $(BIN)/mergesort.o $(BIN)/quicksort.o -o $(BIN)/driver_str.x -I $(INC)

$(BIN)/bubblesort.o: $(SRC)/bubblesort.c $(INC)/bubblesort.h
	$(CC) -c $(SRC)/bubblesort.c -I $(INC)
	$(MV_OBJ)

$(BIN)/mergesort.o: $(SRC)/mergesort.c $(INC)/mergesort.h
	$(CC) -c $(SRC)/mergesort.c -I $(INC)
	$(MV_OBJ)

$(BIN)/quicksort.o: $(SRC)/quicksort.c $(INC)/quicksort.h
	$(CC) -c $(SRC)/quicksort.c -I $(INC)
	$(MV_OBJ)

clean:
	rm -rvf $(BIN)/*

