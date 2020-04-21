/*!
	collin gros
	03/06/2020

	create a parse tree by using YACC's production rules and semantic action
*/

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"


/*	getNODETYPE

	retrieve the string corresponding to the given nodetype and store it
	in buf

	success:
		returns 0
	failure:
		returns 1	*/
int getNODETYPE(enum NODETYPE nt, char *buf);


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


/*	prettyPrint

	print out things nicely	*/
void prettyPrint(const char *msg, int numTabs)
{
	for (int i = 0; i < numTabs; ++i) {
		fprintf(stderr, "    ");
	}

	fprintf(stderr, "%s\n", msg);
}


/*	ASTfollowNode

	follow a node down to it's last next pointer	*/
ASTNode *ASTfollowNode(ASTNode *node)
{
	/* follow the chain to the last node */
	while (node->next != NULL) {
		node = node->next;
	}

	return node;
}


/*	getNODETYPE

	retrieve the string corresponding to the given nodetype and store it
	in buf

	success:
		returns 0
	failure:
		returns 1	*/
int getNODETYPE(enum NODETYPE nt, char *buf)
{
	switch (nt) {
		case VARDEC:
			sprintf(buf, "%s", "VARDEC");
			break;
		case FUNDEC:
			sprintf(buf, "%s", "FUNDEC");
			break;
		case PARAM:
			sprintf(buf, "%s", "PARAM");
			break;
		case BLOCK:
			sprintf(buf, "%s", "BLOCK");
			break;
		case MYWRITE:
			sprintf(buf, "%s", "WRITE");
			break;
		case MYNUM:
			sprintf(buf, "%s", "NUM");
			break;
		case BOOL:
			sprintf(buf, "%s", "BOOL");
			break;
		case EXPR:
			sprintf(buf, "%s", "EXPR");
			break;
		case CALL:
			sprintf(buf, "%s", "CALL");
			break;
		case ID:
			sprintf(buf, "%s", "ID");
			break;
		case ASSIGN:
			sprintf(buf, "%s", "ASSIGN");
			break;
		case RETURN:
			sprintf(buf, "%s", "RETURN");
			break;
		case MYWHILE:
			sprintf(buf, "%s", "WHILE");
			break;
		case MYIF:
			sprintf(buf, "%s", "IF");
			break;
		case MYELSE:
			sprintf(buf, "%s", "ELSE");
			break;
		case MYREAD:
			sprintf(buf, "%s", "READ");
			break;
		case MYNOT:
			sprintf(buf, "%s", "NOT");
			break;
		default:
			fprintf(stderr, "ERROR: unknown datatype!\n");
			return 1;
	}

	return 0;
}


/*	getDATATYPE

	retrieve the string corresponding to the given datatype and store it
	in buf

	success:
		returns 0
	failure:
		returns 1	*/
int getDATATYPE(enum DATATYPE dt, char *buf)
{
	switch (dt) {
		case INTTYPE:
			sprintf(buf, "%s", "INT_T");
			break;
		case VOIDTYPE:
			sprintf(buf, "%s", "VOID_T");
			break;
		case BOOLEANTYPE:
			sprintf(buf, "%s", "BOOL_T");
			break;
		default:
			fprintf(stderr, "ERROR: unknown datatype!\n");
			return 1;
	}

	return 0;
}


/*	getOPERATOR
	
	retrieve the string corresponding to the given operator and store it
	in buf

	success:
		returns 0
	failure:
		returns 1	*/
int getOPERATOR(enum OPERATOR op, char *buf)
{
	switch (op) {
		case PLUS:
			sprintf(buf, "%s", "PLUS");
			break;
		case MINUS:
			sprintf(buf, "%s", "MINUS");
			break;
		case MULTIPLY:
			sprintf(buf, "%s", "MULTIPLY");
			break;
		case DIVIDE:
			sprintf(buf, "%s", "DIVIDE");
			break;
		case MYAND:
			sprintf(buf, "%s", "AND");
			break;
		case MYOR:
			sprintf(buf, "%s", "OR");
			break;
		case GT:
			sprintf(buf, "%s", "GT");
			break;
		case LT:
			sprintf(buf, "%s", "LT");
			break;
		case MYEQ:
			sprintf(buf, "%s", "EQ");
			break;
		case MYNEQ:
			sprintf(buf, "%s", "NEQ:");
			break;
		case MYGE:
			sprintf(buf, "%s", "GE");
			break;
		case MYLE:
			sprintf(buf, "%s", "LE");
			break;
		default:
			fprintf(stderr, "ERROR: unknown operator type!\n");
			return 1;
	}

	return 0;
}


