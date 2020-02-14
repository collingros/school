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

int mydebug=1;
#include "y.tab.h"
%}


%%

int {
	if (mydebug) {
		fprintf(stderr, "\"int\" found!\n");
	}

	return(INT);
}
[a-z]+[0-9]* {
	if (mydebug) {
		fprintf(stderr, "identifier found!\n");
	}

	return(ID);
}
[0-9][0-9]* {
	if (mydebug) {
		fprintf(stderr, "digit found\n"); 
	}

	yylval=atoi((const char *)yytext);
	return(INTEGER);
}
[ \t] {
	if (mydebug) {
		fprintf(stderr,"Whitespace found\n");
	}
}
[=\-+*/%&|();] {
	if (mydebug) {
		fprintf(stderr,"return a token %c\n",*yytext);
	}

	return (*yytext);
}
\n {
	if (mydebug) {
		fprintf(stderr,"cariage return %c\n",*yytext); 
	}

	return (*yytext);
}
%%

int yywrap(void)
{
	return 1;
}


