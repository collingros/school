# collin gros
# 03/12/2020

# makefile for compiling decrypt.c

CC=g++
SRC_DIR=./src
OBJ_DIR=./obj

SRC_FILES=$(wildcard $(SRC_DIR)/*.c))

$(info $(SRC_FILES))
OBJ_FILES=$($(SRC_FILES):.c=.o)

decrypt: $(OBJ_FILES)
	$(CC) -o $@ $^

clean:
	rm -rf $(OBJ_DIR) decrypt

