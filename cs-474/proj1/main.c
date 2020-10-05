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
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define PROJ_ID 1


/*	what we are gonna pass to our child processes for
	them to modify	*/
struct shm {
	int value;
};


/*	proc1
	input: shared mem struct of which to increment value
	output: shared mem struct is incremented up to requested point as per
			the project description, returns nonzero for failure	*/
int proc1(struct shm *total)
{

}


/*	proc2
	input: shared mem struct of which to increment value
	output: shared mem struct is incremented up to requested point as per
			the project description, returns nonzero for failure	*/
int proc2(struct shm *total)
{

}


/*	proc3
	input: shared mem struct of which to increment value
	output: shared mem struct is incremented up to requested point as per
			the project description, returns nonzero for failure	*/
int proc3(struct shm *total)
{

}


/*	proc4
	input: shared mem struct of which to increment value
	output: shared mem struct is incremented up to requested point as per
			the project description, returns nonzero for failure	*/
int proc4(struct shm *total)
{

}


/*	doproc
	input: which process to execute, the shared memory pointer
	output: process performs requested operations, returns nonzero for
			failure	*/
int doproc(int n, struct shm *total)
{
	/*	execute corresponding process function to n	*/
	switch (n) {
		case 1:
			if (proc1(total)) {
				/*	proc1 failed	*/
				return 1;
			};
			break;
		case 2:
			if (proc2(total)) {
				/*	proc1 failed	*/
				return 2;
			};
			break;
		case 3:
			if (proc3(total)) {
				/*	proc1 failed	*/
				return 3;
			};
			break;
		case 4:
			if (proc4(total)) {
				/*	proc1 failed	*/
				return 4;
			};
			break;
		default:
			fprintf(stderr, "failed to find a process that "
					"corresponds to given n!\n");
			return 5;
	}

	return 0;
}


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

	/*	spawn 4 children with fork: each one executes its own instructions
		as given in the function proc{i}()	*/
	for (int i = 1; i < 5; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			/*	child	*/
			if (doproc(i, total)) {
				/*	process failed, or doproc failed	*/
				fprintf(stderr, "doproc failed\n");
				exit(1);
			};
		}
	}

	/*	wait for all child processes to quit	*/
	pid_t pid;
	int status;
	while (pid = wait(&status)) {
		printf("%d done\n", pid);
	}

	return 0;
}


