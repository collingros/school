# collin gros
# 09-29-2020
# cs484
#
# makefile for project 1
#
# usage: make all
# (creates ./run executable)
#
# usage: make clean
# (removes executables & object files)
#
all: main.o
	g++ main.o -o run

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf run *.o
