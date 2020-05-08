/*	collin gros
	04/21/2020

	takes ASTNodes and prints their meaningful code into a file (in MIPS)	*/

#ifndef __EMIT__
#define __EMIT__


#include "ast.h"
#include "symtable.h"

#define WSIZE 4	/*	num bytes in word	*/
#define LOG_WSIZE 2	/*	num shifts to get to WSIZE	*/
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

/*	emit the function's return implicitly or explicitly in MIPS code to fp,
		p is a pointer to an expression or NULL

		returns nothing, but prints MIPS code to fp	*/
void ASTemitFunctionReturn(FILE *fp, ASTNode *p);

/*	gets a pointer to a MYREAD node and prints MIPS code for read in fp,
	returns nothing	*/
void ASTemitRead(FILE *fp, ASTNode *p);

/*	prints MIPS code for write in fp, p is a pointer to a MYWRITE node,
	returns nothing	*/
void ASTemitWrite(FILE *fp, ASTNode *p);

/*	takes a pointer to an expression in YACC (p) and prints MIPS code that
	sets $a0 to the value of it, returns nothing.	*/
void ASTemitExpr(FILE *fp, ASTNode *p);

/*	p is a pointer to an ID node, and prints MIPS code such that $a0 is the
	address of where ID is in memory, returns nothing	*/
void ASTemitIdentifier(FILE *fp, ASTNode *p);

/*	p is a pointer to an ASSIGN node, does assignment using $a0, returns
	nothing	*/
void ASTemitAssignment(FILE *fp, ASTNode *p);

/*	p is a pointer to a MYIF node, prints MIPS code for If statatement,
	returns nothing	*/
void ASTemitIf(FILE *fp, ASTNode *p);

/*	p is a pointer to a MYWHILE node, prints MIPS code for While statement,
	returns nothing	*/
void ASTemitWhile(FILE *fp, ASTNode *p);

#endif

