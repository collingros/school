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


struct SymbolTable *first = NULL;
struct SymbolTable *last = NULL;
int size = 0;
int debug = 1;

int search(char *symbol)
{
	// iterate the entire list
	struct SymbolTable *p = first;
	while (p != NULL) {
		if (strcmp(symbol, p->symbol) == 0) {
			// our symbol was found! return its address!
			return p->address;
		}

		p = p->next;
	}

	// symbol does not exist
	return -1;
}


int insertSymbol(char *symbol, int offset)
{
	if (search(symbol) != -1) {
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

