# collin gros
# 03/12/2020

# makefile for compiling decrypt.c

CC=gcc
CFLAGS=-Wall

OBJ_FILES=$(patsubst %.c, %.o, $(wildcard *.c))

decrypt: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf decrypt *.o

