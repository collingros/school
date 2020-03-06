# collin gros
# 03/06/2020

# makefile for lab6
#
# compile lex, and yacc files seperately,
# then link them all together!
#
# creates a ./run.gitignoreme executable

# compile all seperately, then link them together

# directory that contains our c-code (ast)
c=./c


all: yacc lex ast
	gcc -Wall -o run.gitignoreme lex.yy.o y.tab.o ast.o

# compile yacc file
yacc: lab6.y
	yacc -d lab6.y
	gcc -c y.tab.c

# compile lex file
lex: lab6.l
	lex lab6.l
	gcc -c lex.yy.c

# compile AST c code
ast: $c/ast.c $c/ast.h
	gcc -c $c/ast.c

# get rid of all generated crap
clean:
	rm -f *.yy.c
	rm -f *tab.c
	rm -f *tab.h
	rm -f run.gitignoreme
	rm -f *.o
