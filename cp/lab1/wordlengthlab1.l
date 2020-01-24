/*!
	collin gros
	01/24/2020

	Shaun Cooper, January 2015:

	This lex routine uses a counting array to match alphabeticstrings 
	and make a frequency count.

	The real item to notice is that yywrap() is called at EOF
	and then is run to do what we need to do.   yywrap() returns
	true when we have a successful end to the program.  We may want
	to return false (0) if we want to lexing process 
	to fail 


	collin gros, 01/24/2020:

	this lex routine was updated to count the number of numbers
	from given input.

	(definition section)
	an integer variable, "count" is declared

	(rules section)
	count is incremented if a token contained a string of
	integers.

	(C section (HA!))
	added a print statement to print the total number of numbers
	counted
*/

%{
	int lgths[100];
	int count = 0;
%}

%%
[a-zA-Z]+	{ lgths[yyleng]++; }
[0-9]+		{ count++; }
.	|
\n	;
%%

int yywrap()
{
	int i;
	printf("Length  No. words\n");
	for (i=1; i<100; i++) {
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}

	printf("numbers: %d\n", count);

	return 1;
}

int main()
{
	yylex();
}
