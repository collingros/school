/*
collin gros
12-12-2020
cs484
project-3

udp.c: contains implementations for functions used in server.c
and client.c
*/

#include "udp.h"
/*	struct sockaddr_in	*/
#include <netinet/in.h>
#include <stdio.h>
/*	memset	*/
#include <string.h>



/*
init_udp_server()

takes the server sockaddr_in and client sockaddr_in structs, a var
to hold the socket file descriptor, and reads from constants set in
	udp.h
to initialize these values. binds the socket to the server address.

returns non-zero on error:
	1:	failed to initialize socketfd.
	2:	failed to bind the socket with the sockaddr_in for the server

*/
int init_udp_server(struct sockaddr_in *server_addr,
					struct sockaddr_in *client_addr,
					int *socketfd,
					int port)
{
	/*	initialize the socket, and abort if it fails	*/
	*socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd < 0) {
		perror("ERROR: [udp.c] failed to get socketfd from socket()");
		return 1;
	}

	/*	intialize our given socketaddr_ins to 0 and initialize
		servers' address values	*/
	/*	handle server_addr	*/
	memset(server_addr, 0, sizeof(struct sockaddr_in));
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = INADDR_ANY;
	server_addr->sin_port = htons(port);

	/*	handle client addr	*/
	memset(client_addr, 0, sizeof(struct sockaddr_in));

	/*	bind socket and server_addr
		and abort if it fails	*/
	int ret;
	/*	must cast our sockaddr_in to const struct sockaddr *	*/
	ret = bind(*socketfd, (const struct sockaddr *) server_addr,
					sizeof(struct sockaddr_in));
	/*	abort if bind() failed	*/
	if (ret < 0) {
		perror("ERROR: [udp.c] failed to bind socket and server_addr");
		fprintf(stderr, "ERROR: [udp.c] bind returned: %d\n", ret);
		return 2;
	}


	/*	successfully initialized everything we were given	*/
	return 0;
}


/*
udp_server_listen()

note: THIS FUNCTION WILL BLOCK AS IT CALLS recvfrom() WITH MSG_WAITALL!

listens for a transmission to our socket and puts the message in
the given buffer.

returns non-zero on error:

*/
int udp_server_listen(char *buf, int *socketfd,
						struct sockaddr_in *client_addr)
{
	/*	FIXME currently blocks but we want it to quit after timeout is
		reached.	*/
	int *client_addr_len = (int *) sizeof(struct sockaddr_in);
	printf("listening..\n");
	int len = recvfrom(*socketfd, buf, MAX_MSG_LEN, MSG_WAITALL,
						(struct sockaddr *) client_addr,
						client_addr_len);
	/*	terminate the buffer at the end of received string	*/
	buf[len] = '\0';

	printf("received!\n");

	return 0;
}


/*
udp_server_transmit()

note: THIS FUNCTION WILL BLOCK AS IT CALLS recvfrom() WITH MSG_WAITALL!

transmits a given message to the server.

returns non-zero on error:
*/
int udp_client_transmit(char *buf, int *socketfd,
						struct sockaddr_in *server_addr)
{
	/*	FIXME implement stop-and-wait	*/
	int server_addr_len = sizeof(struct sockaddr_in);
	int len = sendto(*socketfd, buf, strlen(buf), MSG_CONFIRM,
						(struct sockaddr *) server_addr,
						server_addr_len);

	printf("sent!\n");

	return 0;
}

/*
init_udp_client()

takes the server sockaddr_in struct, a var
to hold the socket file descriptor, and reads from constants set in
	udp.h
to initialize these values.

returns non-zero on error.
*/
int init_udp_client(struct sockaddr_in *server_addr, int *socketfd,
					int port)
{
	/*	initialize the socket, and abort if it fails	*/
	*socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd < 0) {
		perror("ERROR: [udp.c] failed to get socketfd from socket()");
		return 1;
	}

	/*	intialize our given socketaddr_in to 0 and initialize
		servers' address values	*/
	/*	handle server_addr	*/
	memset(server_addr, 0, sizeof(struct sockaddr_in));
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = INADDR_ANY;
	server_addr->sin_port = htons(port);

	return 0;
}
