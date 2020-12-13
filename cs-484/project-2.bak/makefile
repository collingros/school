# collin gros
# 12-12-2020
# cs484
# project-3
#
# makefile for project-3. compiles both server.c and client.c

all: udp.o server.o client.o
	gcc -g server.o udp.o -o server
	gcc -g client.o udp.o -o client

server.o: server.c udp.o
	gcc -g -c server.c
client.o: client.c udp.o
	gcc -g -c client.c
udp.o: udp.c udp.h
	gcc -g -c udp.c

clean:
	rm -rf *.o server client
