/*
	collin gros
	11-20-2020
	cs474
	proj3

	this is the main function for the baboon problem in the problem
	description (Problem 1 in ./problem.pdf)

	sources used for this code are located in ./sources/main.txt
*/

#include <stdio.h>
#include <stdlib.h>

/*	pthreads	*/
#include <pthread.h>

/*	sleep	*/
#include <unistd.h>

/*	error handling	*/
#include <errno.h>
#include <string.h>

/*	maximum total of 'R' and 'L' characters ('R's + 'L's) in the
	given baboon file	*/
#define MAX_BABOONS	100


/*	keep record of numbers of baboons	*/
struct baboon_counts {
	int total;
	int left;
	int right;
};


void *left(void *arg);
void *right(void *arg);
int init(char** argv, char *baboon_buf,
			struct baboon_counts *baboon_counts);


/*	how long it takes for a baboon to cross (user input)	*/
static int travel_time;



int main(int argc, char** argv)
{
	/*	confirm we have the correct number of arguments	*/
	if (argc != 3) {
		fprintf(stderr, "main.c: incorrect number of arguments\n"
						"\tusage: ./run [_le name] [time (s) "
						"required for baboon to cross]\n");
		return 1;
	}


	/*	INITIALIZE VARS TO ARGUMENTS	*/
	struct baboon_counts baboon_counts;
	char baboon_buf[MAX_BABOONS];
	/*	initialize vars to arguments; if error, print and return	*/
	if (init(argv, baboon_buf, &baboon_counts)) {
		fprintf(stderr, "init(): ERROR: %s\n", strerror(errno));
		return 1;
	}


	/*	PREPARE FOR THREAD CREATION	*/
	/*	note: in the CREATE THREADS section, the baboons are created in
				a reverse order, meaning, the first baboon to be queued
				on the right side has a PID located at
					baboon_counts.right - 1
				the second has a PID located at
					baboon_counts.right - 2 (because right is decremented)
				... all the way to 0 (no baboons are waiting to be
										queued on the right side)	*/
	pthread_t r_baboons[baboon_counts.right],
				l_baboons[baboon_counts.left];


	/*	CREATE THREADS	*/
	for (int i = 0; i < baboon_counts.total; ++i) {
		/*	FIXME preserve FIFO order	*/
		sleep(1);

		/*	create thread for baboon	*/
		char baboon = baboon_buf[i];
		if (baboon == 'R') {
			/*	subtract 1 to avoid off-by-one error	*/
			int next_baboon = baboon_counts.right - 1;
			/*	create the thread	*/
			pthread_create(&r_baboons[next_baboon], NULL,
							right, NULL);

			/*	subtract 1 from the right queue as we have just
				queued a baboon from the right	*/
			baboon_counts.right--;
		}
		if (baboon == 'L') {
			/*	subtract 1 to avoid off-by-one error	*/
			int next_baboon = baboon_counts.left - 1;
			/*	create the thread	*/
			pthread_create(&l_baboons[next_baboon], NULL,
							left, NULL);

			/*	subtract 1 from the left queue as we have just
				queued a baboon from the left	*/
			baboon_counts.left--;
		}
	}


	/*	WAIT FOR THREAD COMPLETION	*/
	/*	[wait for ALL baboons]	*/
	/*	wait for right baboons	*/
	for (int i = baboon_counts.right-1; i > 0; --i) {
		pthread_join(r_baboons[i], NULL);
	}
	/*	wait for left baboons	*/
	for (int i = baboon_counts.left-1; i > 0; --i) {
		pthread_join(l_baboons[i], NULL);
	}


	return 0;
}


void *left(void *arg)
{
}

void *right(void *arg)
{
}


/*	init()
	initializes variables from cmd-line args (baboon_buf, baboon_counts,
												travel_time)
	pre: takes empty baboon_buf, baboon_counts struct, and uninitialized
			travel_time value
	post: baboon_buf contains 'R' and 'L' characters, in the order
			at which baboons arrive. baboon_counts contains the correct
			count of baboons in total, on the left, and on the right.
			travel_time is set to the given command-line value.
	return value: non-zero for error.

	note: the file located in argv[1] is opened and read.	*/
int init(char** argv, char *baboon_buf,
			struct baboon_counts *baboon_counts)
{
	/*	set time from argument	*/
	travel_time = atoi(argv[2]);

	/*	set baboon_counts and baboon_buf from file argument	*/
	FILE *file = fopen(argv[1], "r");
	/*	if file failed to open, error	*/
	if (file == NULL) {
		return 1;
	}

	/*	prepare to read file - initialize vars	*/
	baboon_counts->total = 0;
	baboon_counts->right = 0;
	baboon_counts->left = 0;

	/*	read file	*/
	for (char c = getc(file); c != EOF; c = getc(file)) {
		/*	fill baboon_buf according to which side the baboon crosses
			from	*/
		if (c == 'R' || c == 'L') {
			baboon_buf[baboon_counts->total] = c;
			if (c == 'R') {
				baboon_counts->right++;
			}
			if (c == 'L') {
				baboon_counts->left++;
			}
			baboon_counts->total++;
		}
	}

	return 0;
}

