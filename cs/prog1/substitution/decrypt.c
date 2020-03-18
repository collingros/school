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

	int *freqs = getFrequencyOfAllLetters();
	for (int i = 0; i < 26; ++i) {
		char c = i + 'A';
		printf("letter: %c\tfreq: %d\n", c, freqs[i]);
	}

	int *res = getGuessedKey(freqs);
	for (int i = 0; i < 26; ++i) {
		char c = i + 'A';
		printf("c: %c\tres: %c\n", c, res[i] + 'A');
	}

	decrypt(res);

	return 0;
}
