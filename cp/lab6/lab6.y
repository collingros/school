%{
/*
	collin gros
	02/28/20 - 03/29/2020

	YACC program for handling code in 'Extended BNF Grammar for C-Algol'
	format.

	all rules were copied from lab 5, though some bugs were found and fixed:

		in the 'call' rule. 'var' was originally VARIABLE, which was just
		a token instead of the actual production rule 'var'.

		in the 'argsList' rule, i didn't use '0 or more times' which made
		it so you couldn't have more than 2 arguments in a call...


	i added semantic action for every production rule, and created c-code
	to generate a parse tree.

	it seems like the PLUS and MINUS operations are computed backwards, which
	might be caused by my use of a while loop instead of a recursive function,
	but i hope that won't affect anything.

	the VARIABLE token might seem confusing, but it is equivalent to 'ID'.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "c/ast.h"

#define MAX_SIZE 3


ASTNode *globalTreePointer = 0;

int yylex();
extern int linecount;

void yyerror (s)	/* Called by yyparse on error */
	 char *s;
{
	fprintf (stderr, "%s on line %d\n", s, linecount);
}
%}


%start program

%union
{
	int number;
	char *string;
	enum DATATYPE datatype;
	enum OPERATOR op;
	struct ASTNodeType *node;
}

%token	INT VOID BOOLEAN MYBEGIN END IF THEN ELSE WHILE DO
		MYRETURN READ WRITE AND OR TRUE FALSE NOT LE GE EQ
		NEQ
%token <number> NUMBER;
%token <string> VARIABLE;

%type <node>	varList varDec dec decList funDec params paramList param
				compoundStmt stmtList stmt localDec writeStmt expr
				simpleExpr additiveExpr term factor args argList call var
				assignmentStmt exprStmt iterationStmt returnStmt readStmt
				selectionStmt

%type <datatype> typeSpec 
%type <op> addop multop relop

%%
/* program -> declaration-list */
program	: decList {
			globalTreePointer = $1;
		}
		;

/* declaration-list -> declaration { declaration } */
decList	: dec {
			$$ = $1;
		}
		| dec decList {
			ASTNode *last = ASTfollowNode($1);
			/* append the other decList to the end of the last node
			   in this node's next chain */
			last->next = $2;

			$$ = $1;
		}
		;

/* declaration -> var-declaration | fun-declaration */
dec	: varDec {
		$$ = $1;
	}
	| funDec {
		$$ = $1;
	}
	;

/* var-declaration -> type-specifier var-list ; */
varDec	: typeSpec varList ';' {
			$$ = $2;
			$$->dt = $1;
		}
		;

/* var-list -> ID | ID [ NUM ] | ID , var-list | ID [ NUM ] , var-list */
varList	: VARIABLE {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
		}
		| VARIABLE '[' NUMBER ']' {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;

			/* default is -1, indicating the
			   variable is NOT an array */
			$$->size = $3;
		}
		| VARIABLE ',' varList {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $3;
		}
		| VARIABLE '[' NUMBER ']' ',' varList {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $6;

			/* default is -1, indicating the
			   variable is NOT an array */
			$$->size = $3;
		}
		;

/* type-specifier -> int | void | boolean */
typeSpec	: INT {
				$$ = INTTYPE;
			}
			| VOID {
				$$ = VOIDTYPE;
			}
			| BOOLEAN {
				$$ = BOOLEANTYPE;
			}
			;

/* fun-declaration -> type-specifier ID ( params ) compound-stmt */
funDec	: typeSpec VARIABLE '(' params ')' compoundStmt {
			$$ = ASTcreateNode(FUNDEC);
			$$->name = $2;
			$$->dt = $1;
			$$->s1 = $4;
			$$->s2 = $6;
		}
		;

/* params -> void | param-list */
params	: VOID {
			$$ = NULL;
		}
		| paramList {
			$$ = $1;
		}
		;

/* param-list -> param { , param } */
paramList	: param {
				$$ = $1;
			}
			| param ',' paramList {
				ASTNode *last = ASTfollowNode($1);
				/* append the other decList to the end of the last node
				   in this node's next chain */
				last->next = $3;

				$$ = $1;
			}
			;

