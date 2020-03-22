/*!
	collin gros
	03/12/2020

	assists decrypt.c by
		reading ciphertext.txt and reporting the frequency of a given
		letter

		counting the number of words from dictionary.txt that exist in
		a given plausible key, and returning the total number counted

*/

#ifndef __DECRYPT_HELPER__
#define __DECRYPT_HELPER__

#include "hash.h"

#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY	"dictionary.txt"
#define CIPHERTEXT	"ciphertext.txt"
/* the maximum length a word in the dictionary file will have */
#define MAX_WORD_LENGTH	100
/* the maximum length of the key to check for the existence of a word */
#define MAX_GUESSED_WORD_LENGTH	7


/*
	decrypt()

	decrypts the ciphertext using multiple keys until it finds one
	that matches the most words in the given dictionary. prints
	the decryption to stdout

	returns 0 on success, otherwise failure
*/
	int decrypt(struct dict *myDict);


/*
	reads ciphertext.txt and reports the frequency of a given letter

	returns the frequency of the letter on success, otherwise -1
*/
int getFrequencyOfLetter(char letter);


/*
	creates and fills an array of 25 integers, each representing capital
	letters from A-Z

	returns an integer array with elements 0-25 (0 being A and 25 being Z),
	each with a value representing the frequency found in the ciphertext
	file
*/
int *getFrequencyOfAllLetters();


/*
	returns a mapping of the given key compared to frequency of letters in the
	English language
*/
int *getGuessedKey(int *freqs);


/*
	decrypt the ciphertext file and print decrypted characters to stdout

	returns 0 on success, otherwise failure
*/
int printDecryption(int *key);


/*
	generate a dictionary based on words in the dictionary file

	returns a pointer to the dictionary on success, otherwise NULL
*/
struct dict *getDictFromDictionaryFile();


/*
	counts the number of words from dictionary.txt that exist in a given
	plausible key, and returns the total number of words counted

	returns the number of words in tmpKey on success, otherwise -1
*/
int getNumberOfWords(struct dict *myDict, char *tmpKey);


/*
	counts the number of lines in a text file

	returns the number of lines in a text file
*/
int getLineCount(FILE *fp);


#endif
