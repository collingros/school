/*!
	collin gros
	02/07/2020
	lab 3

	code is from: https://forgetcode.com/C/101-Symbol-table

	indent, comment, and understand the code. create a .h file w/description

	i created the .h file, and indented/commented a lot of the code
*/

#ifndef __SYMTABLE__
#define __SYMTABLE__


/* stores node information */
struct SymbTab {
	char label[10],symbol[10];
	int addr;
	struct SymbTab *next;
};


/* insert a new entry into our symboltable */
void Insert();

/* print all of our table */
void Display();

/* search for and delete a node */
void Delete();

/* search through the entire table, looking for a particular symbol */
/* retuns 1 if lab is found, otherwise the label wasn't found*/
int Search(char lab[]);

/* change a particular node's data */
void Modify();

/* our first and last nodes in the symbtable */
struct SymbTab *first,*last;
int size = 0;


#endif
