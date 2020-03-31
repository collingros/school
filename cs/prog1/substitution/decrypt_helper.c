/*!
	collin gros
	03/12/2020
*/

#include "decrypt_helper.h"
#include "dict.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*	returns the contents of a given file in a string

	success:
		returns a char * pointing to the contents of the file (null-term.)
	failure:
		returns a NULL pointer
	NOTE:
		remember to free the returned pointer when finished with it!	*/
char *convertFileToString(const char *filename);


/*	returns the number of times a target letter is found in the
	given string

	success:
		returns the num of times a target letter is found in the str
	failure:
		---	*/
int getFrequencyOfLetter(char *text, char letter);


/*	returns the number of times each letter (A-Z) was counted in a string
	with indicies representing the letter that was counted, and values
	representing the number of times the letter was counted

	success:
		returns an int * pointing to an array representing the frequencies
		of each letter
	failure:
		returns a NULL pointer
	NOTE:
		remember to free the returned pointer when finished with it!	*/
int *getFrequencyOfAllLetters(char *text);


/*	counts the number of words from a dictionary that exist in a
	given text, and returns the total number of words counted

	success:
		returns the number of words counted
	failure:
		returns -1	*/
int getNumberOfWords(struct dict *myDict, char *text);


/*	maps a given frequency counted array to a possible key using frequencies
	of letters in the english language

	success:
		returns a pointer to the generated key
	failure:
		---
	NOTE:
		remember to free the returned pointer when finished with it!	*/
int *getFreqBasedKey(int *freqs);


/*	gets the number of lines in a given file

	success:
		returns the number of lines in the given file
	failure:
		---	*/
int getLineCount(FILE *fp);


/*	gets the number of characters in a file

	success:
		returns the num
	failure:
		---	*/
int getCharCount(FILE *fp);


/*	returns the number of characters in a given string

	success:
		returns the number of chars counted
	failure:
		---	*/
int getLength(char *text);


/*	converts a given file into a string

	success:
		returns the string
	failure:
		---	
	NOTE:
		remember to free the returned pointer when finished with it!	*/
char *convertFileToStr(char *filename);


/*	returns a decryption of the ciphertext using a given key

	success:
		returns plaintext
	failure:
		---
	NOTE:
		remember to free the returned pointer when finished with it!	*/
char *getDecryption(char *ciphertext, int *key);


int getFrequencyOfLetter(char *text, char letter)
{
	int count = 0;
	for (char *c = text; *c != '\0'; ++c) {
		if (*c == letter) {
			++count;
		}
	}

	return count;
}


int *getFrequencyOfAllLetters(char *text)
{
	int *freqs = malloc((sizeof (int)) * 26);
	for (int i = 0; i < 26; ++i) {
		char c = i + 'A';
		freqs[i] = getFrequencyOfLetter(text, c);
	}

	return freqs;
}


char *getDecryption(char *ciphertext, int *key)
{
	int len = getLength(ciphertext);
	char *dec = malloc((sizeof(char) * len) + 1);
	char *c = ciphertext;

	/*	iterate through the ciphertext..	*/
	for (int i = 0; i < len; ++i) {
		/*	the ciphertext char	*/
		int cval = *(c + i);
		/*	the decrypted char	*/
		char p;

		/*	save the newlines!	*/
		if (cval == '\n') {
			p = '\n';
		}
		else if (cval <= 'Z' || cval >= 'A') {
			int idx = cval - 'A';
			p = key[idx] + 'A';
		}

		dec[i] = p;
	}
	dec[len] = '\0';

	return dec;
}


int *getFreqBasedKey(int *freqs)
{
	/* ETAOINSHRDLCUMWFGYPBVKJXQZ */
	char *enString = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
	int *key = malloc(sizeof(int) * 26);
	memcpy(key, freqs, (sizeof(int) * 26));

	/*	so we don't alter freqs	*/
	int *freqsbkup= malloc(sizeof(int) * 26);
	memcpy(freqsbkup, freqs, (sizeof(int) * 26));

	for (int h = 0; h < 26; ++h) {
		int maxVal = -1;
		int maxKey = -1;
		for (int i = 0; i < 26; ++i) {
			/* if we already used this key as a maximum, ignore it */
			if (freqsbkup[i] == -1) {
				continue;
			}

			if (freqsbkup[i] > maxVal) {
				maxVal = freqsbkup[i];
				maxKey = i;
			}
		}

		/* we used this key */
		freqsbkup[maxKey] = -1;

		int idx = enString[h] - 'A';
		key[maxKey] = idx;
	}

	free(freqsbkup);

	/*	remember to free!	*/
	return key;
}


