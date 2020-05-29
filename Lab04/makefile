CC = gcc

all: calc.o vectorClass.o main.o
	$(CC) calc.o vectorClass.o main.o -o p4

calc.o: calc.c calc.h vectorClass.h
	$(CC) calc.c -c -o calc.o

vectorClass.o: vectorClass.c vectorClass.h
	$(CC) vectorClass.c -c -o vectorClass.o

main.o: main.c calc.h
	$(CC) main.c -c -o main.o




