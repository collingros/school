/*!
	collin gros
	03/12/2020
*/

#include "decrypt_helper.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>


int getFrequencyOfLetter(char letter)
{
	FILE *fp;
	fp = fopen(CIPHERTEXT, "r");

	/* if our file DNE */
	if (fp == NULL) {
		return -1;
	}

	int count = 0;
	int curChar = fgetc(fp);
	while (curChar != EOF) {
		/* increment counter every time 'letter' is found */
		if (curChar == letter) {
			++count;
		}

		curChar = fgetc(fp);
	}

	fclose(fp);
	return count;
}


struct dict *getDictFromDictionaryFile()
{
	FILE *fp = fopen(DICTIONARY, "r");
	/* if there was an error opening our dictionary file */
	if (fp == NULL) {
		return NULL;
	}

	int size = getLineCount(fp);
	printf("size: %d\n", size);
	struct dict *myDict = createDict(size);
	/* if there was an error initializing a new dictionary */
	if (myDict == NULL) {
		return NULL;
	}

	char word[MAX_WORD_LENGTH];
	while (fgets(word, MAX_WORD_LENGTH, fp) != NULL) {
		/* if insert encounters any error */
		if(insert(myDict, word, "")) {
			return NULL;
		}
	}

	fclose(fp);
	return myDict;
}


int getNumberOfWords(struct dict *myDict, char *key)
{
	/* iterate through key */
	for (char *curChar = tmpKey; *curChar != '\0'; ++curChar) {
		char *subkey;
		struct node *findResult = find(myDict, subkey);
	}
}


int getLineCount(FILE *fp)
{
	int count = 0;
	int curChar = fgetc(fp);
	while (curChar != EOF) {
		if (curChar == '\n') {
			++count;
		}

		curChar = fgetc(fp);
	}

	/* our EOF and position were changed, need to reset them */
	rewind(fp);
	return count;
}

