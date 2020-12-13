/*
collin gros
12-12-2020
cs484
project-2


this file contains all of the shared functions between client/server
in my udp-chat implementation.

client.c and server.c use this file for creating sockets, binding,
initializing arguments, initializing network values, and listening
to incoming traffic.

if the long function calls are hard to read, change your tabsize to 4
*/

#ifndef __UDP_CHAT_H_INCLUDED__
#define __UDP_CHAT_H_INCLUDED__

/*

#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
*/
#include <arpa/inet.h>
#include <pthread.h>


/*	CONSTANTS	*/
#define MAX_MSG_LEN	1024





/*	struct to contain all information retrieved from
	command-line arguments	*/
struct arg_info {
	/*	if these are arguments for the server program
		(1=server,0=client)	*/
	int is_server;

	/*	ip address of server (not needed if is_server=1)	*/
	char *serv_ip;
	/*	port number of server	*/
	int port;
	/*	username	*/
	char username[20];
};

/*	contains all net_info related to sockaddr_in structs	*/
struct net_info {
	/*	if these are net info for the server program
		(1=server,0=client)	*/
	int is_server;

	/*	socket file descriptor	*/
	int socketfd;
	/*	server sockaddr_in struct	*/
	struct sockaddr_in serv_addr;
	/*	client sockaddr_in struct (not needed if is_server=0)	*/
	struct sockaddr_in clin_addr;
	/*	length of above	*/
	int serv_addr_len;
	/*	(not needed if is_server=0)	*/
	int clin_addr_len;

	/*	so we can reference the arguments in this struct	*/
	struct arg_info *parsed_args;
};



/*	global pointers for use with cleanup()
	***	THESE SHOULD POINT TO THHE arg_info AND net_info
		STRUCTS IN MAIN	***	*/
struct arg_info *parsed_args_p;
struct net_info *netwrk_info_p;

pthread_t listener;


/*
init_args()

initializes all members of the parsed_args struct. used for
reading command-line arguments and storing them into that struct.

returns nonzero on error:
	1:incorrect usage
	2:port wasn't an integer
*/
int init_args(struct arg_info *parsed_args, int argc, char **argv);


/*
init_netw()

this function initializes all members of the netwrk_info struct. this
is used later for sendto() and recvfrom() calls.
it also creates a socket and binds it with the given port number in
	parsed_args

returns nonzero on error:
	1:socket creation failed
	2:ip argument couldn't be converted to binary
	3:bind() failed to bind the socket and port
*/
int init_netw(struct net_info *netwrk_info, struct arg_info *parsed_args);


/*
listen_task()

this is the function that is run from main() forking into a sending
while loop. this prints received messages to stdout.
*/
void *listen_task(void *arg);


/*
sighandler()

responsible for halting the program and immediately calling cleanup()
right before exiting.
*/
void sighandler(int);


/*
cleanup()

responsible for destroying malloc'd structs
*/
void cleanup(struct arg_info *parsed_args, struct net_info *netwrk_info,
				pthread_t listen_task_pid);


/*
send_msg()


sends a given message to the destination address definted in
netwrk_info, whether we are the client or the server.
*/
void send_msg(struct net_info *netwrk_info, char *msg);


#endif
