/*
collin gros
12-12-2020
cs484
project-2

psuedocode for the client program.
*/


/*
listen():
	one thread runs this constantly, to display messages that are recved
	from the server.
	CTRL+C will force this thread to close


transmit():
	one thread runs this constantly, to take user input and send it to
	the server.


init_args():
	handles command-line arguments.


init_netw():
	initializes all variables needed to talk to the server.


main():
	calls init_args() to initialize variables.
	starts the listen and transmit threads with those variables.
	waits for transmit thread to exit; then kills listen thread
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define MAX_MSG_LEN	1024


struct arg_info {
	/*	ip address of server	*/
	char *serv_ip;
	/*	port number of server	*/
	int port;
	/*	client's username	*/
	char *username[20];
};

struct net_info {
	/*	socket file descriptor	*/
	int socketfd;
	/*	server sockaddr_in struct	*/
	struct sockaddr_in serv_addr;
	/*	length of above	*/
	int serv_addr_len;

	/*	so we can reference the arguments in this struct	*/
	struct arg_info *parsed_args;
};


int init_args(struct arg_info *parsed_args, int argc, char **argv);
int init_netw(struct net_info *netwrk_info, struct arg_info *parsed_args);
void *listen_task(void *arg);
void *transmit_task(void *arg);


int main(int argc, char **argv)
{
	/*	create our structs	*/
	struct arg_info *parsed_args = malloc(sizeof(struct arg_info));
	struct net_info *netwrk_info = malloc(sizeof(struct net_info));
	/*	to allow netwrk_info to reference the parsed args later	*/
	netwrk_info->parsed_args = parsed_args;

	/*	parse args into 'parsed_args' struct	*/
	init_args(parsed_args, argc, argv);
	/*	initialize network structs and variables into 'netwrk_info' struct	*/
	init_netw(netwrk_info, parsed_args);


	/*	create transmitter thread and listener threads	*/
	pthread_t listener, transmitter;
	/*	start listener thread	*/
	pthread_create(&listener, NULL, listen_task, netwrk_info);
	pthread_create(&transmitter, NULL, transmit_task, netwrk_info);

	/*	wait for transmitter thread to finish	*/
	pthread_join(transmitter, NULL);
	pthread_join(listener, NULL);

	printf("main cleaning up..\n");
	/*	cleanup	*/
	free(parsed_args);
	free(netwrk_info);
}


void *transmit_task(void *arg)
{
	struct net_info *netwrk_info = (struct net_info *) arg;
	printf("[transmit] transmit task!\n");

	printf("[transmit] $%s:", netwrk_info->parsed_args->username);
	char buf[MAX_MSG_LEN] = "";
	fgets(buf, MAX_MSG_LEN, stdin);
	printf("\n[transmit] sending %s...\n", netwrk_info->parsed_args->username);

	sendto(netwrk_info->socketfd, buf, strlen(buf), 0,
			(struct sockaddr *) &(netwrk_info->serv_addr),
			netwrk_info->serv_addr_len);
	printf("\n[transmit] sent!\n");
}


void *listen_task(void *arg)
{
	struct net_info *netwrk_info = (struct net_info *) arg;
	printf("[listen] listen task!\n");

	printf("[listen] listening...\n");
	char buf[MAX_MSG_LEN] = "";
	recvfrom(netwrk_info->socketfd, buf, MAX_MSG_LEN, 0,
				(struct sockaddr *) &(netwrk_info->serv_addr),
				&(netwrk_info->serv_addr_len));

	printf("[listen] got: %s\n", buf);
}


int init_netw(struct net_info *netwrk_info, struct arg_info *parsed_args)
{
	/*	create our UDP socket	*/
	netwrk_info->socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (netwrk_info->socketfd < 0) {
		fprintf(stderr, "ERROR: could not create socket!\n");
		return 1;
	}

	/*	clear netwrk_info->serv_addr to be empty	*/
	memset(&(netwrk_info->serv_addr), 0, sizeof(netwrk_info->serv_addr));
	/*	init serv_addr_len to be the length of serv_addr	*/
	netwrk_info->serv_addr_len = sizeof(netwrk_info->serv_addr);

	/*	serv_addr member initialization	*/
	netwrk_info->serv_addr.sin_family = AF_INET;
	netwrk_info->serv_addr.sin_port = htons(parsed_args->port);

	/*	convert from string ip to binary in serv_addr	*/
	int ret = inet_aton(parsed_args->serv_ip,
						&(netwrk_info->serv_addr.sin_addr));
	if (ret == 0) {
		fprintf(stderr, "ERROR: could not convert ip '%s' to binary!\n",
				parsed_args->serv_ip);
		return 2;
	}
}


int init_args(struct arg_info *parsed_args, int argc, char **argv)
{
	/*	confirm we have the correct number of command-line args	*/
	if (argc != 3) {
		fprintf(stderr, "ERROR: not enough arguments\n"
						"USAGE: ./client [ip] [port]\n");
		return 1;
	}

	/*	get the port from the given arguments. abort if error.	*/
	parsed_args->port = atoi(argv[2]);
	if (parsed_args->port == 0) {
		fprintf(stderr, "ERROR: could not convert '%s' to an integer!\n",
				argv[2]);
		return 2;
	}

	/*	ask user for name to use and set it	*/
	printf("Enter your username (up to 20 characters): ");
	scanf("%s", parsed_args->username);
	printf("\nYour username has been set to: %s\n", parsed_args->username);


	/*	get the ip from the given arguments.	*/
	parsed_args->serv_ip = argv[1];

	return 0;
}



