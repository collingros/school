# collin gros
# 12-12-2020
# cs484
# project-2
#
# makes main.c, which combines client and server into one executable.
#
# compile with:
# 	make
# run with:
# 	./run

cc=gcc

all: run

run: main.c udp-chat.o
	$(cc) -lpthread main.c udp-chat.o -o run
udp-chat.o: udp-chat.c udp-chat.h
	$(cc) -c udp-chat.c

clean:
	rm -rf *.o run