/* param -> type-specifier ID [ [] ] */
param	: typeSpec VARIABLE '[' ']' {
			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;

			/* this is an array, so to signify that we set size to 0 (we
			   don't know the size, only that the variable is an array) */
			$$->size = 0;
		}
		| typeSpec VARIABLE {
			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;
		}
		;

/* compound-stmt -> begin local-declarations statement-list end */
compoundStmt	: MYBEGIN localDec stmtList END {
					$$ = ASTcreateNode(BLOCK);
					$$->s1 = $2;
					$$->s2 = $3;
				}
				;

/* local-declarations -> { var-declarations } */
localDec	: /* empty */ {
				$$ = NULL;
			}
			| varDec localDec  {
				if ($1 == NULL) {
					$$ = $2;
				}
				else {
					ASTNode *last = ASTfollowNode($1);
					/* append the other decList to the end of the last node
					   in this node's next chain */
					last->next = $2;

					$$ = $1;
				}
			}
			;

/* statement-list -> { statement } */
stmtList	: /* empty */ {
				$$ = NULL;
			}
			| stmt stmtList {
				if ($1 == NULL) {
					$$ = $2;
				}
				else {
					ASTNode *last = ASTfollowNode($1);
					/* append the other decList to the end of the last node
					   in this node's next chain */
					last->next = $2;

					$$ = $1;
				}
			}
			;

/* statement -> expression-stmt | compount-stmt | selection-stmt
				| iteration-stmt | assignment-stmt | return-stmt
				| read-stmt | write-stmt */
stmt	: exprStmt {
			$$ = $1;
		}
		| compoundStmt {
			$$ = $1;
		}
		| selectionStmt {
			$$ = $1;
		}
		| iterationStmt {
			$$ = $1;
		}
		| assignmentStmt {
			$$ = $1;
		}
		| returnStmt {
			$$ = $1;
		}
		| readStmt {
			$$ = $1;
		}
		| writeStmt {
			$$ = $1;
		}
		;

/* expression-stmt -> expression ; | ; */
exprStmt	: expr ';' {
				$$ = $1;
			}
			| ';' {
				$$ = NULL;
			}
			;

/* selection-stmt -> if expression then statement [ else statement ]+ */
selectionStmt	: IF expr THEN stmt {
					$$ = ASTcreateNode(MYIF);
					$$->s1 = $2;

					ASTNode *elseNode = ASTcreateNode(MYELSE);
					/*	the stmt in the IF	*/
					elseNode->s1 = $4;
					/*	the stmt in the ELSE	*/
					elseNode->s2 = NULL;

					$$->s2 = elseNode;
				}
				| IF expr THEN stmt ELSE stmt {
					$$ = ASTcreateNode(MYIF);
					$$->s1 = $2;

					ASTNode *elseNode = ASTcreateNode(MYELSE);
					/*	the stmt in the IF	*/
					elseNode->s1 = $4;
					/*	the stmt in the ELSE	*/
					elseNode->s2 = $6;

					$$->s2 = elseNode;
				}
				;

/* iteration-stmt -> while expressino do statement */
iterationStmt	: WHILE expr DO stmt {
					$$ = ASTcreateNode(MYWHILE);
					$$->s1 = $2;
					$$->s2 = $4;
				}
				;

/* return-stmt -> return [ expressinon ]+ */
returnStmt	: MYRETURN ';' {
				$$ = ASTcreateNode(RETURN);
			}
			| MYRETURN expr ';' {
				$$ = ASTcreateNode(RETURN);
				$$->s1 = $2;
			}
			;

/* read-stmt -> read variable; */
readStmt	: READ var ';' {
				$$ = ASTcreateNode(MYREAD);
				$$->s1 = $2;
			}
			;

/* write-stmt -> write expr; */
writeStmt	: WRITE expr ';' {
				$$ = ASTcreateNode(MYWRITE);
				$$->s1 = $2;
			}
			;

/* assignment-stmt -> var = simple-expression; */
assignmentStmt	: var '=' simpleExpr ';' {
					$$ = ASTcreateNode(ASSIGN);
					$$->s1 = $1;
					$$->s2 = $3;
				}
				;

