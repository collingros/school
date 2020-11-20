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

int main(int argc, char** argv)
{
	/*	confirm we have the correct number of arguments	*/
	if (argc != 3) {
		fprintf(stderr, "main.c: incorrect number of arguments\n"
						"\tusage: ./run [_le name] [time (s) "
						"required for baboon to cross]\n");
		return 1;
	}


	return 0;
}
