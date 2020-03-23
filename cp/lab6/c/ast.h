/*!
	collin gros
	03/06/2020

*/

#ifndef __AST__
#define __AST__


// types of nodes in our tree
enum NODETYPE {
	VARDEC,
	FUNDEC,
	PARAM,
	BLOCK,
	MYWRITE,
	MYNUM,
	EXPR
};

enum DATATYPE {
	INTTYPE,
	VOIDTYPE,
	BOOLEANTYPE
};

enum OPERATOR {
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	AND,
	OR
};

typedef struct ASTNodeType {
	enum NODETYPE Type;
	enum DATATYPE dt;
	enum OPERATOR op;

	struct ASTNodeType *s1, *s2, *next;
	char *name;

	/* array size if an array, -1 if not an array */
	int size;

	/* if nodeType is a NUMBER, value is the number */
	int value;
} ASTNode;


/// ASTprint
/// prints the AST of nodes, starting at p and moving down.
/// also indents the screen so that it's easy to see the depth 
/// of the tree
///
/// returns nothing
void ASTprint(ASTNode *p, int level);

/// ASTcreateNode
/// creates a node with the desired NODETYPE
///
/// returns the node's address on success
ASTNode *ASTcreateNode(enum NODETYPE desiredType);

/// prettyPrint()
/// print node information, as well as indent nicely according to depth
/// of the tree
///
/// returns nothing
void prettyPrint(const char *msg, int numTabs);


/*
	returns a pointer to the last node that is connected to node's next
*/
ASTNode *ASTfollowNode(ASTNode *node);


#endif
