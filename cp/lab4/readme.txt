collin gros
02/24/2020
lab4, CS370

my symbol_table, lex, and yacc code all compiles and runs.

i used a couple of test cases to test whether:
	if i define more than the MAX number of variables, i BARF!

	i cannot declare a variable more than once

	i cannot use a variable that is undeclared

	i can declare a variable, then use it on the left and right hand side

all tests behaved as expected.

symbol table code is in the folder ./c

to compile:
	make
to run:
	./run.gitignoreme
	{enter commands}
to clean generated crap:
	make clean
