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

a summary can be found near functions in comments in 'udp-chat.h'
if the long function calls are hard to read, change your tabsize to 4
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "udp-chat.h"



/*
listen_task()

this is the function that is run from main() forking into a sending
while loop. this prints received messages to stdout.
*/
void *listen_task(void *arg)
{
	struct net_info *netwrk_info = (struct net_info *) arg;

	/*	we listen to different addresses depending if we are the client
		or server.	*/
	if (netwrk_info->is_server) {
		while (1) {
			char buf[MAX_MSG_LEN] = "";
			recvfrom(netwrk_info->socketfd, buf, MAX_MSG_LEN, 0,
						(struct sockaddr *) &(netwrk_info->clin_addr),
						&(netwrk_info->clin_addr_len));

			/*	saving this here in case i want to see ip/port instead
			printf("\n[listen_task] %s:%d says: %s\n",
					inet_ntoa(netwrk_info->clin_addr.sin_addr),
					ntohs(netwrk_info->clin_addr.sin_port), buf);
			*/

			/*	get the source username of the message we just
				received and print their message	*/
			char name[20];
			printf("\n%s\n", buf);

			/*	re-print our username so it looks pretty	*/
			printf("$%s:", netwrk_info->parsed_args->username);
		}
	}
	/*	we are the client - send messages to the server	*/
	else {
		while (1) {
			char buf[MAX_MSG_LEN] = "";
			recvfrom(netwrk_info->socketfd, buf, MAX_MSG_LEN, 0,
						(struct sockaddr *) &(netwrk_info->serv_addr),
						&(netwrk_info->serv_addr_len));

			/*	saving this here in case i want to see ip/port instead
			printf("\n[listen_task] %s:%d says: %s\n",
					inet_ntoa(netwrk_info->clin_addr.sin_addr),
					ntohs(netwrk_info->clin_addr.sin_port), buf);
			*/

			/*	get the source username of the message we just
				received and print their message	*/
			char name[20];
			printf("\n%s\n", buf);

			/*	re-print our username so it looks pretty	*/
			printf("$%s:", netwrk_info->parsed_args->username);
		}
	}

	printf("[listen_task] done\n");
}


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
int init_netw(struct net_info *netwrk_info, struct arg_info *parsed_args)
{
	/*	create our UDP socket	*/
	netwrk_info->socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (netwrk_info->socketfd < 0) {
		fprintf(stderr, "[init_netw] ERROR: could not create socket!\n");
		return 1;
	}

	/*	clear netwrk_info->serv_addr to be empty	*/
	memset(&(netwrk_info->serv_addr), 0, sizeof(netwrk_info->serv_addr));
	/*	init serv_addr_len to be the length of serv_addr	*/
	netwrk_info->serv_addr_len = sizeof(netwrk_info->serv_addr);

	/*	if we are the server we have to clear and init
		clin_addr and clin_addr_len as well	*/
	if (netwrk_info->is_server) {
		/*	also clear netwrk_info->clin_addr if we are the server	*/
		memset(&(netwrk_info->clin_addr), 0,
				sizeof(netwrk_info->clin_addr));
		/*	init serv_addr_len to be the length of serv_addr	*/
		netwrk_info->clin_addr_len = sizeof(netwrk_info->clin_addr);
	}

	/*	serv_addr member initialization	*/
	netwrk_info->serv_addr.sin_family = AF_INET;
	netwrk_info->serv_addr.sin_port = htons(parsed_args->port);
	/*	if we are the server we have to set
		serv_addr.sin_addr.s_addr as well	*/
	if (netwrk_info->is_server) {
		netwrk_info->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}


	/*	if we are the client we have to convert the ip to binary
		and save it to the serv_addr struct as well (the server
		doesn't have to do this because it is its own ip)	*/
	if (!netwrk_info->is_server) {
		/*	convert from string ip to binary in serv_addr	*/
		int ret = inet_aton(parsed_args->serv_ip,
							&(netwrk_info->serv_addr.sin_addr));
		/*	abort if that failed	*/
		if (ret == 0) {
			fprintf(stderr, "[init_netw] ERROR: could not convert "
							"ip '%s' to binary!\n",
					parsed_args->serv_ip);
			return 2;
		}
	}


	/*	server must perform a bind to the port/socket	*/
	if (netwrk_info->is_server) {
		int ret = bind(netwrk_info->socketfd,
						(struct sockaddr *) &(netwrk_info->serv_addr),
						netwrk_info->serv_addr_len);
		/*	abort if that failed	*/
		if (ret < 0) {
			fprintf(stderr, "[init_netw] ERROR: bind failed!\n");
			return 3;
		}
	}

	return 0;
}