struct dict *getDictFromDictionaryFile(const char *filename)
{
	FILE *fp = fopen(filename, "r");
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


int notInArray(int *arr, int k, int len)
{
	for (int i = 0; i < len; ++i) {
		if (arr[i] == k) {
			return 0;
		}
	}

	return 1;
}


int inString(char *str, char k)
{
	for (char *c = str; *c != '\0'; ++c) {
		if (*c == k) {
			return 1;
		}
	}

	return 0;
}


int permute(int *freqs, int offset)
{
	int usedMaxes[26];
	int numMaxes = 0;
	/*	need to get all of the keys of the maxes	*/
	for (int x = 0; x < 26; ++x) {
		if (x > offset) {
			break;
		}

		int maxf = 0;
		int maxk = 0;
		for (int i = 0; i < 26; ++i) {
			if (freqs[i] > maxf && notInArray(usedMaxes, i, 26)) {
				maxf = freqs[i];
				maxk = i;
			}
		}

		usedMaxes[x] = maxk;
		++numMaxes;
	}


	for (int i = 0; i < numMaxes - 1; ++i) {
		int k1 = usedMaxes[i];
		int k2 = usedMaxes[i + 1];

		/*	making the swap	*/
		int tmpf = freqs[k2];
		freqs[k2] = freqs[k1];
		freqs[k1] = tmpf;
	}

	return 0;
}


int getNumberOfWords(struct dict *myDict, char *text)
{
	int count = 0;

	for (char *c = text; *c != '\0'; ++c) {
		char subStr[MAX_GUESSED_WORD_LENGTH + 1];

		for (int i = 0; i < MAX_GUESSED_WORD_LENGTH; ++i) {
			char subChar = *(c + i);
			if (subChar == '\0') {
				break;
			}

			subStr[i] = subChar;
			/* so we know where the end of the string is */
			subStr[i + 1] = '\0';

			if (i <= MIN_GUESSED_WORD_LENGTH) {
				continue;
			}

			struct entry *subStrNode = dictSearch(myDict, subStr);
			/*	check if a word was found	*/
			if (subStrNode != NULL) {
				printf("%s\n", subStr);
				count++;
			}
		}
	}

	return count;
}


int getCharCount(FILE *fp)
{
	int count = 0;
	int curChar = fgetc(fp);
	while (curChar != EOF) {
		if (curChar == '\n') {
			curChar = fgetc(fp);
			continue;
		}

		curChar = fgetc(fp);
	}

	/* our EOF and position were changed, need to reset them */
	rewind(fp);
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


char *convertFileToStr(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		return NULL;
	}

	char *str = malloc(sizeof(char) * getCharCount(fp) + 1);
	int i = 0;
	char c = fgetc(fp);
	while ((int) c != EOF) {
		str[i] = c;

		c = fgetc(fp);
		++i;
	}
	str[i] = '\0';

	fclose(fp);
	return str;
}


int getLength(char *text)
{
	int count = 0;
	for (char *c = text; *c != '\0'; ++c) {
		++count;
	}

	return count;
}


int swapLetters(char x, char y, char *text)
{
	for (char *c = text; *c != '\0'; ++c) {
		if (*c == x) {
			*c = y;
		}
		else if (*c == y) {
			*c = x;
		}
	}

	return 0;
}


int shiftLetters(char *text, int shift)
{
	for (char *c = text; *c != '\0'; ++c) {
		/*	wrap around	*/
		if (*c + shift > 'Z') {
			*c = *c + shift - 26;
		}
		else {
			*c = *c + shift;
		}
	}

	return 0;
}


int shiftKey(int *key)
{
	for (int i = 1; i < 26; ++i) {
		int tmp = key[i - 1];
		key[i - 1] = key[i];
		key[i] = tmp;
	}
}


void printBestDecryption(struct dict *myDict, char *text, int *freqs)
{
	int num = 0, bestIteration = 0, maxNum = 0;
	char *plaintext;
	/*	we try shifting the ciphertext first..	*/
	for (int i = 0; i < 26; ++i) {
		plaintext = getDecryption(text, freqs);
		num = getNumberOfWords(myDict, plaintext);

		if (num > maxNum) {
			bestIteration = i;
			maxNum = num;
		}

		free(plaintext);
		shiftKey(freqs);
	}

	for (int i = 0; i < bestIteration; ++i) {
		shiftKey(freqs);
	}

	plaintext = getDecryption(text, freqs);
	num = getNumberOfWords(myDict, plaintext);

	/*	from inspection, "security", "succeed", "if they"	*/
	swapLetters('P', 'Y', plaintext);
	swapLetters('F', 'D', plaintext);
	swapLetters('W', 'F', plaintext);

	char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int len = getLength(text);
	char *bestp = malloc((sizeof(char) * len) + 1);
	maxNum = 0;
	char *ignoreMe = "SECURITYDHFUL";
	/*	now we swap a bunch of letters to hopefully get a high word
		count	*/
	for (char *c = plaintext; (int) *c != '\0'; ++c) {
		/*	dont swap letters i think are in the right places	*/
		if ((int) *c == '\n') {
			continue;
		}
		else if (inString(ignoreMe, *c)) {
			continue;
		}

		for (char *x = alphabet; (int) *x != '\0'; ++x) {
			/*	dont swap letters i think are in the right places	*/
			if ((int) *x == '\n') {
				continue;
			}
			if (inString(ignoreMe, *x)) {
				continue;
			}

			swapLetters(*c, *x, plaintext);
			num = getNumberOfWords(myDict, plaintext);

			if (num > maxNum) {
				maxNum = num;
				memcpy(bestp, plaintext, (sizeof(char) * len) + 1);
				bestp[len] = '\0';
			}
		}
	}

	/*	more inspection..	*/
	/*	KQVERNZENT	:	GOVERNMENT?	*/
	swapLetters('K', 'G', bestp);
	swapLetters('Q', 'O', bestp);
	swapLetters('Z', 'M', bestp);

	/*	EVENTHOUGHBE	:	EVENTHOUGHWE	*/
	swapLetters('B', 'W', bestp);
	/*	PNOW	:	KNOW	*/
	swapLetters('P', 'K', bestp);
	/*	GOOGLEQNDMICROSOFT	:	GOOGLEANDMICROSOFT	*/
	swapLetters('Q', 'A', bestp);
	/*	COMBANIES	:	COMPANIES	*/
	swapLetters('B', 'P', bestp);
	/*	ZACK	:	BACK	*/
	swapLetters('Z', 'B', bestp);
	/*	EZCEPT	:	EXCEPT	*/
	swapLetters('Z', 'X', bestp);


	printf("decryption: %s\n", bestp);
}

