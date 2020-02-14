# collin gros
# 02/14/2020

# makefile for lab4

all:
	yacc -d lab4.y
	lex lab4.l
	gcc -Wall -o run lex.yy.c y.tab.c

clean:
	rm *.yy.c
	rm *tab.c
	rm *tab.h
	rm run
