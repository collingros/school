/*
	collin gros
	03/23/2020

	tests the dictionary code
*/

#include <stdio.h>

#include "dict.h"


int main()
{
	struct dict *myDict = dictCreate(100);
	int errors = dictInsert(myDict, "COLLINLIKESABIGWEINER", "GROS");
	errors += dictInsert(myDict, "AMANDA", "GROS");
	errors += dictInsert(myDict, "BROOKE", "PAYTON");

	struct entry *foundEntry = dictSearch(myDict, "BROOKE");
	if (foundEntry == NULL) {
		printf("entry DNE!\n");
	}
	else {
		printf("foundEntry val: %s\n", foundEntry->val);
	}

	errors += dictDelete(myDict, "AMANDA");
	errors += dictDestroy(myDict);


	printf("number of errors: %d\n", errors);
}
