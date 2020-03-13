%{
/*
	collin gros
	02/28/20

	YACC program for handling code in 'Extended BNF Grammar for C-Algol'
	format.

	all rules were copied from the above grammar.

	NOTE: can't handle any semantics yet, only syntax
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

%token INT VOID BOOLEAN MYBEGIN END IF THEN ELSE WHILE DO MYRETURN
%token READ WRITE AND OR TRUE FALSE NOT LE GE EQ NEQ
%token <number> NUMBER;
%token <string> VARIABLE;

%type <node> varList varDec dec decList funDec
%type <node> params paramList param
%type <node> compoundStmt stmtList stmt localDec writeStmt
%type <node> expr simpleExpr additiveExpr term factor

%type <datatype> typeSpec 
%type <op> addop

%%
/* program -> declaration-list */
program	: decList {
			globalTreePointer = $1;
		}
		;

/* declaration-list -> declaration { declaration } */
decList	: dec {
			printf("declaration!\n");
			printf("\t$1: %p\n", $1);
			$$ = $1;
		}
		| dec decList {
			/* chain the declaration to the other declarations */
			printf("decl list!\n");
			$1->next = $2;
			printf("\tname: %s\tname: %s\n", $1->name, $2);
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
		}
		;

/* var-list -> ID | ID [ NUM ] | ID , var-list | ID [ NUM ] , var-list */
varList	: VARIABLE {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			printf("\tname: %s\n", $$->name);
		}
		| VARIABLE '[' NUMBER ']' {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			printf("\tname: %s\n", $$->name);
		}
		| VARIABLE ',' varList {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $3;
			printf("\tname: %s\tnext: %s\n", $$->name, $3->name);
		}
		| VARIABLE '[' NUMBER ']' ',' varList {
			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $6;
			printf("\tname: %s\tnext: %s\n", $$->name, $6->name);
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
				$1->next = $3;
				$$ = $1;
			}
			;

/* param -> type-specifier ID [ [] ] */
param	: typeSpec VARIABLE '[' ']' {
			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;
			$$->size = 0;
		}
		| typeSpec VARIABLE {
			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;
			$$->size = -1;
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
					$1->next = $2;
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
					$1->next = $2;
					$$ = $1;
				}
			}
			;

/* statement -> expression-stmt | compount-stmt | selection-stmt
				| iteration-stmt | assignment-stmt | return-stmt
				| read-stmt | write-stmt */
stmt	: exprStmt {
			/* WILL EVENTUALLY WRITE $$ = $1 */
			$$ = NULL;
		}
		| compoundStmt {
			$$ = $1;
		}
		| selectionStmt {
			$$ = NULL;
		}
		| iterationStmt {
			$$ = NULL;
		}
		| assignmentStmt {
			$$ = NULL;
		}
		| returnStmt {
			$$ = NULL;
		}
		| readStmt {
			$$ = NULL;
		}
		| writeStmt {
			$$ = $1;
		}
		;

/* expression-stmt -> expression ; | ; */
exprStmt	: expr ';'
			| ';'
			;

/* selection-stmt -> if expression then statement [ else statement ]+ */
selectionStmt	: IF expr THEN stmt
				| IF expr THEN stmt ELSE stmt
				;

/* iteration-stmt -> while expressino do statement */
iterationStmt	: WHILE expr DO stmt
				;

/* return-stmt -> return [ expressinon ]+ */
returnStmt	: MYRETURN ';'
			| MYRETURN expr ';'
			;

/* read-stmt -> read variable; */
readStmt	: READ VARIABLE ';'
			;

/* write-stmt -> write expr; */
writeStmt	: WRITE expr ';' {
				$$ = ASTcreateNode(MYWRITE);
				$$->s1 = $2;
			}
			;

/* assignment-stmt -> var = simple-expression; */
assignmentStmt	: var '=' simpleExpr ';'
				;

/* expression -> simple-expression; */
expr	: simpleExpr {
			$$ = $1;
		}
		;

/* var -> ID [ [ expression ] ]+ */
/* NOTE: we aren't dealing with multi dimensional arrays */
var	: VARIABLE
	| VARIABLE '[' expr ']'
	;

/* simple-expression -> additive-expression [ relop additive-expression ]+
   */
simpleExpr	: additiveExpr {
				$$ = $1;
			}
			| simpleExpr relop additiveExpr {
				$$ = NULL;
			}
			;

/* relop -> <= | < | > | >= | == | != */
relop	: LE
		| '<'
		| '>'
		| GE
		| EQ
		| NEQ
		;

/* additive-expression -> term { addop term } */
additiveExpr	: term {
					$$ = $1;
				}
				| term addop additiveExpr  {
					/* all of our multi-expr stuff is EXPR */
					$$ = ASTcreateNode(EXPR);
					$$-> s1 = $1;
					$$-> s2 = $3;
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
		| multop term {
			$$ = NULL;
		}
		;

/* multop -> factor { multop factor } */
multop	: '*'
		| '/'
		| AND
		| OR
		;

/* factor -> ( expression ) | NUM | var | call | TRUE | FALSE | NOT factor
   */
factor	: '(' expr ')' {
			$$ = NULL;
		}
		| NUMBER {
			$$ = ASTcreateNode(MYNUM);
			$$->value = $1;
		}
		| var {
			$$ = NULL;
		}
		| call {
			$$ = NULL;
		}
		| TRUE {
			$$ = NULL;
		}
		| FALSE {
			$$ = NULL;
		}
		| NOT factor {
			$$ = NULL;
		}
		;

/* call -> ID ( args ) */
call	: VARIABLE '(' args ')'
		;

/* args -> arg-list | empty */
args	: /* empty */
		| argList
		;

/* argList -> expression { , expression } */
argList	: expr
		| expr ',' expr
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
