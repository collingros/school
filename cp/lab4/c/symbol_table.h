/*!
	collin gros
	02/20/20
	lab 4

	supply yacc with a symbol table structure, so that we may be able
	to declare and use variables in our language

*/

#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__


struct SymbolTable {
	char *symbol;
	int addr;
	struct SymbolTable *next;
};


/// insert a new symbol into our symbol table
///
/// returns 0 for success, otherwise failure
int insertSymbol(char *symbol);

/// delete a symbol from our symbol table
///
/// returns 0 for success, otherwise failure
int deleteSymbol(char *symbol);

/// search for a symbol in our symbol table
///
/// returns 1 if symbol is found in our symbol table, otherwise it
/// wasn't found or failure
int symbolExists(char *symbol);

/// modify a symbol's data
///
/// returns 0 for success, otherwise failure
int modifySymbol(char *symbol);


/* TEMPORARY FUNCTIONS FOR DEBUGGING */

/// print our symbol table to stdout
void display();

