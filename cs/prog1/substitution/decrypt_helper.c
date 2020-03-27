/*!
	collin gros
	03/12/2020
*/

#include "decrypt_helper.h"
#include "dict.h"

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

	int curChar = fgetc(fp);
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

	/*	remember to free!	*/
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

	/*	remember to free!	*/
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
	struct dict *myDict = dictCreate(size);
	/* if there was an error initializing a new dictionary */
	if (myDict == NULL) {
		return NULL;
	}

	char word[MAX_WORD_LENGTH];
	while (fgets(word, MAX_WORD_LENGTH, fp) != NULL) {
		/*	replaces newline with null character so strcmp works	*/
		word[strcspn(word, "\n")] = '\0';
		if (dictInsert(myDict, word, "")) {
			return NULL;
		}
	}

	fclose(fp);
	return myDict;
}


int getNumberOfWords(struct dict *myDict, char *ciphertext)
{
	int count = 0;

	for (char *c = ciphertext; *c != '\0'; ++c) {
		char subStr[MAX_GUESSED_WORD_LENGTH + 1];

		for (int i = 0; i < MAX_GUESSED_WORD_LENGTH; ++i) {
			char subChar = *(c + i);
			if (subChar == '\0') {
				break;
			}

			subStr[i] = subChar;
			/* so we know where the end of the string is */
			subStr[i + 1] = '\0';

			struct entry *subStrNode = dictSearch(myDict, subStr);
			/*	check if a word was found	*/
			if (subStrNode != NULL) {
				printf("word found: %s\n", subStr);
				count++;
			}
		}
	}

	return count;
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

