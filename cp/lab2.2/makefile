# collin gros
# 01/31/2020
#
# makefile for lab2.2

all: lab2.2

# compile lex-generated code after running lex
lab2.2: y.tab.c
	gcc -o run y.tab.c

# turn lex code into c code
y.tab.c: lab2docalc.l
	lex lab2docalc.l

# feed yacc the lex file
lab2docalc.l: lab2docalc.y
	yacc -d lab2docalc.y

# get rid of all the generated crap
clean:
	rm run
	rm lex.*
	rm y.*
