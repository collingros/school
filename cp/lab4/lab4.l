%{
/*
	Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
	along with single string elements like '+'.

	This LEX definition is the companion to the docalc.y YACC routine which
	is a simple calculator

	Shaun Cooper
	January 2015


--------------------------------------------------------------------------------
	collin gros
	02/24/2020

	added support for longer variable names, as well as multiple types
	for use with variable names and integers (yacc %UNION)

	made sure to use strdup to avoid using the same memory address as is
	pointed to by yytext.
*/

#include "y.tab.h"

#include <stdio.h>
#include <string.h>

%}


%%
int {
	return(INT);
}
[a-zA-Z][a-zA-Z0-9]* {
	yylval.string = strdup(yytext);
	return(VARIABLE);
}
[0-9][0-9]* {
	yylval.number = atoi(yytext);
	return(INTEGER);
}
[ \t] {
}
[=\-+*/%&|();] {
	return (*yytext);
}
\n {
	return (*yytext);
}
%%

int yywrap(void)
{
	return 1;
}


