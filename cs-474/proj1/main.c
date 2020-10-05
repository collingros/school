/*
	collin gros
	10-04-2020
	cs474
	project1
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define PROJ_ID 1


/*	what we are gonna pass to our child processes for
	them to modify	*/
struct shm {
	int value;
};


int main()
{
	/*	generate key for shmget	*/
	key_t key = ftok("mem", PROJ_ID);
	if (key < 0) {
		/*	ftok failed	*/
		perror("ftok");
		exit(1);
	}

	/*	get id of segment we are going to use for shared memory	*/
	int shmid = shmget(key, sizeof(struct shm), IPC_CREAT | 0666);
	if (shmid < 0) {
		/*	shmget failed	*/
		perror("shmget");
		exit(1);
	}

	/*	attaching memory segment	*/
	struct shm *total = shmat(shmid, NULL, 0);
	if (total == (struct shm *) -1) {
		/*	shmat failed	*/
		perror("shmat");
		exit(1);
	}

	total->value = 0;
	pid_t pid1 = fork();
	if (pid1 == 0) {
		/*	child	*/
	}
	else {
		/*	parent*/
	}
}


