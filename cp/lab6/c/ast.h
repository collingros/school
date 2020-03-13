/*!
	collin gros
	03/06/2020

*/

#ifndef __AST__
#define __AST__


// types of nodes in our tree
enum NODETYPE {
	VARDEC,
	FUNDEC
};

typedef struct ASTNodeType {
	enum NODETYPE Type;
	struct ASTNodeType *s1, *s2, *next;
	char *name;
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


#endif
