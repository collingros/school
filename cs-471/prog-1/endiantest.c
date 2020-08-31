/*
	collin gros
	08-30-2020

	retrieved from:
https://stackoverflow.com/questions/4181951/how-to-check-whether-a-system-is-big-endian-or-little-endian
*/


#include <stdio.h>

int main()
{
	int n = 1;
	if (*(char *)&n == 1) {
		printf("little endian!\n");
	}
	else {
		printf("big endian!\n");
	}
}
