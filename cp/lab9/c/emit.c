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
}


void ASTemitFunctionReturn(FILE *fp, ASTNode *p)
{
	/*	adjust activiation record back	*/
	ASTemitLine(fp, "", "", "");
	ASTemitLine(fp, "", "lw $ra, 4($a0)", "# restore RA");
	ASTemitLine(fp, "", "lw $sp, 4($sp)", "# restore RA");
	ASTemitLine(fp, "", "", "");

	/*	we have to do things differently if it is main	*/
	if (strcmp(CURR_FUNCTION, "main") == 0) {
		/*	handl main returns	*/
		ASTemitLine(fp, "", "li $v0, 10", "# leave main program ");
		ASTemitLine(fp, "", "syscall", "# leave main ");
	}
	else {
		/*	every other function	*/
	}
}


void ASTemitWrite(FILE *fp, ASTNode *p)
{

}









