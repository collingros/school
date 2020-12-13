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
#include <pthread.h>

/*	max msg length is 1KB	*/
#define MAX_MSG_LEN	1024


/*	encapsulates all data needed for sending/receiving for passing
	to threads	*/
struct connection_info {
	int socketfd;
	struct sockaddr_in *serv_addr;
	int serv_addr_len;
};


/*	transmit function for the transmitter thread. used to send chats
	to the server.	*/
void *transmit(void *connection_info)
{
	struct connection_info *connection = (struct connection_info *)
										connection_info;
	int socketfd = connection->socketfd;
	struct sockaddr_in *serv_addr = connection->serv_addr;
	int *serv_addr_len = connection->serv_addr_len;
	char sendbuf[MAX_MSG_LEN];

	/*	wipe the buffer and get user's message	*/
	memset(sendbuf, 0, strlen(sendbuf));
	printf("%:");
	fgets(sendbuf, sizeof(sendbuf), stdin);
	printf("\n");

	printf("sending...");
	/*	send msg	*/
	int ret = sendto(socketfd, sendbuf, strlen(buf), 0,
						(struct sockaddr *) serv_addr,
						*serv_addr_len);

}


void *listen(void *connection_info)
{
	struct connection_info *connection = (struct connection_info *)
										connection_info;
	int socketfd = connection->socketfd;
	struct sockaddr_in *serv_addr = connection->serv_addr;
	int *serv_addr_len = connection->serv_addr_len;
	char recvbuf[MAX_MSG_LEN];

		/*	listen for msg from server	*/
		int msg_len = recvfrom(socketfd, recvbuf,
								MAX_MSG_LEN, 0, (struct sockaddr *)
								serv_addr, serv_addr_len);
		/*	print the sender's ip and port, and the message	*/
		printf("from %s:%d:\n\t%s\n", inet_ntoa(
									serv_addr->sin_addr),
									ntohs(serv_addr->sin_port),
									recvbuf);
}



int main(int argc, char **argv)
{
	/*	confirm we have the correct number of command-line args	*/
	if (argc != 3) {
		fprintf(stderr, "ERROR: not enough arguments\n"
						"USAGE: ./client [ip] [port]\n");
		return 1;
	}

	/*	get the port from the given argument. abort if error.	*/
	int port = atoi(argv[2]);
	if (port == 0) {
		fprintf(stderr, "ERROR: could not convert '%s' to an integer!\n",
				argv[2]);
		return 2;
	}

	/*	ask user for name to use and set it	*/
	printf("Enter your username: ");
	scanf("%s", buf);
	const char *USERNAME;
	strcpy(USERNAME, buf);
	printf("\nYour username has been set to: %s\n", USERNAME);


	/*	get the ip from the given argument.	*/
	const char *SERV_IP = argv[1];


	/*	INITIALIZING STEP	*/
	/*	initialize everything to prepare for listening/transmission	*/
	int socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketfd < 0) {
		fprintf(stderr, "ERROR: could not create socket!\n");
		return 3;
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));

	int serv_addr_len = sizeof(serv_addr);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	/*	convert from string ip to binary in serv_addr	*/
	int ret = inet_aton(SERV_IP, &serv_addr.sin_addr);
	if (ret == 0) {
		fprintf(stderr, "ERROR: could not convert ip '%s' to binary!\n",
				SERV_IP);
		return 4;
	}
	/*	END INITIALIZING STEP	*/

	

	/*	start listener and transmitter threads	*/
	if (pthread_create(&listener, NULL, listen, connection)) {
		fprintf(stderr, "ERROR: failed to create listener thread!\n");
		return 5;
	}

	if (pthread_create(&transmitter, NULL, transmit, connection)) {
		fprintf(stderr, "ERROR: failed to create listener thread!\n");
		return 6;
	}

	return 0;
}

