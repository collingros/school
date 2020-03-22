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

	/* assuming that the node is NOT an array (change this at the moment
	   the node is created in YACC if it IS an array) */
	p->size = -1;

	return p;
}

void prettyPrint(const char *msg, int numTabs)
{
	for (int i = 0; i < numTabs; ++i) {
		fprintf(stderr, "    ");
	}

	fprintf(stderr, "%s\n", msg);
}


ASTNode *ASTfollowNode(ASTNode *node)
{
	/* follow the chain to the last node */
	while (node->next != NULL) {
		node = node->next;
	}

	return node;
}


void ASTprint(ASTNode *p, int level)
{
	if (p == NULL) {
		return;
	}

	char buf[100];
	switch (p->Type) {
		case VARDEC:
			sprintf(buf, "VARDEC: %s", p->name);
			prettyPrint(buf, level);

			break;

		case FUNDEC:
			sprintf(buf, "FUNDEC: %s", p->name);
			prettyPrint(buf, level);

			// pump up the parameters first
			if (p->s1 == NULL) {
				sprintf(buf, "PARAM: (VOID)");
				prettyPrint(buf, level);
			}
			else {
				ASTprint(p->s1, level + 1);
				ASTprint(p->s2, level + 1);
			}

			break;

		case PARAM:
			sprintf(buf, "PARAM: %s", p->name);
			prettyPrint(buf, level);

			break;

		case BLOCK:
			/* list of trees: need to recur */
			ASTprint(p->s1, level + 1);
			ASTprint(p->s2, level + 1);
			break;

		case MYWRITE:
			sprintf(buf, "MWRITE!\n");
			prettyPrint(buf, level);
			ASTprint(p->s1, level + 1);
			break;

		case MYNUM:
			sprintf(buf, "NUM: %d\n", p->value);
			prettyPrint(buf, level);
			break;

		case EXPR:
			sprintf(buf, "EXPR\n");
			prettyPrint(buf, level);

			/* left side */
			ASTprint(p->s1, level + 1);
			/* print the operator */
			switch (p->op) {
				case PLUS:
					fprintf(stderr, " + ");
					break;
				case MINUS:
					fprintf(stderr, " - ");
					break;
				default:
					fprintf(stderr, "ERROR: unknown type in OPERATORS!\n");
			}
			/* right side */
			ASTprint(p->s2, level + 1);

			break;

		default: fprintf(stderr, "ERROR: unknown type in ASTPrint!\n");
	}

	ASTprint(p->next, level);
}

