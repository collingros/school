collin gros
12-12-2020
cs484
project-2


this directory contains my code for running a UDP server and client
through the use of sockets. various sources i referenced while making this
can be seen in the ./sources directory.

the ./combined directory contains an alternative version of the code,
which combines the server and client into one executable. this was not
part of the original task, but it's kinda cool so HA.

to compile:
	make
to run as the server:
	./server [port number to listen on]
to run as the client:
	./client [ipv4 address] [port number]
to exit the program while it is running:
	CTRL + C
to clean up:
	make clean

EXAMPLE:
	(on host A):
		./server PORT_A
		[enter username]
		chat!
	(on host B):
		./client IP_A PORT_A
		[enter username]
		chat!


