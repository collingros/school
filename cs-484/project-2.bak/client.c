/*
collin gros
12-12-2020
cs484
project-3


this code is part of a "Chat application" that can be used to talk to
a server.

this is the client-side code of a UDP connection in C using sockets.
it implements the stop-and-wait protocol to create reliability.
*/


/*	custom udp functions	*/
#include "udp.h"

/*	struct sockaddr_in	*/
#include <netinet/in.h>

/*	error handling	*/
#include <errno.h>
#include <string.h>
#include <stdio.h>

/*	atoi	*/
#include <stdlib.h>


/*
main()

takes the port number and acts as the client-side of a UDP connection

returns nonzero for error:
	1:	not enough arguments
	2:	couldn't convert given port to an integer
	3:	initializing udp values failed - see
			./udp.h
		for details on the given error
*/
int main(int argc, char **argv)
{
	int socketfd, port;
	struct sockaddr_in server_addr, client_addr;
	char buf[MAX_MSG_LEN];

	/*	confirm we have the correct number of command-line args	*/
	if (argc != 2) {
		fprintf(stderr, "ERROR: not enough arguments\n"
						"USAGE: ./server [port to listen on]\n");
		return 1;
	}

	/*	get the port from the given argument. abort if error.	*/
	if (port = atoi(argv[1]) == 0) {
		fprintf(stderr, "ERROR: could not convert '%s' to an integer!\n",
				argv[1]);
		return 2;
	}


	/*	set our initial values required to listen on the socket,
		parameters for these are set in
			./udp.h	*/
	init_udp_client(&server_addr, &socketfd, port);

	/*	send msg to server	*/
	udp_client_transmit("penis\0", &socketfd, &server_addr);
	/*	send ack	*/


	return 0;
}

