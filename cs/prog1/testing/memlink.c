/*
	collin gros
	03/25/2020

	small test to see if dict.c has any memleaks
*/

#include "dict.h"
#include "decrypt_helper.h"

#define DICTIONARY_FILE	"dictionary.txt"


int main()
{
	struct dict *myDict = getDictFromDictionaryFile(DICTIONARY_FILE);

	dictDestroy(myDict);
}