/* expression -> simple-expression; */
expr	: simpleExpr {
			$$ = $1;
		}
		;

/* var -> ID [ [ expression ] ]+ */
/* NOTE: we aren't dealing with multi dimensional arrays */
var	: VARIABLE {
		$$ = ASTcreateNode(ID);
		$$->name = $1;
	}
	| VARIABLE '[' expr ']' {
		$$ = ASTcreateNode(ID);
		$$->name = $1;
		/*	an VARIABLE node's s1 points to its expression	*/
		$$->s1 = $3;
	}
	;

/* simple-expression -> additive-expression [ relop additive-expression ]+
   */
simpleExpr	: additiveExpr {
				$$ = $1;
			}
			| simpleExpr relop additiveExpr {
				$$ = ASTcreateNode(EXPR);
				$$->s1 = $1;
				$$->op = $2;
				$$->s2 = $3;
			}
			;

/* relop -> <= | < | > | >= | == | != */
relop	: LE {
			$$ = MYLE;
		}
		| '<' {
			$$ = GT;
		}
		| '>' {
			$$ = LT;
		}
		| GE {
			$$ = MYGE;
		}
		| EQ {
			$$ = MYEQ;
		}
		| NEQ {
			$$ = MYNEQ;
		}
		;

/* additive-expression -> term { addop term } */
additiveExpr	: term {
					$$ = $1;
				}
				| term addop additiveExpr  {
					/* all of our multi-expr stuff is EXPR */
					$$ = ASTcreateNode(EXPR);
					$$->s1 = $1;
					$$->op = $2;
					$$->s2 = $3;
				}
				;

/* addop -> + | - */
addop	: '+' {
			$$ = PLUS;
		}
		| '-' {
			$$ = MINUS;
		}
		;

/* term -> factor { multop factor } */
term	: factor {
			$$ = $1;
		}
		| factor multop term {
			/* all of our multi-expr stuff is EXPR */
			$$ = ASTcreateNode(EXPR);
			$$->s1 = $1;
			$$->op = $2;
			$$->s2 = $3;
		}
		;

/* multop -> factor { multop factor } */
multop	: '*' {
			$$ = MULTIPLY;
		}
		| '/' {
			$$ = DIVIDE;
		}
		| AND {
			$$ = MYAND;
		}
		| OR {
			$$ = MYOR;
		}
		;

/* factor -> ( expression ) | NUM | var | call | TRUE | FALSE | NOT factor
   */
factor	: '(' expr ')' {
			$$ = $2;
		}
		| NUMBER {
			$$ = ASTcreateNode(MYNUM);
			$$->value = $1;
		}
		| var {
			$$ = $1;
		}
		| call {
			$$ = $1;
		}
		| TRUE {
			$$ = ASTcreateNode(BOOL);
			$$->value = 1;
		}
		| FALSE {
			$$ = ASTcreateNode(BOOL);
			$$->value = 0;
		}
		| NOT factor {
			/*	NOT is only defined on boolean types, this will NOT throw an
				error yet if factor is not a boolean...	*/
			$$ = $2;
			$$->value = !($$->value);
		}
		;

/* call -> ID ( args ) */
call	: VARIABLE '(' args ')' {
			$$ = ASTcreateNode(CALL);
			$$->name = $1;
			$$->s1 = $3;
		}
		;

/* args -> arg-list | empty */
args	: /* empty */ {
			$$ = NULL;
		}
		| argList {
			$$ = $1;
		}
		;

/* argList -> expression { , expression } */
argList	: expr {
			$$ = $1;
		}
		| expr ',' argList {
			ASTNode *last = ASTfollowNode($1);
			/* append the other decList to the end of the last node
			   in this node's next chain */
			last->next = $3;

			$$ = $1;
		}
		;
%%

int main(int argc, char** argv)
{
	if (yyparse()) {
		fprintf(stderr, "yyparse() failed!\n");
		exit(1);
	}
	printf("yyparse() was successful!\n");

	if (globalTreePointer == 0) {
		fprintf(stderr, "ERROR: globalTreePointer points to null!\n");
		exit(1);
	}

	// print out
	ASTprint(globalTreePointer, 0);

	exit(0);
}
