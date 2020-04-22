/*	collin gros
	04/21/2020	*/


#include <string.h>
#include <stdio.h>

#include "emit.h"


static int GLABEL = 0;	/*	global label counter	*/


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

