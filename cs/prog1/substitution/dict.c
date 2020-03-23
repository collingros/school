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
int freeEntry(struct entry *myEntry)
{
	free(myEntry->key);
	free(myEntry->val);
	free(myEntry);


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
		struct entry *curEntry = myDict->table[i];
		if (curEntry == NULL) {
			continue;
		}
		if (curEntry->next == NULL) {
			freeEntry(curEntry);
			continue;
		}

		/*	free up all of the nodes chained together from identical
			indexes	*/
		struct entry *prevEntry = curEntry;
		struct entry *nextEntry = curEntry->next;
		while (nextEntry != NULL) {
			/*	we're advancing to the node connected to nextEntry, then
				freeing the node we came from (prevEntry)	*/
			prevEntry = nextEntry;
			nextEntry = nextEntry->next;

			/*	erase the entryalong with all its components	*/
			freeEntry(prevEntry);
		}
	}

	free(myDict->table);
	free(myDict);

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
	for (curChar; (int) *curChar != '\0'; ++curChar) {
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
	size_t idx = hash(key) % myDict->size;

	/*	first entry in chain corresponding to the given key	*/
	struct entry *myEntry = myDict->table[idx];

	/*	move down the chain until we find our specific key	*/
	struct entry *curEntry = myEntry;
	while (curEntry != NULL) {
		if (strcmp(curEntry->key, key) == 0) {
			break;
		}

		curEntry = curEntry->next;
	}

	/*	nextEntry will be NULL if the specified entry was not found!	*/
	return curEntry;
}


int dictDelete(struct dict *myDict, const char *key)
{
	/*	we could use dictSearch here, but then we wouldn't know how to
		tell the previous node that this node doesn't exist anymore	*/
	size_t idx = hash(key) % myDict->size;

	/*	first entry in chain corresponding to the given key	*/
	struct entry *myEntry = myDict->table[idx];

	/*	no entry exists with this key! nothing to delete!	*/
	if (myEntry == NULL) {
		return 0;
	}

	/*	move down the chain until we find our specific key	*/
	struct entry *curEntry = myEntry;
	struct entry *prevEntry = myEntry;
	while (curEntry->next != NULL) {
		if (strcmp(curEntry->key, key) == 0) {
			break;
		}

		curEntry = curEntry->next;
		prevEntry = curEntry;
	}

	/*	skip over the entry we're deleting	*/
	prevEntry->next = curEntry->next;
	freeEntry(curEntry);


	return 0;
}

