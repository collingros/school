/*
	collin gros
	11-03-2020
	cs474
	project2

	purpose:	learn how to use semaphores to protect a limited size
				resource.

	references:
			[ given:	textbook ]
			[ given:	CS474_project2.pdf ]
			https://www.geeksforgeeks.org/use-posix-semaphores-c/
			https://stackoverflow.com/questions/6154539/how-can-i-
				wait-for-any-all-pthreads-to-complete
			https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem

*/

#define _REENTRANT
/*	size of our shared circular buffer	*/
#define MAX_B_SIZE	15
/*	character size is 1 byte	*/
#define B_SZ		1

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

/*	circular_buffer data structure	*/
#include "circ.h"



/*	semaphore for ensuring mutual exclusion in consumer and producer	*/
sem_t mutex;
/*	number of items in buffer	*/
sem_t fill_count;
/*	number of space in buffer	*/
sem_t empty_count;

/*	allocate circular buffer in data segment	*/
static circular_buffer buf;
cb_init(&buf, MAX_B_SIZE, B_SZ);


/*	producer thread:
		reads characters one by one from mytest.dat and places it in
		the buffer and continues to do that until EOF. it informs
		the consumer when reaching EOF (after placing last char in buff).
		it does this by placing * into the buffer.	*/
void* producer(void* arg)
{
	printf("entered producer\n");

	/*	reading test file	*/
	char c;
	FILE *fp;

	fp = fopen("mytest.dat", "r");
	while (fscanf(fp, "%c", &c) != EOF) {
		/*	inserting character into shared buffer	*/
		sem_wait(&empty_count);
		sem_wait(&mutex);
		cb_push_back(&buf, c);
		sem_post(&mutex);
		sem_post(&fill_count);
	}

	fclose(fp);

	/*	insert * into buffer as we've reached EOF	*/
	sem_wait(&empty_count);
	sem_wait(&mutex);
	cb_push_back(&buf, '*');
	sem_post(&mutex);
	sem_post(&fill_count);

	printf("exiting producer\n");
}


/*	consumer thread:
		runs slower than the producer (1 second sleep in between reads of
		buffer).
		reads chars one by one from the shared buffer and prints to
		the screen.	*/
void* consumer(void* arg)
{
	printf("entered consumer\n");

	while (1) {
		sem_wait(&fill_count);
		sem_wait(&mutex);

		/*	retrieve char from buffer and print it	*/
		char c;
		cb_pop_front(&buf, &c);
		printf("%c", c);

		sem_post(&mutex);
		sem_post(&empty_count);
	}

	printf("exiting consumer\n");
}


/*	parent process (main):
		creates both the producer and consumer threads and waits until
		both are finished tod estroy semaphores.	*/
int main()
{
	/*	initialize semaphore to 1 so the first created process (producer)
		executes first	*/
	sem_init(&mutex, 0, 1);
	sem_init(&fill_count, 0, 0);
	sem_init(&empty_count, 0, MAX_B_SIZE);


	/*	create producer and consumer threads. producer runs critical
		section first.	*/

	pthread_t tprod, tcons;
	pthread_create(&tprod, NULL, producer, NULL);
	pthread_create(&tcons, NULL, consumer, NULL);

	/*	wait until both are finshed	and destroy producer and consumer
		threads.	*/
	pthread_join(tprod, NULL);
	pthread_join(tcons, NULL);


	/*	cleanup	*/
	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);
	return 0;
}

