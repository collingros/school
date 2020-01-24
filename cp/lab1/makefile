# collin gros
# 01/24/2020
#
# makefile for lab1

all: lab1 

# compile lex-generated code after running lex
lab1: lex.yy.c
	gcc -o run lex.yy.c

# run lex on lex code
lex.yy.c: wordlengthlab1.l
	lex wordlengthlab1.l

# get rid of all the generated crap
clean:
	rm run
	rm lex.*
