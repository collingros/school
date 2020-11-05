/*
	collin gros
	11-03-2020
	cs474
	project2

	purpose:	learn how to use semaphores to protect a limited size
				resource.

	references:
			given:	textbook
			given:	CS474_project2.pdf
			https://www.geeksforgeeks.org/use-posix-semaphores-c/
			https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
			https://stackoverflow.com/a/827749

*/

#define _REENTRANT
/*	size of our shared circular buffer	*/
#define MAX_BUFFER_SIZE	15
/*	character size is 1 byte	*/
#define BUFFER_SZ		1

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

/*	allocate circular buffer in data segment (global) so it is not
	in the stack since the stack is not shared across threads	*/
static circular_buffer buf;


/*	producer thread:
		reads characters one by one from mytest.dat and places it in
		the buffer and continues to do that until EOF. it informs
		the consumer when reaching EOF (after placing last char in buff).
		it does this by placing * into the buffer.	*/
void* producer(void* arg)
{
	/*	open test file for reading	*/
	char c;
	FILE *fp;

	fp = fopen("mytest.dat", "r");
	while (fscanf(fp, "%c", &c) != EOF) {
		/*	wait until there is space in buffer	*/
		sem_wait(&empty_count);
		/*	wait our turn	*/
		sem_wait(&mutex);

		/*	inserting character into shared buffer	*/
		cb_push_back(&buf, &c);

		/*	end our turn	*/
		sem_post(&mutex);
		/*	for consumer to know it has available data to get	*/
		sem_post(&fill_count);
	}

	fclose(fp);

	/*	wait until there is space in buffer	*/
	sem_wait(&empty_count);
	/*	wait our turn	*/
	sem_wait(&mutex);

	/*	insert * into buffer as we've reached EOF	*/
	const char star = '*';
	cb_push_back(&buf, &star);

	/*	end our turn	*/
	sem_post(&mutex);
	/*	for consumer to know it has available data to get	*/
	sem_post(&fill_count);
}


/*	consumer thread:
		runs slower than the producer (1 second sleep in between reads of
		buffer).
		reads chars one by one from the shared buffer and prints to
		the screen.	*/
void* consumer(void* arg)
{
	while (1) {
		/*	sleep instruction added to run slower than producer */
		sleep(1);

		/*	wait until producer gives us data	*/
		sem_wait(&fill_count);
		/*	wait for our turn	*/
		sem_wait(&mutex);

		/*	retrieve char from buffer and print it	*/
		char c;
		cb_pop_front(&buf, &c);

		/*	abort if EOF	*/
		if (c == '*') {
			break;
		}

		printf("%c", c);
		fflush(stdout);

		/*	end our turn	*/
		sem_post(&mutex);
		/*	let producer know there is an available spot	*/
		sem_post(&empty_count);
	}
}


/*	parent process (main):
		creates both the producer and consumer threads and waits until
		both are finished tod estroy semaphores.	*/
int main()
{
	/*	initialize the circular buffer with a maximum size and the
		size of the data type	*/
	cb_init(&buf, MAX_BUFFER_SIZE, BUFFER_SZ);

	/*	initialize semaphore to 1 so the first created process (producer)
		executes first	*/
	sem_init(&mutex, 0, 1);
	/*	no spots are full	*/
	sem_init(&fill_count, 0, 0);
	/*	all spots are empty	*/
	sem_init(&empty_count, 0, MAX_BUFFER_SIZE);


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

