# collin gros
# 02/28/2020

# makefile for lab5
#
# compile lex, and yacc files seperately,
# then link them all together!
#
# creates a ./run.gitignoreme executable

# compile all seperately, then link them together
all: yacc lex 
	gcc -Wall -o run.gitignoreme lex.yy.o y.tab.o

# compile yacc file
yacc: lab5.y
	yacc -d lab5.y
	gcc -c y.tab.c

# compile lex file
lex: lab5.l
	lex lab5.l
	gcc -c lex.yy.c

# get rid of all generated crap
clean:
	rm -f *.yy.c
	rm -f *tab.c
	rm -f *tab.h
	rm -f run.gitignoreme
	rm -f *.o
