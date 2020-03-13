/*!
	collin gros
	03/12/2020
*/

#include "hash.h"

#include <string.h>
#include <stdio.h>


struct dict *createDict(size_t size)
{
	struct dict *myDict = malloc(sizeof(struct dict));
	/* if malloc failed.. */
	if (myDict == 0) {
		return NULL;
	}

	/* allocate space for every node we will have in our dict */
	myDict->table = malloc(sizeof(struct node *) * size);
	myDict->size = size;

	/* initialize all node pointers to be 0 */
	for (size_t i = 0; i < size; ++i) {
		myDict->table[i] = 0;
	}

	return myDict;
}


size_t hash(char *key, size_t size)
{
	size_t hashValue = 0;
	char *curChar;
	/* iterate every character in our string, and generate our hash value */
	for (curChar = key; *curChar != '\0'; ++curChar) {
		hashValue = *curChar + PRIME * hashValue;
	}

	/* we have our unique index for the hashed value! */
	size_t index = hashValue % size;
	return index;
}


struct node *find(struct dict *myDict, char *key)
{
	size_t keyIndex = hash(key, myDict->size);
	/* grab the node at keyIndex */
	struct node *n = myDict->table[keyIndex];

	/* if there is a node at this index */
	if (n != NULL) {
		/* if this node is what we're looking for */
		if (strcmp(n->key, key) == 0) {
			return n;
		}
	}

	/* we never found it! */
	return NULL;
}


int insert(struct dict *myDict, char *key, char *value)
{
	struct node *n = malloc(sizeof(struct node));
	/* malloc failed.. */
	if (n == 0) {
		return 1;
	}

	n->key = strdup(key);
	n->value = strdup(value);

	size_t keyIndex = hash(key, myDict->size);
	n->next = myDict->table[keyIndex];

	/* insert newly created node into the dictionary */
	myDict->table[keyIndex] = n;

	return 0;
}

