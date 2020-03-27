/*
	collin gros
	03/23/2020
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dict.h"


struct dict *dictCreate(int size)
{
	struct dict *myDict = malloc(sizeof(struct dict));
	/*	malloc failed!	*/
	if (myDict == NULL) {
		return NULL;
	}

	myDict->size = size;
	myDict->n = 0;

	myDict->table = malloc(sizeof(struct entry) * myDict->size);
	/*	malloc failed!	*/
	if (myDict->table== NULL) {
		return NULL;
	}

	/*	initialize all entries to 0 (so we know if it is empty or not	*/
	for (int i = 0; i < myDict->size; ++i) {
		myDict->table[i] = 0;
	}


	return myDict;
}


/*	frees the memory that was allocated in a given entry 'myEntry'

	returns 0 on success, otherwise failure	*/
int freeEntry(struct entry *e)
{
	free(e->key);
	free(e->val);
	free(e);
	e = NULL;

	return 0;
}


int dictDestroy(struct dict *myDict)
{
	/*	if myDict doesn't exist	*/
	if (myDict == NULL) {
		return 1;
	}

	/*	free memory of all entries in dictionary	*/
	for (int i = 0; i < myDict->size; ++i) {
		struct entry *myEntry = myDict->table[i];
		while (myEntry != NULL) {
			struct entry *nextEntry = myEntry->next;

			freeEntry(myEntry);

			myEntry = nextEntry;
		}
	}


	free(myDict->table);
	free(myDict);
	myDict = NULL;

	return 0;
}


/*	computes a hash for any given key, using the multiplier specified in
	the header file

	returns the hashed value for the given key, based on the additions of its
	ascii values	*/
size_t hash(const char *key)
{
	size_t res = 0;
	const char *curChar = key;
	for (; (int) *curChar != '\0'; ++curChar) {
		res = res * HASH_MULTIPLIER + *curChar;
	}

	return res;
}


int dictInsert(struct dict *myDict, const char *key, const char *val)
{
	/*	if any of the parameters don't exist	*/
	if (myDict == NULL || key == NULL || val == NULL) {
		return 1;
	}

	struct entry *newEntry = malloc(sizeof(struct entry));
	/*	malloc failed!	*/
	if (newEntry == NULL) {
		return 1;
	}

	newEntry->key = strdup(key);
	newEntry->val = strdup(val);

	/*	compute an idx that is (hopefully) unique from our hash function	*/
	size_t idx = hash(key) % myDict->size;

	/*	in case of a duplicate index, we chain together the entry that was
		previously in the table along with our new entry	*/
	struct entry *prevEntry = myDict->table[idx];
	newEntry->next = prevEntry;
	myDict->table[idx] = newEntry;
	myDict->n++;

	return 0;
}


struct entry *dictSearch(struct dict *myDict, const char *key)
{
	/*	if the dictionary doesn't exist!	*/
	if (myDict == NULL) {
		return NULL;
	}

	size_t idx = hash(key) % myDict->size;

	/*	first entry in chain corresponding to the given key	*/
	struct entry *myEntry = myDict->table[idx];

	/*	search all chained entries at this idx	*/
	for (; myEntry != NULL; myEntry = myEntry->next) {
		if (strcmp(myEntry->key, key) == 0) {
			return myEntry;
		}
	}

	return NULL;
}


