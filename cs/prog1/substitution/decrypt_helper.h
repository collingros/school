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

/*
	reads ciphertext.txt and reports the frequency of a given letter

	returns the frequency of the letter on success, otherwise -1
*/
int getFrequencyOfLetter(char letter);


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
int getNumberOfWords(struct dict *myDict, char *tmpKey, size_t tmpKeySize);


/*
	counts the number of lines in a text file

	returns the number of lines in a text file
*/
int getLineCount(FILE *fp);


#endif
