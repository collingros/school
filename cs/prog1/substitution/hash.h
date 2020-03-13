/*!
	collin gros
	03/12/2020

	implements a hash table data structure in C, so that i may use it
	when scanning the dictionary file and analyzing words in
	getNumberOfWords()

	IMPORTANT: with the way i set this up, this is very vulnerable to
			   errors. i just wanted a quick way to do this without having
			   to use some kind of data structure in C++ STL.

	sources used:
		[section 8.2]
		https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)
		HashTables.html?highlight=%2528CategoryAlgorithmNotes%2529

		https://stackoverflow.com/questions/4384359/
		quick-way-to-implement-dictionary-in-c
*/

#ifndef __HASH__
#define __HASH__

#include <stdlib.h>

/* some prime number to use with our hash function */
#define PRIME	97


/* node structure used within the hash table */
struct node {
	struct node *next;
	char *key;
	char *value;
};


/*
	dictionary structure used to represent our dict and contain info
	on the size and number of elements currently inserted
*/
struct dict {
	size_t size;
	struct node **table;
};


/*
	finds the node that contains 'key'

	returns a pointer to the requested node on success, otherwise NULL
*/
struct node *find(struct dict *myDict, char *key);


/*
	inserts a new node into the hash table with key: 'key' and value:
	'value'

	returns 0 on success, otherwise failure
*/
int insert(struct dict *myDict, char *key, char *value);


/*
	initializes a dictionary of size 'size'

	returns a pointer to it on success, otherwise NULL 
*/
struct dict *createDict(size_t size);


/* computes and returns the hash value for a given key */
size_t hash(char *key, size_t size);


#endif
