/*!
	collin gros
	03/12/2020

	decrypts a substitution cipher given in ciphertext.txt, with words from
	dictionary.txt
*/

#include "dict.h"
#include "decrypt_helper.h"

#include <stdio.h>

#define DICTIONARY_FILE	"dictionary.txt"
#define CIPHERTEXT_FILE	"ciphertext.txt"


int main()
{
	struct dict *myDict = getDictFromDictionaryFile(DICTIONARY_FILE);
	if (myDict == NULL) {
		printf("ERROR: problem retrieving myDict!\n");
		exit(1);
	}

	char *key = getBestDecryption(myDict, CIPHERTEXT_FILE);
	printf("best decryption: %s\n", key);

	dictDestroy(myDict);

	return 0;
}
