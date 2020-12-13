# collin gros
# 12-12-2020
# cs484
# project-3
#
# makefile for project-3. compiles both server.c and client.c

all: server client

server: server.c udp-chat.o
	gcc -lpthread server.c udp-chat.o -o server
client: client.c udp-chat.o
	gcc -lpthread client.c udp-chat.o -o client
udp-chat.o: udp-chat.c udp-chat.h
	gcc -c udp-chat.c

clean:
	rm -rf *.o server client
