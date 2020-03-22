/*!
	collin gros
	03/12/2020

	decrypts a substitution cipher given in ciphertext.txt, with words from
	dictionary.txt
*/

#include "hash.h"
#include "decrypt_helper.h"

#include <stdio.h>


int main()
{
	struct dict *myDict = getDictFromDictionaryFile();
	if (myDict == NULL) {
		printf("ERROR: problem retrieving myDict!\n");
		exit(1);
	}

	struct node *myNode = find(myDict, "hello");
	if (myNode != NULL) {
		printf("a word was found!\n");
	}

/*
	int num = getNumberOfWords(myDict, "hellomyname");
	printf("num: %d\n", num);
*/

	return 0;
}
