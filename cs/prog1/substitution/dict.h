/*
	collin gros
	03/23/2020

	a dictionary structure for use with the substitution cipher problem

	heavily referenced:
		https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html
		highlight=%2528CategoryAlgorithmNotes%2529
*/

#ifndef __DICT_H_
#define __DICT_H_

#define HASH_MULTIPLIER	31

struct entry {
	char *key;
	char *val;
	struct entry *next;
};

struct dict {
	int size;
	int n;
	struct entry **table;
};


/*	create a dictionary of size 'size' 

	returns a pointer to the dictionary that is created	*/
struct dict *dictCreate(int size);


/*	delete a dictionary pointed to by 'myDict'

	returns 0 for success, otherwise failure	*/
int dictDestroy(struct dict *myDict);


/*	insert an entry into the dictionary pointed to by 'myDict'

	returns 0 for success, otherwise failure	*/
int dictInsert(struct dict *myDict, const char *key, const char *val);


/*	searches the dictionary for a particular key

	returns a pointer to the entry, if found, and a NULL pointer otherwise	*/
struct entry *dictSearch(struct dict *myDict, const char *key);


#endif
