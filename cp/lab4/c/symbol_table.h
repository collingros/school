/*!
	collin gros
	02/20/20
	lab 4

	supply yacc with a symbol table structure, so that we may be able
	to declare and use variables in our language

*/

#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__

#include <stdlib.h>


struct SymbolTable {
	char *symbol;
	int address;
	struct SymbolTable *next;
};


/// point to the first and last symbols in our symbol table..
struct SymbolTable *first = NULL;
struct SymbolTable *last = NULL;
/// how many SymbolTables we have in our list of SymbolTable(s)
int size = 0;
/// if we want to see debug messages
int debug = 0;


/// insert a new symbol into our symbol table
///
/// returns 0 for success, otherwise failure
int insertSymbol(char *symbol, int offset);

/// delete a symbol from our symbol table
///
/// returns 0 for success, otherwise failure
int deleteSymbol(char *symbol);

/// search for a symbol in our symbol table
///
/// returns 1 if symbol is found in our symbol table, otherwise it
/// wasn't found or failure
int symbolExists(char *symbol, struct SymbolTable *p);


/* TEMPORARY FUNCTIONS FOR DEBUGGING */

/// print our symbol table to stdout
void display();

#endif
