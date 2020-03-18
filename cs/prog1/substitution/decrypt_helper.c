/*!
	collin gros
	03/12/2020
*/

#include "decrypt_helper.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int printDecryption(int *key)
{
	FILE *fp;
	fp = fopen(CIPHERTEXT, "r");

	/* if our file DNE */
	if (fp == NULL) {
		return -1;
	}

	char curChar = fgetc(fp);
	while (curChar != EOF) {
		if (curChar >= 'A' && curChar <= 'Z') {
			char plaintext = key[curChar - 'A'];
			fputc(plaintext + 'A', stdout);
		}
		else {
			printf("\n");
		}

		curChar = fgetc(fp);
	}


	fclose(fp);
	return 0;
}


int *getFrequencyOfAllLetters()
{
	int *freqs = malloc((sizeof (int)) * 26);
	for (int i = 0; i < 26; ++i) {
		char c = i + 'A';
		freqs[i] = getFrequencyOfLetter(c);
	}

	return freqs;
}


int *getGuessedKey(int *freqs)
{
	/* ETAOINSHRDLCUMWFGYPBVKJXQZ */
	char *enString = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
	int *key = malloc(sizeof(int) * 26);
	memcpy(key, freqs, (sizeof(int) * 26));

	for (int h = 0; h < 26; ++h) {
		int maxVal = -1;
		int maxKey = -1;
		for (int i = 0; i < 26; ++i) {
			/* if we already used this key as a maximum, ignore it */
			if (freqs[i] == -1) {
				continue;
			}

			if (freqs[i] > maxVal) {
				maxVal = freqs[i];
				maxKey = i;
			}
		}

		/* we used this key */
		freqs[maxKey] = -1;

		int idx = enString[h] - 'A';
		key[maxKey] = idx;
	}

	return key;
}


struct dict *getDictFromDictionaryFile()
{
	FILE *fp = fopen(DICTIONARY, "r");
	/* if there was an error opening our dictionary file */
	if (fp == NULL) {
		return NULL;
	}

	int size = getLineCount(fp);
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
	int count = 0;
	for (char *curChar = key; *curChar != '\0'; ++curChar) {
		char *subkey;
		struct node *findResult = find(myDict, subkey);
		if (findResult != NULL) {
			count++;
		}
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

