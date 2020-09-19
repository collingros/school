/*
	collin gros
	09-17-2020

	using cooper's code to understand why a print statement is being
	jumped in main

	(Shaun Cooper 2020 Sept.)
*/

#include <stdio.h>


/*
	pre: printf statement must be after this function call so that
		you can see the effect of modifying the return address
	post: modifies the return address so that the printf statement
		following this function is skipped
	in: none
	out: print statements revealing memory around f
*/
void f()
{
	unsigned int *A;
	int i, a = 0, b = 0;

	// pointing A to its own address
	A = (unsigned int *) &A;
	// print memory around A
	for (i = 0; i <= 10; i++) {
		printf("\t%d\t%u\n", i, A[i]);
	}

	// backs up enough to call f infinitely
	//A[6] = A[6] - 20;
	//A[6] = A[6] - 10;

	// increments return address by 10 to skip the printf statement after
	// the f call
	//A[6] = A[6] + 10;

	// changed to 8 because we added 2 variables (2 bytes), so the
	// RA shifted by 2 bytes
	A[8] = A[8] + 10;

	printf("\tA:\t%u\n", A);

	// print memory around A (to see modified changes)
	for (i = -4; i <= 10; i++) {
		printf("\t%d\t%u\n", i, A[i]);
	}
}


/*
	pre: none
	post: none
	in: none
	out: exit status/ print statements that demonstrate how changing
		a return address using a pointer is possible
*/
int main()
{
	int A[100];
	unsigned int L[4];
	L[0] = 100;
	L[1] = 200;
	L[2] = 300;
	L[3] = 400;
	for (int i = 0; i < 100; i++) {
		A[i] = i;
	}

	printf("main:\t\t%lu\n", main);
	printf("f:\t\t%lu\n", f);

	printf("i ama bout to call f\n");
	f();
	printf("i called f\n");

	out: printf("I am here\n");
}
