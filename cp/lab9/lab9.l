%{
/*	collin gros
	04/21/2020

	lex routine for handling ALGOL-like code, and helping YACC compile it
	to MIPS asm code.	*/

#include "c/ast.h"
#include "y.tab.h"

#include <stdio.h>
#include <string.h>

int linecount = 1;
%}


%%
 /* keywords */
int {
	return (INT);
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

 /* yacc can't handle two-character matching like this */
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

begin {
	return (MYBEGIN);
}
end {
	return (END);
}

\".*\" {
	yylval.string = strdup(yytext);
	return(STRING);
}

 /* variable and number rules */
[a-zA-Z][a-zA-Z0-9]* {
	yylval.string = strdup(yytext);
	return(VARIABLE);
}
[0-9][0-9]* {
	yylval.number = atoi(yytext);
	return(NUMBER);
}

 /* we ignore whitespace */
[ \t] {
}

 /* all the literal characters we can use in yacc */
[,\[\]()=<>+\-*/;] {
	return (*yytext);
}

 /* carrige returns only for line counting */
\n {
	++linecount;
}
%%

int yywrap(void)
{
	return 1;
}


