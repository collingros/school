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
		case ASSIGN:
			ASTemitAssignment(fp, p);
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


void ASTemitAssignment(FILE *fp, ASTNode *p)
{
	char s[100];

	ASTemitIdentifier(fp, p->s1);

	sprintf(s, "sw $a0, %d($sp)", p->sym->offset * WSIZE);
	ASTemitLine(fp, "", s, "# moving up to p for our assignment");

	ASTemitExpr(fp, p->s2);

	sprintf(s, "lw $t0, %d($sp)", p->sym->offset * WSIZE);
	ASTemitLine(fp, "", s, "# loaded expression to prepare for assignment");

	ASTemitLine(fp, "", "sw $a0, ($t0)", "# assignment");
	ASTemitLine(fp, "", "", "");
}


void ASTemitIf(FILE *fp, ASTNode *p)
{
	char *L1, *L2;
	L1 = genlabel();
	L2 = genlabel();

	char s[100];
	ASTemitExpr(fp, p->s1);
	/*	$a0 now has the expr s1 in it (the conditional)	*/
	ASTemitLine(fp, "", "ldi $t0, 0", "# set $t0 to 0");

	/*	jmp to else if they're both 0	*/
	sprintf(s, "breq $a0, $t0, %s", L1);
	ASTemitLine(fp, "", s, "# if they're both 0 we want to jump to else");

	/*	emit the positive part of if	*/
	ASTemit(fp, p->s2->s1);
	sprintf(s, "jmp %s", L2);
	ASTemitLine(fp, "", s, "# end of if statement");

}


void ASTemitIdentifier(FILE *fp, ASTNode *p)
{
	char s[100];
	/*	if ID is a scalar	*/
	if (p->sym->isArray) {
		/*	if ID is global	*/
		if (p->sym->level == 0) {
			/*	get the desired index in $a0	*/
			ASTemitExpr(fp, p->s1);
			ASTemitLine(fp, "", "move $a1, $a0", "# move specified index to "
						"$a1");

			/*	load address of array into $a0	*/
			sprintf(s, "la $a0, %s", p->name);
			ASTemitLine(fp, "", s, "# id is a GLOBAL ARRAY");
			sprintf(s, "add $a0, $sp, %d", p->sym->offset * WSIZE);
			ASTemitLine(fp, "", s, "# add offset to $a0");

			/*	add the two	*/
			ASTemitLine(fp, "", "add $a0, $a0, $a1", "# add index to (array + "
						"offset");
			ASTemitLine(fp, "", "", "");
		}
		/*	ID is local	*/
		else {
			sprintf(s, "add $a0, $sp, %d", p->sym->offset * WSIZE);
			ASTemitLine(fp, "", s, "# id is a LOCAL ARRAY");
			ASTemitLine(fp, "", "", "");
		}
	}
	/*	ID is an array	*/
	else {
		/*	if ID is global	*/
		if (p->sym->level == 0) {
			/*	global var has a label	*/
			sprintf(s, "la $a0, %s", p->name);
			ASTemitLine(fp, "", s, "# id is a GLOBAL SCALAR");
			ASTemitLine(fp, "", "", "");
		}
		/*	ID is local	*/
		else {
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
		case CALL:
			ASTemitLine(fp, "", "", "# function call");
			/*	shouldn't p->name be a label?	*/
			sprintf(s, "jal %s", p->name);
			ASTemitExpr(fp, p->s1);
			return;
			break;
	}

	/*	expression is expr, deal with it recursively	*/
	/*	evaluate s1, store s1 in p->sym->offset (sw a0 %d($sp))
		evaluate s2, move $a0 to $a1 (copies RHS to A1)
		load $a0 with p->sym->offset (lw a0 %d($sp))
		perform calculation (add a0 a0 a1)	*/
	/*	evaluating LHS	*/
	char buf[100];

	getNODETYPE(p->Type, buf);
	ASTemitExpr(fp, p->s1);

	/*	if our expression is a NOT expression, we don't deal with a RHS	*/
	/*	if p->s2 == NULL, the expr is a NOT expr	*/
	if (p->s2 != NULL) {
		sprintf(s, "sw $a0, %d($sp)", p->sym->offset * WSIZE);
		ASTemitLine(fp, "", s, "# store s1 in temp");


		/*	evaluating RHS	*/
		ASTemitExpr(fp, p->s2);
		printf("after s2\n");
		ASTemitLine(fp, "", "move $a1, $a0", "# moving expr1 out of the way");
		sprintf(s, "lw $a0, %d($sp)", p->sym->offset * WSIZE);
		ASTemitLine(fp, "", s, "# put temp in $a0");

		/*	at this point: the expr p->s1 is in $a0 and p->s2 is in $a1	*/
	}

	switch(p->op) {
		case PLUS:
			ASTemitLine(fp, "", "add $a0, $a0, $a1", "# expr PLUS");
			break;
		case MINUS:
			ASTemitLine(fp, "", "sub $a0, $a0, $a1", "# expr MINUS");
			break;
		case MYAND:
			ASTemitLine(fp, "", "and $a0, $a0, $a1", "# expr AND");
			break;
		case MYOR:
			ASTemitLine(fp, "", "or $a0, $a0, $a1", "# expr OR");
			break;
		case MULTIPLY:
			ASTemitLine(fp, "", "mult $a0, $a1", "# expr MULTIPLY");
			ASTemitLine(fp, "", "mflo $a0", "# expr MULTIPLY");
			break;
		case DIVIDE:
			ASTemitLine(fp, "", "div $a0, $a1", "# expr DIVIDE");
			ASTemitLine(fp, "", "mflo $a0", "# expr DIVIDE");
			break;
		case MYLE:
			ASTemitLine(fp, "", "sle $a0, $a0, $a1", "# expr <=");
			break;
		case MYGE:
			ASTemitLine(fp, "", "sge $a0, $a0, $a1", "# expr >=");
			break;
		case MYEQ:
			ASTemitLine(fp, "", "seq $a0, $a0, $a1", "# expr ==");
			break;
		case MYNEQ:
			ASTemitLine(fp, "", "sne $a0, $a0, $a1", "# expr !=");
			break;
		case LT:
			ASTemitLine(fp, "", "slt $a0, $a0, $a1", "# expr <");
			break;
		case GT:
			ASTemitLine(fp, "", "sgt $a0, $a0, $a1", "# expr >");
			break;
		case MYNOT:
			ASTemitLine(fp, "", "sltiu $a0, $a0, 1", "# expr !");
			break;
		case MYLE:
			ASTemitLine(fp, "", "slt $t0, $a0, $a1", "# expr < (<=)");
			ASTemitLine(fp, "", "seq $t1, $a0, $a1", "# expr == (<=)");
			ASTemitLine(fp, "", "or $a0, $t0, $t1", "# expr OR (>=)");
			break;
		case MYGE:
			ASTemitLine(fp, "", "sgt $t0, $a0, $a1", "# expr > (>=)");
			ASTemitLine(fp, "", "seq $t1, $a0, $a1", "# expr == (>=)");
			ASTemitLine(fp, "", "or $a0, $t0, $t1", "# expr OR (>=)");
			break;
	}

	ASTemitLine(fp, "", "", "");
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







