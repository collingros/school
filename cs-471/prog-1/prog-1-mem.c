/*
	collin gros
	08-30-2020

	program that prints the memory location of various arrays
	and functions
*/


#include <stdio.h>


/*	INPUT:	void
	OUTPUT:	1
	PRECONDITION:	program is runnning
	POSTCONDITION:	prints the memory locations of various arrays and
					functions for proof of where they are located
					in memory	*/
int main()
{
	/*	in main's activation record (stack)	*/
	int A[100];
	/*	same as A	*/
	char *S = (char *)A;

	/*	in the data segment	*/
	static int B[100];

	printf("main is at \t\t%p\n"
			"A is at \t\t%p\n"
			"S is at \t\t%p\n"
			"*S is at \t\t%p\n"
			"B is at \t\t%p\n", main, A, &S, S, B);

	return 1;
}

