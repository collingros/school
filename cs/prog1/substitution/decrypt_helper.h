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

#include "dict.h"

#include <stdlib.h>
#include <stdio.h>

/* the maximum length a word in the dictionary file will have */
#define MAX_WORD_LENGTH	100
/* the maximum length of the key to check for the existence of a word */
#define MAX_GUESSED_WORD_LENGTH	7


/*	generate a dictionary based on words in the dictionary file

	returns a pointer to the dictionary on success, otherwise NULL	*/
struct dict *getDictFromDictionaryFile(const char *file);


/*	returns the key that resulted in the best decryption	*/
char *getBestDecryption(struct dict *myDict, const char *file);


#endif
