# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = src/main.c src/add_route.c
OBJ = main.o add_route.o
EXEC = add_route

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

