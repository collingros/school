/*
	collin gros
	08-30-2020
	prog-1-alt

	shows what happens when we
*/

#include <stdio.h>


int main()
{
	/*	3 bytes are needed for my name, plus the one
		for a null */
	int nameArr[4];
	/*	for printing the array of ascii-coded bytes with printf	*/
	char *S = (char *) nameArr;

	/*	must multiply by powers of 256 (i think this is the same
		thing as bitshifting by 8 because 2^8 = 256?)	*/
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

	/*	this way prints xxx	*/
/*
	nameArr[3] = 'x' +
				'x' * (256) +
				'x' * (256 * 256) +
				0;
*/

	/*	this way prints nothing	*/
	nameArr[3] = 0 +
				'x' * (256) +
				'x' * (256 * 256) +
				'x' * (256 * 256 * 256);

	/*	print my name!	*/
	printf("My name is %s\n", S);
}
