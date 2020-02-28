%{
/*
	collin gros
	02/28/20
*/

#include <stdio.h>
#include <ctype.h>

#include "./c/symbol_table.h"

#define MAX_SIZE 3


int yylex();
extern int linecount;

// our SymbolTable's memory
int regs[MAX_SIZE];
// where we are in regs[]
int offset = 0;

void yyerror (s)	/* Called by yyparse on error */
	 char *s;
{
	printf ("%s on line %d\n", s, linecount);
	exit(1);
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
program	: decList;

/* declaration-list -> declaration { declaration } */
decList	: dec
		| dec decList
		;

/* declaration -> var-declaration | fun-declaration */
decl	: varDec
		| funDec
		;

/* var-declaration -> type-specifier var-list ; */
varDec	: typeSpec varList
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
compoundStmt	: MYBEGIN localDecs stmtList END
				;

/* local-declarations -> { var-declarations } */
localDecs	: /* empty */
			| varDecs localDecs
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
assignmentStmt	: VARIABLE '=' simpleExpr ';'
				;

/* expression -> simple-expression; */
expr	: simpleExpr
		;

/* var -> ID [ [ expression ] ]+ */
/* NOTE: we aren't dealing with multi dimensional arrays */
var	: VARIABLE '[' expr ']'
	;

/* simple-expression -> additive-expression [ relop additive-expression ]+
   */
simpleExpr	: additiveExpr
			| additiveExpr relop additiveExpr
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
				| term addop term
				;

/* addop -> + | - */
addop	: '+'
		| '-'
		;

/* term -> factor { multop factor } */
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
	yyparse();
}