void ASTprint(ASTNode *p, int level)
{
	if (p == NULL) {
		return;
	}

	char buf[100], nt[15], dt[15], op[15];
	getNODETYPE(p->Type, nt);
	switch (p->Type) {
		case VARDEC:
			getDATATYPE(p->dt, dt);

			/*	check if it's an array	*/
			if (p->size >= 0) {
				sprintf(buf, "%s: %s %s\tARRAY_SIZE: %d", nt, dt, p->name,
						p->size);
			}
			else {
				sprintf(buf, "%s: %s %s", nt, dt, p->name);
			}

			prettyPrint(buf, level);
			break;

		case FUNDEC:
			getDATATYPE(p->dt, dt);

			sprintf(buf, "%s: %s %s", nt, dt, p->name);
			prettyPrint(buf, level);

			/*	pump up the parameters first	*/
			if (p->s1 == NULL) {
				sprintf(buf, "PARAM: VOID");
				prettyPrint(buf, level);
			}
			else {
				ASTprint(p->s1, level + 1);
			}

			ASTprint(p->s2, level + 1);
			break;

		case PARAM:
			getDATATYPE(p->dt, dt);

			/*	check if it's an array, different from varDec because
				the array doesn't have a declared size in the parameter part
				of a funDec	*/
			if (p->size == 0) {
				sprintf(buf, "%s: %s %s\tARRAY", nt, dt, p->name);
			}
			else {
				sprintf(buf, "%s: %s %s", nt, dt, p->name);
			}

			prettyPrint(buf, level);
			break;

		case BLOCK:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			ASTprint(p->s1, level + 1);
			ASTprint(p->s2, level + 1);
			break;

		case MYWRITE:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print expression	*/
			if (p->s1 != NULL) {
				ASTprint(p->s1, level + 1);
			}
			/*	print string instead	*/
			else {
				printf("with the string %s\n", p->name);
				printf("and label: %s\n", p->label);
			}

			break;

		case MYNUM:
			sprintf(buf, "%s: %d", nt, p->value);
			prettyPrint(buf, level);
			break;

		case BOOL:
			sprintf(buf, "%s: %d", nt, p->value);
			prettyPrint(buf, level);
			break;

		case EXPR:
			getOPERATOR(p->op, op);
			sprintf(buf, "%s: %s", nt, op);
			prettyPrint(buf, level);

			/*	right side	*/
			ASTprint(p->s2, level + 1);
			/*	left side	*/
			ASTprint(p->s1, level + 1);
			break;

		case CALL:
			sprintf(buf, "%s: %s", nt, p->name);
			prettyPrint(buf, level);

			/*	print arguments	*/
			ASTprint(p->s1, level + 1);
			break;

		case ID:
			sprintf(buf, "%s: %s", nt, p->name);
			prettyPrint(buf, level);
			if (p->s1 != NULL) {
			/*	print expr	*/
				sprintf(buf, "%s", "BEGIN_ARRAY_REFERENCE_[");
				prettyPrint(buf, level);

				ASTprint(p->s1, level + 1);

				sprintf(buf, "%s", "END_ARRAY_REFERENCE_]");
				prettyPrint(buf, level);
			}

			break;

		case ASSIGN:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print var being assigned to	*/
			ASTprint(p->s1, level + 1);
			/*	print expr	*/
			ASTprint(p->s2, level + 1);
			break;

		case RETURN:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print what we're returning	*/
			ASTprint(p->s1, level + 1);
			break;

		case MYWHILE:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print the expr	*/
			ASTprint(p->s1, level + 1);
			/*	print the stmt	*/
			ASTprint(p->s2, level + 1);
			break;
		
		case MYIF:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print the expr	*/
			ASTprint(p->s1, level + 1);
			/*	print the else (will print stmt)	*/
			ASTprint(p->s2, level + 1);
			break;

		case MYELSE:
			/*	print if stmt	*/
			ASTprint(p->s1, level + 1);

			/*	print the else stmt	*/
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);
			ASTprint(p->s2, level + 1);

			break;

		case MYREAD:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print the var	*/
			ASTprint(p->s1, level + 1);
			break;

		case MYNOT:
			sprintf(buf, "%s", nt);
			prettyPrint(buf, level);

			/*	print the assoc. factor	*/
			ASTprint(p->s1, level + 1);
			break;

		default: fprintf(stderr, "ERROR: unknown type in ASTPrint!\n");
	}

	ASTprint(p->next, level);
}

