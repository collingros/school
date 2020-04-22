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

/*	given three strings, print them out in assembly format in fp, returns
	nothing

	example:	emit(fp, "L1", "ldi R13, 15", "#load a number"
				out: L1:	ldi R15, 15 #load number	*/
void ASTemitLine(FILE *fp, char *label, char *command, char *comment);

/*	takes an AST tree and outputs MIPS code in fp, returns nothing	*/
void ASTemit(FILE *fp, ASTNode *p);

/*	writes the header code in MIPS to fp, returns nothing	*/
void ASTemitFunctionHead(FILE *fp, ASTNode *p);

/*	emit the function's return (implicitly) in MIPS code to fp, returns
	nothing	*/
void ASTemitFunctionReturn(FILE *fp, ASTNode *p);

void ASTemitWrite(FILE *fp, ASTNode *p);

#endif

