%{
/*
	collin gros
	02/21/20

	yacc program for parsing a calculator.

	example use (notice no semicolon on the end of statements):
		int x;
		int y;
		x = 2
		y = 5
		y = x * y
		y
		value: 10

	added support for using a symbol table instead of a simple array
	that was based on ascii codes
*/

#include <stdio.h>
#include <ctype.h>

#include "./c/symbol_table.h"

#define MAX_SIZE 3


int yylex();

void yyerror (s)	/* Called by yyparse on error */
	 char *s;
{
	printf ("%s\n", s);
	exit(1);
}

// our SymbolTable's memory
int regs[MAX_SIZE];
// where we are in regs[]
int offset = 0;
%}


%start program 

%token INT

%union
{
	int number;
	char *string;
}

%token <number> INTEGER;
%token <string> VARIABLE;
%type <number> expr;

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%	/* end specs, begin rules */

program	:	decls list
;

decls	:	/* empty */
		| decls decl
;

decl	:	INT VARIABLE ';' '\n'
		{
			/* has this variable been declared already? */
			if (insertSymbol($2, offset)) {
				printf("ERROR: insertion of new variable failed!\n");
				exit(1);
			}
			/* do we have enough room for it? */
			else if (offset >= MAX_SIZE) {
				printf("ERROR: maximum size for regs[] reached!\n");
				exit(1);
			}
			/* insertSymbol was successful! */
			else {
				++offset;
			}
		}
;

list	:	/* empty */
		|	list stat '\n'
			/* could add semicolon to the above, but our language is special! */
		|	list error '\n'
			{ yyerrok; }
;

stat	:	VARIABLE '=' expr
		{
			/* checking if this variable has already been declared */
			int varAddress = search($1);
			if (varAddress == -1) {
				printf("ERROR: use of an undeclared variable!\n");
				exit(1);
			}

			/* assign the r-value for $1 */
			regs[varAddress] = $3;
		}

		/* printing a given variable */
		|	VARIABLE
		{
			int varAddress = search($1);
			if (varAddress == -1) {
				printf("ERROR: use of an undeclared variable!\n");
				exit(1);
			}

			int val = regs[varAddress];
			printf("value: %d\n", val);
		}
;

expr	:	'(' expr ')'
		{
			$$ = $2;
		}

		|	'-' expr	%prec UMINUS
		{
			$$ = -$2;
		}

		|	expr '-' expr
		{
			$$ = $1 - $3;
		}

		|	expr '+' expr
		{
			$$ = $1 + $3;
		}

		|	expr '*' expr
		{
			$$ = $1 * $3;
		}

		|	expr '/' expr
		{
			$$ = $1 / $3;
		}

		|	expr '%' expr
		{
			$$ = $1 % $3;
		}

		|	expr '&' expr
		{
			$$ = $1 & $3;
		}

		|	expr '|' expr
		{
			$$ = $1 | $3;
		}

		|	VARIABLE
		{
			/* checking if this variable has already been declared */
			int varAddress = search($1);
			if (varAddress == -1) {
				printf("ERROR: use of an undefined variable!\n");
				exit(1);
			}

			/* assign the r-value for $1 */
			$$ = regs[varAddress];
		}

		|	INTEGER
		{
			$$ = $1;
		}
;

%%	/* end of rules, start of program */

int main(int argc, char** argv)
{
	yyparse();
}
