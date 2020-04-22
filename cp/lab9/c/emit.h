/*	collin gros
	04/21/2020

	emit.h	*/

#ifndef __EMIT__
#define __EMIT__


#include "ast.h"
#include "symtable.h"

#define WSIZE 4	/*	num bytes in word	*/
#define LOGWSIZE 2	/*	num shifts to get to WSIZE	*/
#define MAX_LABEL_SIZE 100	/* maximum length a label name can be	*/


/*	generate labels of the form L_{GLABEL} and return it, remember to
free it!	*/
char *genlabel();

/*	prints all of the strings in MIPS format, returns
	nothing	*/
void ASTemitStrings(FILE *fp, ASTNode *p);

/*	prints all of the global vars in MIPS format,
	returns nothing	*/
void ASTemitGlobs(FILE *fp, ASTNode *p);

#endif

