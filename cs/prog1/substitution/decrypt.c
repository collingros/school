/*!
	collin gros
	03/12/2020

	decrypts a substitution cipher given in ciphertext.txt, with words from
	dictionary.txt
*/

#include "dict.h"
#include "decrypt_helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_FILE	"dictionary.txt"
#define CIPHERTEXT_FILE	"ciphertext.txt"
#define NUM_PERMUTATIONS	3


int main()
{
	struct dict *myDict = getDictFromDictionaryFile(DICTIONARY_FILE);
	if (myDict == NULL) {
		printf("ERROR: problem retrieving myDict!\n");
		exit(1);
	}

	char *text = convertFileToStr(CIPHERTEXT_FILE);
	char choice;
	printf("would you like to enter your own key? (y/n)\n");
	scanf("%c", &choice);
	switch (choice) {
		case 'y':
			printf("ENTER YOUR VALUES!\n");
			int *usrkey = malloc(sizeof(int) * 26);
			for (int i = 0; i < 26; ++i) {
				char userc;
				printf("%c: \n", (i + 'A'));
				scanf(" %c", &userc);
				usrkey[i] = userc - 'A';
			}

			char *p = getDecryption(text, usrkey);
			printf("decryption: %s\n", p);

			free(p);
			free(usrkey);
			break;
		case 'n':
			printf("PERFORMING DECRYPTION!\n");
			int *freqs = getFrequencyOfAllLetters(text);
			int *key = getFreqBasedKey(freqs);

			printBestDecryption(myDict, text, key);
			break;
		default:
			printf("unknown choice entered!\n");
			exit(1);
	}

	free(text);


	dictDestroy(myDict);

	/*
	free(plaintext);
	free(text);
	free(freqs);
	free(key);
	*/

	return 0;
}


