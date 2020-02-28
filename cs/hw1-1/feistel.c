/*!
	collin gros
	02/27/2020

	Homework1-1.pdf: #15

	program to compute a ciphertext block for a given plaintext block
	using a feistel cipher with
		round function:
			F(X, K) = X XOR K
		number of rounds:
			4
		plaintext block (P, 8 bits):
			1011 0101
		subkeys (K0 - K3, 4 bits):
			1011, 0100, 0101, 1010


		binary numbers are represented with the least significant bit
		at the end of the array
		e.g., 1011 0101 in an array is {10110101}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// fill leftHalf with left half of bits of src 
void getRightHalf(int *rightHalf, int *src)
{
	size_t halfSize = 4;
	size_t srcIndexOffset = 4;
	for (size_t i = 0; i < 4; ++i) {
		size_t realIndex = i + srcIndexOffset;
		rightHalf[i] = src[realIndex];
	}
}


// fill leftHalf with left half of bits of src 
void getLeftHalf(int *leftHalf, int *src)
{
	size_t halfSize = 4;
	for (size_t i = 0; i < halfSize; ++i) {
		leftHalf[i] = src[i];
	}
}


// concatenate the left and right parts of a binary number to res
void concatBinaryArrays(int *arr1, int *arr2, int *res)
{
	for (size_t i = 0; i < 8; ++i) {
		int curVal;
		// concatenate the left side first, then the right side
		if (i < 4) {
			curVal = arr1[i];
		}
		else {
			// because the right half starts at 0 and goes up to 4
			int actualIndex = i - 4;
			curVal = arr2[actualIndex];
		}

		res[i] = curVal;
	}
}


// prints an array of integers
void printArray(int *src, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		printf("%d", src[i]);
	}

	printf("\n");
}


// perform the XOR operation on each element in arr1 and arr2, and
// record the result in res
void xorArrays(int *arr1, int *arr2, int *res)
{
	for (size_t i = 0; i < 4; ++i) {
		res[i] = arr1[i] ^ arr2[i];
	}
}


// the given round function for our feistel cipher:
// F(X, K) = X XOR K
void roundFunction(int *oldRightHalf, int *subKey, int *res) {
	xorArrays(oldRightHalf, subKey, res);
}


int feistel(int *plaintext, int *ciphertext,
			int subkeyTable[4][4], size_t numRounds)
{
	// keep track of the old left, right and new left, right halves
	// through the rounds
	int *oldLeftHalf, *oldRightHalf;
	int *newLeftHalf, *newRightHalf;

	// repeat for every round
	for (size_t i = 0; i < numRounds; ++i) {
		printf("\nROUND: %d\n", i);

		// if this is our first round, we want to use the plaintext's
		// halves
		if (i == 0) {
			oldLeftHalf = malloc(4);
			oldRightHalf = malloc(4);

			getLeftHalf(oldLeftHalf, plaintext);
			getRightHalf(oldRightHalf, plaintext);
		}


		// grab our subkey for the round out of our subkeys table
		// (Ki)
		int *currentSubkey = subkeyTable[i];


		// GETTING NEW LEFT HALF
		// the newLeftHalf gets the oldRightHalf
		newLeftHalf = malloc(4);
		memcpy(newLeftHalf, oldRightHalf, sizeof(int) * 4);


		// GETTING NEW RIGHT HALF 
		int result[4];
		// get result of round function with oldRightHalf and current subkey
		roundFunction(oldRightHalf, currentSubkey, result);

		newRightHalf = malloc(4);
		// XOR oldLeftHalf with result of round function
		xorArrays(oldLeftHalf, result, newRightHalf);

		// set newHalves to be oldHalves, and free oldHalves
		free(oldLeftHalf);
		oldLeftHalf = newLeftHalf;

		free(oldRightHalf);
		oldRightHalf = newRightHalf;


		printf("Li: ");
		printArray(oldLeftHalf, 4);
		printf("Ri: ");
		printArray(oldRightHalf, 4);
	}

	// set our ciphertext to last left and right halves
	concatBinaryArrays(oldLeftHalf, oldRightHalf, ciphertext);
}


int main()
{
	int plaintext[8] = {1, 0, 1, 1, 0, 1, 0, 1};
	int ciphertext[8];

	int subkeyTable[4][4] = {
		{1, 0, 1, 1},
		{0, 1, 0, 0},
		{0, 1, 0, 1},
		{1, 0, 1, 0}
	};
	int numRounds = 4;

	printf("plaintext: ");
	printArray(plaintext, 8);

	feistel(plaintext, ciphertext, subkeyTable, 4);

	printf("ciphertext: ");
	printArray(ciphertext, 8);
}

