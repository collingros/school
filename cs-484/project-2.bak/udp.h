#ifndef __UDP_H_INCLUDED__
#define __UDP_H_INCLUDED__

/*	struct sockaddr_in	*/
#include <netinet/in.h>

/*	constants	*/
/*	1KB max msg length	*/
#define MAX_MSG_LEN	1024


/*
init_udp_server()

takes the server sockaddr_in and client sockaddr_in structs, a var
to hold the socket file descriptor, and reads from constants set in
	udp.h
to initialize these values.

returns non-zero on error.
*/
int init_udp_server(struct sockaddr_in *server_addr,
					struct sockaddr_in *client_addr,
					int *socketfd,
					int port);


/*
init_udp_client()

takes the client sockaddr_in struct, a var
to hold the socket file descriptor, and reads from constants set in
	udp.h
to initialize these values.

returns non-zero on error.
*/
int init_udp_client(struct sockaddr_in *server_addr, int *socketfd,
					int port);


/*
udp_server_listen()

note: THIS FUNCTION WILL BLOCK AS IT CALLS recvfrom() WITH MSG_WAITALL!

listens for a transmission to our socket and puts the message in
the given buffer.

returns non-zero on error:

*/
int udp_server_listen(char *buf, int *socketfd,
						struct sockaddr_in *client_addr);

/*
udp_server_transmit()

note: THIS FUNCTION WILL BLOCK AS IT CALLS recvfrom() WITH MSG_WAITALL!

transmits a given message to the server.

returns non-zero on error:
*/
int udp_client_transmit(char *buf, int *socketfd,
						struct sockaddr_in *server_addr);


#endif

