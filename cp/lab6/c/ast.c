/*!
	collin gros
	03/06/2020
*/

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"


ASTNode *ASTcreateNode(enum NODETYPE desiredType)
{
	ASTNode *p;
	p = (ASTNode *)(malloc(sizeof(struct ASTNodeType)));

	p->s1 = 0;
	p->s2 = 0;
	p->next = 0;
	p->Type = desiredType;

	/* assuming that the node is not an array */
	p->size = -1;

	printf("created a node!\n\taddr: %p\ts1: %p\ts2: %p\tnext:"
		   "%p\n", p, p->s1, p->s2, p->next);
	return p;
}

void prettyPrint(const char *msg, int numTabs)
{
	for (int i = 0; i < numTabs; ++i) {
		fprintf(stderr, "    ");
	}

	fprintf(stderr, "%s\n", msg);
}


void ASTprint(ASTNode *p, int level)
{
	if (p == NULL) {
		return;
	}

	if (level == 0) {
		fprintf(stderr, "START: ASTprint!\n");
	}

	char buf[100];
	switch (p->Type) {
		case VARDEC:
			sprintf(buf, "VARDEC: %s", p->name);
			prettyPrint(buf, level);

			break;
		case FUNDEC:
			// pump up the parameters first
			if (p->s1 == NULL) {
				fprintf(stderr, "(VOID)");
			}
			else {
				ASTprint(p->s1, level + 1);
			}

			ASTprint(p->s2, level + 1);
			break;

		case PARAM:
			break;

		case BLOCK:
			/* list of trees: need to recur */
			ASTprint(p->s1, level + 1);
			ASTprint(p->s2, level + 1);
			break;

		case MYWRITE:
			ASTprint(p->s1, level + 1);
			break;

		case MYNUM:
			/* print out the value */
			break;

		case EXPR:
			/* do a pre order print (print left and then right) */
			/* print operator (can be switch statement or a function) */


			ASTprint(p->s1, level + 1);
			ASTprint(p->s2, level + 1);
			break;

		default: fprintf(stderr, "ERROR: unknown type in ASTPrint!\n");
	}

	ASTprint(p->next, level);
}