/*
init_args()

initializes all members of the parsed_args struct. used for
reading command-line arguments and storing them into that struct.

returns nonzero on error:
	1:incorrect usage
	2:port wasn't an integer
*/
int init_args(struct arg_info *parsed_args, int argc, char **argv)
{
	/*	we check for different arguments for different is_server values.
		e.g., server doesn't need to know an 'ip'	*/
	/*	parse server args	*/
	if (parsed_args->is_server) {
		/*	confirm we have the correct number of command-line args	*/
		if (argc != 2) {
			fprintf(stderr, "[init_args] ERROR: not enough arguments\n"
							"[init_args]\tUSAGE: ./server "
							"[port to listen on]\n");
			return 1;
		}

		/*	set port	*/
		parsed_args->port = atoi(argv[1]);
	}
	/*	parse client args	*/
	else {
		/*	confirm we have the correct number of command-line args	*/
		if (argc != 3) {
			fprintf(stderr, "[init_args] ERROR: not enough arguments\n"
							"[init_args]\tUSAGE: ./client [ip] [port]\n");
			return 1;
		}

		/*	set port	*/
		parsed_args->port = atoi(argv[2]);
	}

	/*	abort if port wasn't an integer	*/
	if (parsed_args->port == 0) {
		fprintf(stderr, "[init_args] ERROR: could not "
						"convert '%s' to an integer!\n",
				parsed_args->port);
		return 2;
	}

	/*	ask user for name to use and set it	*/
	printf("Enter your username (up to 20 characters): ");
	/*	\n is important so fgets doesn't eat it up	*/
	fgets(parsed_args->username, 20, stdin);
	/*	strip newline	*/
	parsed_args->username[strlen(parsed_args->username)-1] = '\0';
	printf("\nYour username has been set to: %s\n", parsed_args->username);


	/*	if we are the client we want to save the ip from the args as
		well	*/
	if (!parsed_args->is_server) {
		/*	get the ip from the given arguments.	*/
		parsed_args->serv_ip = argv[1];
	}


	return 0;
}


/*
sighandler()

responsible for halting the program and immediately calling cleanup()
right before exiting.
*/
void sighandler(int signum)
{
	printf("\n[sighandler] got signal! cleaning up and quitting...\n");
	cleanup(parsed_args_p, netwrk_info_p, listener);
	printf("[sighandler] done\n");
	printf("[sighandler] exiting...\n");
	exit(0);
}


/*
cleanup()

responsible for destroying malloc'd structs
*/
void cleanup(struct arg_info *parsed_args, struct net_info *netwrk_info,
				pthread_t listener)
{
	/*	signal listen_task() to stop and then wait for it to
		quit	*/
	/*	if the listener already started we want to kill it	*/
	if (listener != (pid_t) 0) {
		printf("[cleanup] killing listen_task(), waiting...\n");
		kill(listener, 9);
		printf("[cleanup] listen_task() killed\n");
	}
	else {
		printf("[cleanup] listen_task() not started so not killed\n");
	}

	/*	free all manually allocated memory	*/
	printf("[cleanup] freeing structs...\n");
	free(parsed_args);
	free(netwrk_info);
	printf("[cleanup] done\n");
}



/*
send_msg()


sends a given message to the destination address definted in
netwrk_info, whether we are the client or the server.
*/
void send_msg(struct net_info *netwrk_info, char *msg)
{
	/*	use client address as dst if we are the server	*/
	if (netwrk_info->is_server) {
		sendto(netwrk_info->socketfd, msg, strlen(msg), 0,
				(struct sockaddr *) &(netwrk_info->clin_addr),
				netwrk_info->clin_addr_len);
	}
	/*	use server address as dst if we are the client	*/
	else {
		sendto(netwrk_info->socketfd, msg, strlen(msg), 0,
				(struct sockaddr *) &(netwrk_info->serv_addr),
				netwrk_info->serv_addr_len);
	}
}



