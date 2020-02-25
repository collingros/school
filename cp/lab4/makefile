# collin gros
# 02/14/2020

# makefile for lab4
#
# compile lacc, lex, and symbol_table files seperately,
# then link them all together!
#
# creates a ./run.gitignoreme executable

# compile all seperately, then link them together
all: symbol_table yacc lex 
	gcc -Wall -o run.gitignoreme lex.yy.o y.tab.o symbol_table.o

# compile yacc file
yacc: lab4.y
	yacc -d lab4.y
	gcc -c y.tab.c

# compile lex file
lex: lab4.l
	lex lab4.l
	gcc -c lex.yy.c

# compile symbol_table code
symbol_table: ./c/symbol_table.c ./c/symbol_table.h
	gcc -c ./c/symbol_table.c ./c/symbol_table.h

# get rid of all generated crap
clean:
	rm -f *.yy.c
	rm -f *tab.c
	rm -f *tab.h
	rm -f run.gitignoreme
	rm -f *.o
	rm -f ./c/*.gch
