/*
	collin gros
	08-29-2020
	cs-471
	prog-1
*/


#include <stdio.h>


int main()
{
	int nameArr[4];
	nameArr[0] = 'C' +
				'o' * (256) +
				'l' * (256 * 256) +
				'l' * (256 * 256 * 256);
	nameArr[1] = 'i' +
				'n' * (256) +
				' ' * (256 * 256) +
				'G' * (256 * 256 * 256);
	nameArr[2] = 'r' +
				'o' * (256) +
				's' * (256 * 256) +
				'.' * (256 * 256 * 256);
	nameArr[3] = 0;

	char *S = nameArr;
	printf("My name is %s\n", S);
}

