# collin gros
# 02/14/2020

# makefile for lab4

all: symbol_table yacc lex 
	gcc -Wall -o run.gitignoreme lex.yy.o y.tab.o symbol_table.o

yacc: lab4.y
	yacc -d lab4.y
	gcc -c y.tab.c

lex: lab4.l
	lex lab4.l
	gcc -c lex.yy.c

symbol_table: ./c/symbol_table.c ./c/symbol_table.h
	gcc -c ./c/symbol_table.c ./c/symbol_table.h

clean:
	rm -f *.yy.c
	rm -f *tab.c
	rm -f *tab.h
	rm -f run.gitignoreme
	rm -f *.o
