# collin gros
# 11-20-2020
# cs474
# proj3
#
# this is the makefile for project 3. compile with 'make' and clean with
# 'make clean'
#
# run with './run'
#

all: main.o
	gcc main.o -lpthread -o run

main.o: main.c
	gcc -c main.c -lpthread

clean:
	rm -rf run *.o
