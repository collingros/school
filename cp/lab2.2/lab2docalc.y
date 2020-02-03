%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/*
	This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
	The return type via yylval is integer 

	When we need to make yylval more complicated, we need to define a pointer type for yylval 
	and to instruct YACC to use a new type so that we can pass back better values
 
	The registers are based on 0, so we substract 'a' from each single letter we get.

	based on context, we have YACC do the correct memmory look up or the storage depending
	on position

	Shaun Cooper
	 January 2015

	problems  fix unary minus, fix parenthesis, add multiplication
	problems  make it so that verbose is on and off with an input argument instead of compiled in


	collin gros
	01/31/2020

	i changed the lex file to pass the symbols, '(' and ')' as tokens to
	yacc. this solved the paranthesis issue.

	i added an expression for handling the '*' token. this solved the
	multiplication issue.

	i deleted the 'expr' right before the '-' token under the unary minus
	rule. this solved the unary minus issue.
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "lex.yy.c"

int regs[26];
int base, debugsw = 0;

void yyerror (s)	/* Called by yyparse on error */
	  char *s;
{
  printf ("%s\n", s);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated	*/

%start list

%token INTEGER
%token  VARIABLE

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

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

int main(int argc, char* argv)
{
	yyparse();
}
