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

#include "udp.h"


int udp_servinit(int *mysocket)
{
	*mysocket = socket(AF_INET, SOCK_DGRAM, IPROTO_UDP);
	if (mysocket < 0) {
		fprintf(stderr, "[server.c] ERROR: failed to create socket!\n");
		return 1;
	}
}
