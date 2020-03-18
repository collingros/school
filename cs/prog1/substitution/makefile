# collin gros
# 03/12/2020

# makefile for compiling decrypt.c

CC=gcc

OBJ_FILES=$(patsubst %.c, %.o, $(wildcard *.c))

decrypt: $(OBJ_FILES)
	$(CC) -o $@ $^

clean:
	rm -rf decrypt *.o

