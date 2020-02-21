%{

/*
	collin gros
	02/21/20

	yacc file for parsing a calculator
*/

#include <stdio.h>
#include <ctype.h>

#include "symbol_table.h"


int yylex();

void yyerror (s)	/* Called by yyparse on error */
	 char *s;
{
	printf ("%s\n", s);
}

// our SymbolTable's memory
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
%token <string> ID;

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

program	:	DECLS list
;

DECLS	:	/* empty */
		| DEC DECLS
;

DEC	:	INT	ID ';'	'\n'
		{
			if (insertSymbol($2, offset)) {
				fprintf(stderr, "ERROR: failed to insert!\n");
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

stat	:	expr
			{
			fprintf(stderr,"the anwser is %d\n", $1); 
			}
	|	VARIABLE '=' expr
			{ regs[$1] = $3; }
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '*' expr
			{ $$ = $1 * $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	VARIABLE
			{ $$ = regs[$1];
				{ fprintf(stderr,"found a variable value =%d\n",$1); }
			}
	|	INTEGER {$$=$1;
				{ fprintf(stderr,"found an integer\n");}
			}
	;



%%	/* end of rules, start of program */

int main(int argc, char** argv)
{
	yyparse();
}
