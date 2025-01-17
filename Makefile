all: build run
.PHONY: build run clean

CC=cc
FLAGS=-Wall -Werror -Wextra
OUT=main

build:
	$(CC) $(FLAGS) -c -o ham.o ham/ham.c
	$(CC) $(FLAGS) -o $(OUT) main.c ham.o

run:
	./main

clean:
	rm -f main ham.o
