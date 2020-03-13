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

	printf("created a node!\n\taddr: %p\ts1: %p\ts2: %p\tnext:"
		   "%p\n", p, p->s1, p->s2, p->next);
	return p;
}

void printTabs (int numTabs)
{
	for (int i = 0; i < numTabs; ++i) {
		printf("\t");
	}
}


void ASTprint(ASTNode *p, int level)
{
	if (p == NULL) {
		printf("\n");
		return;
	}
	printf("level: %d\n", level);

	printTabs(level);
	if (level == 0) {
		fprintf(stderr, "START: ASTprint!\n");
	}

	// for pretty printing of messages
	char buf[100];
	switch (p->Type) {
		case VARDEC:
			fprintf(stderr, "VARDEC: %s\n", p->name);
			// print child nodes of this node
			ASTprint(p->next, level + 1);
			break;

		default: fprintf(stderr, "ERROR: unknown type in ASTPrint!\n");
	}
}

