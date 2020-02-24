%{
/*
	collin gros
	02/21/20

	yacc program for parsing a calculator
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
			if (insertSymbol($2, offset)) {
				printf("ERROR: insertion of new variable failed!\n");
				exit(1);
			}
			else if (offset >= MAX_SIZE) {
				printf("ERROR: maximum size for regs[] reached!\n");
				exit(1);
			}
			else {
				++offset;
			}
		}
;

list	:	/* empty */
		|	list stat '\n'
		|	list error '\n'
			{ yyerrok; }
;

stat	:	VARIABLE '=' expr
		{
			/* assign the r-value for $1 */
			regs[search($1)] = $3;
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
			$$ = regs[search($1)];
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
