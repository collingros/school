/*
collin gros
12-12-2020
cs484
project-2


this program contains the implementaiton of the server side of my
udp-chat program.

my implementation currently only supports 1 client 1 server.

view 'udp-chat.h' for further documentation on many of the functions
that i use here.
*/

/*	note: other constants declared in 'udp-chat.h'	*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "udp-chat.h"


int main(int argc, char **argv)
{
	/*	signal handler for quitting - quit when any signal is sent	*/
	signal(SIGINT, sighandler);
	/*	disable stdout buffering	*/
	setbuf(stdout, NULL);
	listener = (pid_t) 0;

	/*	create our structs and prepare them for initialization	*/
	struct arg_info *parsed_args = malloc(sizeof(struct arg_info));
	struct net_info *netwrk_info = malloc(sizeof(struct net_info));
	/*	THESE ARE DEFINED IN 'udp-chat.h': used with cleanup()	*/
	parsed_args_p = parsed_args;
	netwrk_info_p = netwrk_info;


	/*	ask user to act as the client or the server	*/
	char c;
	do {
		printf("[main] Run as the server(y/n)?: ");
		scanf("%c\n", &c);
		/*	tell both structs who we are (client or server)	*/
		if (c == 'y') {
			parsed_args->is_server = 1;
			netwrk_info->is_server = 1;
			printf("[main] will run as the server...\n");
		}
		/*	tell both structs who we are (client or server)	*/
		else if (c == 'n') {
			parsed_args->is_server = 0;
			netwrk_info->is_server = 0;
			printf("[main] will run as the client...\n");
		}
		else {
			printf("[main] invalid input - try again.\n");
		}
	} while (c != 'y' && c != 'n');


	/*	to allow netwrk_info to reference the parsed args later	*/
	netwrk_info->parsed_args = parsed_args;


	/*	parse args into 'parsed_args' struct	*/
	int ret = init_args(parsed_args, argc, argv);
	if (ret != 0) {
		fprintf(stderr, "[main] ERROR: init_args() failed with code %d!\n",
				ret);
		return 1;
	}
	/*	initialize network structs and
		variables into 'netwrk_info' struct	*/
	ret = init_netw(netwrk_info, parsed_args);
	if (ret != 0) {
		fprintf(stderr, "[main] ERROR: init_netw() failed with code %d!\n",
				ret);
		return 2;
	}


	/*	start listener thread; listener defined in 'udp-chat.h'	*/
	pthread_create(&listener, NULL, listen_task, netwrk_info);

	while (1) {
		/*	prompt user for input, then save it to buf	*/
		printf("$%s:", parsed_args->username);
		char buf[MAX_MSG_LEN] = "";
		fgets(buf, MAX_MSG_LEN, stdin);

		/*	add our username to the outgoing message	*/
		/*	prepare formatted buffer, with space for username and '$:'
			*/
		char fbuf[MAX_MSG_LEN+22];
		sprintf(fbuf, "$%s:%s", parsed_args->username, buf);

		/*	send buf to appropriate addr	*/
		printf("\n[main] sending\"%s\"\n", fbuf);
		if (netwrk_info->is_server) {
			sendto(netwrk_info->socketfd, buf, strlen(buf), 0,
					(struct sockaddr *) &(netwrk_info->clin_addr),
					netwrk_info->clin_addr_len);
		}
		else {
			sendto(netwrk_info->socketfd, buf, strlen(buf), 0,
					(struct sockaddr *) &(netwrk_info->serv_addr),
					netwrk_info->serv_addr_len);
		}

		printf("\n[main] msg sent!\n");
	}


	printf("[main] begin cleanup...\n");
	/*	cleanup	*/
	cleanup(parsed_args, netwrk_info, listener);
	printf("[main] done\n");

	printf("[main] exiting...\n");
	return 0;
}






