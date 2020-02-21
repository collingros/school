%{
/*
	Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
	along with single string elements like '+'.

	This LEX definition is the companion to the docalc.y YACC routine which
	is a simple calculator

	Shaun Cooper
	January 2015


	collin gros
*/

#include "y.tab.h"

#include <stdio.h>
#include <string.h>


int mydebug=1;
%}


%%
int {
	if (mydebug) {
		fprintf(stderr, "INT found!\n");
	}

	return(INT);
}
[a-zA-Z]+[a-zA-Z0-9]* {
	if (mydebug) {
		fprintf(stderr, "ID found!\n");
	}

	yylval.string = strdup(yytext);
	return(ID);
}
[0-9][0-9]* {
	if (mydebug) {
		fprintf(stderr, "INTEGER found!\n"); 
	}

	yylval.number = atoi(yytext);
	return(INTEGER);
}
[ \t] {
	if (mydebug) {
		fprintf(stderr, "whitespace found!\n");
	}
}
[=\-+*/%&|();] {
	if (mydebug) {
		fprintf(stderr, "found a token!\n");
	}

	return (*yytext);
}
\n {
	if (mydebug) {
		fprintf(stderr, "found carriage return!\n"); 
	}

	return (*yytext);
}
%%

int yywrap(void)
{
	return 1;
}


