# collin gros
# 03/12/2020

# makefile for compiling decrypt.c

all: decrypt_helper.o decrypt.o hash.o
	gcc decrypt_helper.o decrypt.o hash.o -o decrypt

decrypt_helper.o: decrypt_helper.c decrypt_helper.h
	gcc -c decrypt_helper.c

decrypt.o: decrypt.c
	gcc -c decrypt.c

hash.o: hash.c
	gcc -c hash.c


clean:
	rm -f *.o
	rm -f decrypt
