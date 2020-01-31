# collin gros
# 01/31/2020
#
# makefile for lab2.1

all: lab2.1

# compile lex-generated code after running lex
lab2.1: lex.yy.c
	gcc -o run lex.yy.c

# run lex on lex code
lex.yy.c: lab2remove.l
	lex lab2remove.l

# get rid of all the generated crap
clean:
	rm run
	rm lex.*
