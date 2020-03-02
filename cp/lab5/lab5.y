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

#define MAX_SIZE 3


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
}

%token INT VOID BOOLEAN MYBEGIN END IF THEN ELSE WHILE DO MYRETURN
%token READ WRITE AND OR TRUE FALSE NOT LE GE EQ NEQ
%token <number> NUMBER;
%token <string> VARIABLE;

%%
/* program -> declaration-list */
program	: decList
		;

/* declaration-list -> declaration { declaration } */
decList	: dec
		| dec decList
		;

/* declaration -> var-declaration | fun-declaration */
dec	: varDec
	| funDec
	;

/* var-declaration -> type-specifier var-list ; */
varDec	: typeSpec varList ';'
		;

/* var-list -> ID | ID [ NUM ] | ID , var-list | ID [ NUM ] , var-list */
varList	: VARIABLE
		| VARIABLE '[' NUMBER ']'
		| VARIABLE ',' varList
		| VARIABLE '[' NUMBER ']' ',' varList
		;

/* type-specifier -> int | void | boolean */
typeSpec	: INT
			| VOID
			| BOOLEAN
			;

/* fun-declaration -> type-specifier ID ( params ) compound-stmt */
funDec	: typeSpec VARIABLE '(' params ')' compoundStmt
		;

/* params -> void | param-list */
params	: VOID
		| paramList
		;

/* param-list -> param { , param } */
paramList	: param
			| param ',' paramList
			;

/* param -> type-specifier ID [ [] ] */
param	: typeSpec VARIABLE '[' ']'
		| typeSpec VARIABLE
		;

/* compound-stmt -> begin local-declarations statement-list end */
compoundStmt	: MYBEGIN localDec stmtList END
				;

/* local-declarations -> { var-declarations } */
localDec	: /* empty */
			| varDec localDec 
			;

/* statement-list -> { statement } */
stmtList	: /* empty */
			| stmt stmtList
			;

/* statement -> expression-stmt | compount-stmt | selection-stmt
				| iteration-stmt | assignment-stmt | return-stmt
				| read-stmt | write-stmt */
stmt	: exprStmt
		| compoundStmt
		| selectionStmt
		| iterationStmt
		| assignmentStmt
		| returnStmt
		| readStmt
		| writeStmt
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
writeStmt	: WRITE expr ';'
			;

/* assignment-stmt -> var = simple-expression; */
assignmentStmt	: var '=' simpleExpr ';'
				;

/* expression -> simple-expression; */
expr	: simpleExpr
		;

/* var -> ID [ [ expression ] ]+ */
/* NOTE: we aren't dealing with multi dimensional arrays */
var	: VARIABLE
	| VARIABLE '[' expr ']'
	;

/* simple-expression -> additive-expression [ relop additive-expression ]+
   */
simpleExpr	: additiveExpr
			| simpleExpr relop additiveExpr
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
additiveExpr	: term
				| term addop additiveExpr 
				;

/* addop -> + | - */
addop	: '+'
		| '-'
		;

/* term -> factor { multop factor } */
term	: factor
		| multop term
		;

/* multop -> factor { multop factor } */
multop	: '*'
		| '/'
		| AND
		| OR
		;

/* factor -> ( expression ) | NUM | var | call | TRUE | FALSE | NOT factor
   */
factor	: '(' expr ')'
		| NUMBER
		| var
		| call
		| TRUE
		| FALSE
		| NOT factor
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

	exit(0);
}
