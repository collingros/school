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
	return p;
}


void prettyPrint (const char *msg, int numTabs)
{
	fprintf(stderr, "\t%s\n", msg);
}


void ASTprint(ASTNode *p, int level)
{
	if (p == NULL) {
		return;
	}
	if (level == 0) {
		fprintf(stderr, "START: ASTprint!\n");
	}

	// for pretty printing of messages
	char buf[100];
	switch (p->Type) {
		case VARDEC:

			// 03/06/2020
			// TODO: prettyPrint! use sprintf to store a msg into buf,
			// and do a prettyPrint using buf and level!

			// print child nodes of this node
			ASTprint(p->s1, level + 1);
			ASTprint(p->s2, level + 1);
			break;

		default: fprintf(stderr, "ERROR: unknown type in ASTPrint!\n");
	}
}

