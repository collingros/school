# collin gros
# 10-01-2020
# cs474
# project1
#
#
# makefile for project 1
#
# use
#		make
# to output run, then run the program with
#		./run
# to clean up, run
#		make clean


all: run

run: main.o
	gcc main.o -o run

main.o: main.c
	gcc -c main.c


clean:
	rm -rf *.o run
