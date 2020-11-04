/*
	collin gros
	11-03-2020
	cs474
	project2

*/

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>


int main()
{
	char c;
	FILE *fp;

	fp = fopen("mytest.dat", "w");
	for (int i = 0; i < 150; ++i) {
		fprintf(fp, "x", i);
	}
/*
	fp = fopen("mytest.dat", "r");
	while (fscanf(fp, "%c", &c) != EOF) {
		printf("%c", c);
	}
*/
	fclose(fp);
}

