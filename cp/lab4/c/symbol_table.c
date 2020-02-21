/*!
	collin gros
	02/20/20
	lab 4

	supply yacc with a symbol table structure, so that we may be able
	to declare and use variables in our language

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "symbol_table.h"


int symbolExists(char *symbol, struct SymbolTable *p)
{
	// if we reach the end of the list
	if (p == NULL) {
		return 0;
	}

	// if we found our symbol
	if (strcmp(symbol, p->symbol) == 0) {
		return 1;
	}

	return symbolExists(symbol, p->next);
}


int insertSymbol(char *symbol, int offset)
{
	if (symbolExists(symbol, first)) {
		if (debug) {
			printf("ERROR: the symbol \"%s\" already exists in the "
				   "symbol table!\n", symbol);
		}

		return 1;
	}

	// create our symbol
	struct SymbolTable *p = malloc(sizeof(struct SymbolTable));
	// copy our symbol's data to the table
	p->symbol = strdup(symbol);
	p->address = offset;

	// insert it in our list of tables
	p->next = NULL;
	// if our symbol table is empty
	if (size == 0) {
		first = p;
		last = p;
	}
	// it's not empty, so append to the end
	else {
		last->next = p;
		last = p;
	}

	++size;

	return 0;
}


void display()
{
	struct SymbolTable *p = first;
	while (p != NULL) {
		printf("symbol: %s\n"
			   "address: %d\n", p->symbol, p->address);
		p = p->next;
	}
	printf("\n");
}


/*

MAIN FUNCTION IS USED FOR TESTING SYMBOL TABLE CODE

int main()
{
	debug = 1;
	display();
	if (insertSymbol("a", 1)) {
		printf("ERROR: insertSymbol() failed!\n");
	}
	display();
	if (insertSymbol("b", 2)) {
		printf("ERROR: insertSymbol() failed!\n");
	}
	display();
	if (insertSymbol("b", 3)) {
		printf("ERROR: insertSymbol() failed!\n");
	}
	display();

	return 0;
}

*/

