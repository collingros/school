/*!
	collin gros
	03/12/2020

	decrypts a substitution cipher given in ciphertext.txt, with words from
	dictionary.txt
*/

#include "dict.h"
#include "decrypt_helper.h"

#include <stdio.h>


int main()
{
	struct dict *myDict = getDictFromDictionaryFile();
	if (myDict == NULL) {
		printf("ERROR: problem retrieving myDict!\n");
		exit(1);
	}

	int num = getNumberOfWords(myDict, "hello, what is your name?");
	printf("num: %d\n", num);

	dictDestroy(myDict);

	return 0;
}
