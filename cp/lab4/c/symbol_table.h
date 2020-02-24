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
extern struct SymbolTable *first;
extern struct SymbolTable *last;
/// how many SymbolTables we have in our list of SymbolTable(s)
extern int size;
/// if we want to see debug messages
extern int debug;


/// insert a new symbol into our symbol table
///
/// returns 0 for success, otherwise failure
///
/// will return failure if symbol already exists
int insertSymbol(char *symbol, int offset);

/// delete a symbol from our symbol table
///
/// returns 0 for success, otherwise failure
int deleteSymbol(char *symbol);

/// search for a symbol in our symbol table, and return its address
///
/// returns the address of the symbol on success, -1 on failure
/// (failure also happens when the symbol does not exist)
int search(char *symbol);

/* TEMPORARY FUNCTIONS FOR DEBUGGING */

/// print our symbol table to stdout
void display();

#endif
