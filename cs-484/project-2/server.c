/*
collin gros
12-12-2020
cs484
project-2
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*	max msg length is 1KB	*/
#define MAX_MSG_LEN	1024


int main(int argc, char **argv)
{
	/*	confirm we have the correct number of command-line args	*/
	if (argc != 2) {
		fprintf(stderr, "ERROR: not enough arguments\n"
						"USAGE: ./server [port to listen on]\n");
		return 1;
	}

	/*	get the port from the given argument. abort if error.	*/
	int port = atoi(argv[1]);
	if (port == 0) {
		fprintf(stderr, "ERROR: could not convert '%s' to an integer!\n",
				argv[1]);
		return 2;
	}


	/*	INITIALIZING STEP	*/
	/*	initialize everything to prepare for listening/transmission	*/
	int socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketfd < 0) {
		fprintf(stderr, "ERROR: could not create socket!\n");
		return 3;
	}

	struct sockaddr_in serv_addr, client_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	int client_addr_len = sizeof(client_addr);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*	bind the socket and serv_addr	*/
	int ret = bind(socketfd, (struct sockaddr *) &serv_addr,
					sizeof(serv_addr));
	if (ret < 0) {
		fprintf(stderr, "ERROR: bind() failed!\n");
		return 4;
	}
	/*	END INITIALIZING STEP	*/

	
	char buf[MAX_MSG_LEN];
	/*	begin listening/transmitting	*/
	while (1) {
		printf("listening...\n");
		fflush(stdout);

		/*	retrieve msg and put it into buffer (buf)	*/
		int msg_len = recvfrom(socketfd, buf, MAX_MSG_LEN, 0,
								(struct sockaddr *) &client_addr,
								&client_addr_len);

		/*	print the sender's ip and port, and the message	*/
		printf("from %s:%d:\n\t%s\n", inet_ntoa(client_addr.sin_addr),
									ntohs(client_addr.sin_port),
									buf);

	}



	return 0;
}




