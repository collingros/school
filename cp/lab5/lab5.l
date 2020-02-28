%{
/*
	Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
	along with single string elements like '+'.

	This LEX definition is the companion to the docalc.y YACC routine which
	is a simple calculator

	Shaun Cooper
	January 2015


	collin gros
	02/28/2020

*/

#include "y.tab.h"

#include <stdio.h>
#include <string.h>

int linecount = 1;
%}


%%
int {
	return(INT);
}
void {
	return (VOID);
}
boolean {
	return (BOOLEAN);
}

true {
	return (TRUE);
}
false {
	return (FALSE);
}

and {
	return (AND);
}
or {
	return (OR);
}
not {
	return (NOT);
}

while {
	return (WHILE);
}
do {
	return (DO);
}

if {
	return (IF);
}
then {
	return (THEN);
}
else {
	return (ELSE);
}

read {
	return (READ);
}
write {
	return (WRITE);
}

return {
	return (MYRETURN);
}

"<=" {
	return (LE);
}
">=" {
	return (GE);
}
"==" {
	return (EQ);
}
"!=" {
	return (NEQ);
}

mybegin {
	return (MYBEGIN);
}
end {
	return (END);
}


[a-zA-Z][a-zA-Z0-9]* {
	yylval.string = strdup(yytext);
	return(VARIABLE);
}
[0-9][0-9]* {
	yylval.number = atoi(yytext);
	return(NUMBER);
}
[ \t] {
}
[,\[\]()=<>+\-*/] {
	return (*yytext);
}
\n {
	++linecount;
}
%%

int yywrap(void)
{
	return 1;
}


