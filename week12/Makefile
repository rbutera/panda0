# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall -o3 -std=c99

default: all

all: list.o test.o
	$(CC) $(CFLAGS) -o list list.o test.o

list.o: debugprint.h minunit.h list.h list.c
	$(CC) $(CFLAGS) -o list.o list.c -c

test.o: debugprint.h minunit.h list.h test.c
	$(CC) $(CFLAGS) -o test.o test.c -c
