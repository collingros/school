# collin gros
# 11-03-2020
# cs474
# project2
#
# makefile for project 2
# compile with:
# 		make
# clean with:
#		clean


all: circ.o
	gcc main.c circ.o -lpthread -lrt -o run
circ.o:
	gcc -c circ.c

clean:
	rm -f run
	rm -f *.o

