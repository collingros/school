/*	collin gros
	04/21/2020	*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "emit.h"


static int GLABEL = 0;	/*	global label counter	*/

char *CURR_FUNCTION = NULL;

char *genlabel()
{
	char buf[MAX_LABEL_SIZE];
	sprintf(buf, "_L%d", GLABEL++);


	char *s = strdup(buf);
	return s;
}


void ASTemitStrings(FILE *fp, ASTNode *p)
{
	if (p == NULL) {
		return;
	}

	if (p->Type == MYWRITE &&
		p->s1 == NULL) {
		fprintf(fp, "%s:\t.asciiz\t%s\n", p->label, p->name);
	}

	ASTemitStrings(fp, p->next);
	ASTemitStrings(fp, p->s1);
	ASTemitStrings(fp, p->s2);
}


void ASTemitGlobs(FILE *fp, ASTNode *p)
{
	if (p == NULL) {
		return;
	}

	if (p->Type == VARDEC &&
		p->sym->level == 0) {
		fprintf(fp, "%s:\t.space\t%d\n", p->name,
				p->sym->mysize * WSIZE);
	}

	ASTemitGlobs(fp, p->next);
	ASTemitGlobs(fp, p->s1);
	/*	no global vardecs on s2	*/
}


void ASTemitLine(FILE *fp, char *label, char *command, char *comment)
{
	if (strcmp(label, "") == 0) {
		fprintf(fp, "%s\t\t%s\t\t%s\n", label, command, comment);
	}
	else {
		fprintf(fp, "%s:\t\t%s\t\t%s\n", label, command, comment);
	}
}


void ASTemit(FILE *fp, ASTNode *p)
{
	if (p == NULL) {
		return;
	}

	switch(p->Type) {
		case VARDEC: /*	no code	*/
			break;
		case FUNDEC:
			ASTemitFunctionHead(fp, p);

			/*	block	*/
			ASTemit(fp, p->s2);

			ASTemitFunctionReturn(fp, NULL);
			break;
		case BLOCK:
			ASTemit(fp, p->s2);
			break;
		case MYWRITE:
			ASTemitWrite(fp, p);
			break;
		case MYREAD:
			ASTemitRead(fp, p);
			break;

		default: printf("ASTemit Type not implemented\n");
	}

	ASTemit(fp, p->next);
}


void ASTemitFunctionHead(FILE *fp, ASTNode *p)
{
	ASTemitLine(fp, p->name, "", "# start of function");

	CURR_FUNCTION = p->name;

	/*	build the stack pointer movement	*/
	char s[100];
	sprintf(s, "subu $a0, $sp, %d", p->sym->mysize * WSIZE);
	ASTemitLine(fp, "", s, "# adjust the stack for function setup");
	ASTemitLine(fp, "", "sw $sp, ($a0)", "");
	ASTemitLine(fp, "", "sw $ra, 4($a0)", "");
	ASTemitLine(fp, "", "move $sp, $a0", "# adjust the stack pointer");
	ASTemitLine(fp, "", "", "");
}


void ASTemitIdentifier(FILE *fp, ASTNode *p)
{
	char s[100];
	/*	if ID is a scalar	*/
	if (p->sym->isArray) {
		/*	if ID is global	*/
		if (p->sym->level == 0) {
			printf("global array: %s\n", p->name);
			/*	global stuff TODO	*/
		}
		/*	ID is local	*/
		else {
			printf("local array: %s\n", p->name);
			/*	TODO	*/
		}
	}
	/*	ID is an array	*/
	else {
		/*	if ID is global	*/
		if (p->sym->level == 0) {
			printf("global scalar: %s\n", p->name);
			/*	global stuff TODO	*/
		}
		/*	ID is local	*/
		else {
			printf("local scalar: %s\n", p->name);
			sprintf(s, "add $a0, $sp, %d", p->sym->offset * WSIZE);
			ASTemitLine(fp, "", s, "# id is a LOCAL SCALAR");
			ASTemitLine(fp, "", "", "");
		}
	}
}


void ASTemitExpr(FILE *fp, ASTNode *p)
{
	char s[100];
	/*	base cases: MYNUM */
	switch (p->Type) {
		case MYNUM: 
			sprintf(s, "li $a0, %d", p->value);
			ASTemitLine(fp, "", s, "# expression is a NUMBER");
			/*	base case - get the heck out of here	*/
			return;
			break;
		case BOOL:
			if (p->value) {
				ASTemitLine(fp, "", "li $a0, 1", "# expression is TRUE");
			}
			else {
				ASTemitLine(fp, "", "li $a0, 0", "# expression is FALSE");
			}
			return;
			break;
		case ID:
			ASTemitIdentifier(fp, p);
			/*	we know $a0 is the address of ID	*/
			ASTemitLine(fp, "", "lw $a0, ($a0)", "# fetch value for ID");
			return;
			break;
		case MYNOT:
		case CALL:
			printf("cases not implemented in emit expression\n");
			exit(1);
			break;
	}

	/*	expression is expr, deal with it recursively	*/
}


void ASTemitFunctionReturn(FILE *fp, ASTNode *p)
{
	if (p != NULL) {
		/*	explicit return	*/
		/*	we need to evaluate the expression	*/
		ASTemitExpr(fp, p); /*	leaves $a0 with the result	*/
	}
	/*	if it is NULL, with do nothing with $a0	*/

	/*	adjust activiation record back	*/
	ASTemitLine(fp, "", "", "");
	ASTemitLine(fp, "", "lw $ra, 4($sp)", "# restore RA");
	ASTemitLine(fp, "", "lw $sp, ($sp)", "# restore SP");
	ASTemitLine(fp, "", "", "");

	/*	we have to do things differently if it is main	*/
	if (strcmp(CURR_FUNCTION, "main") == 0) {
		/*	handl main returns	*/
		ASTemitLine(fp, "", "li $v0, 10", "# leave main program ");
		ASTemitLine(fp, "", "syscall", "# leave main ");
	}
	else {
		/*	every other function	*/
		/*	use JUMP to go back to where $ra references	*/
	}
}


void ASTemitWrite(FILE *fp, ASTNode *p)
{
	/*	if we have a string	*/
	if (p->s1 == NULL) {
		ASTemitLine(fp, "", "li $v0, 4", "# printing a string");

		char s[100];
		sprintf(s, "la $a0, %s", p->label);
		ASTemitLine(fp, "", s, "# printing the string by its label");

		ASTemitLine(fp, "", "syscall", "# system call for printing string");
	}
	/*	otherwise we have an expression	*/
	else {
		ASTemitExpr(fp, p->s1);
		ASTemitLine(fp, "", "li $v0, 1", "# printing a number");
		ASTemitLine(fp, "", "syscall", "# system call for print number");
	}

	ASTemitLine(fp, "", "", "");
}


void ASTemitRead(FILE *fp, ASTNode *p)
{
	ASTemitIdentifier(fp, p->s1);
	ASTemitLine(fp, "", "li $v0, 5", "# read a number from input");
	ASTemitLine(fp, "", "syscall", "# reading a number");
	ASTemitLine(fp, "", "sw $v0, ($a0)", "# store a read into mem location");
	ASTemitLine(fp, "", "", "");
}







