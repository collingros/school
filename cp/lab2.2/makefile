# collin gros
# 02/03/2020
#
# makefile for lab2.2
#
# yacc creates y.tab.c, y.tab.h
# lex creates lex.yy.c

# we don't directly compile lex output because yacc takes the lex file
# as input to create its own c-code. lex is simply a lexographic analyzer.
# yacc takes the tokens provided by lex, and generates c-code

all: lab2.2

# compile lex-generated code after running lex
lab2.2: lex.yy.c y.tab.c
	gcc -o run y.tab.c

# feed lex the lex file
lex.yy.c: lab2docalc.l
	lex lab2docalc.l

# feed yacc the yacc file
y.tab.c: lab2docalc.y
	yacc -d lab2docalc.y

# get rid of all the generated crap
clean:
	rm run
	rm lex.*
	rm y.*
