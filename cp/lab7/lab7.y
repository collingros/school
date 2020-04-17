%{
/*	collin gros
	04/08/2020

	lab7	*/ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "c/ast.h"
#include "c/symtable.h"

#define MAX_SIZE 3


ASTNode *globalTreePointer = 0;

int yylex();
extern int linecount;

/*	level of compound stmts	*/
int level = 0;

/*	offset from the stack pointer	*/
int offset = 0;

/*	global offset	*/
int goffset;

void yyerror (s)	/* Called by yyparse on error */
	 char *s;
{
	fprintf (stderr, "%s on line %d\n", s, linecount);
}
%}


%start program

%union
{
	int number;
	char *string;
	enum DATATYPE datatype;
	enum OPERATOR op;
	struct ASTNodeType *node;
}

%token	INT VOID BOOLEAN MYBEGIN END IF THEN ELSE WHILE DO
		MYRETURN READ WRITE AND OR TRUE FALSE NOT LE GE EQ
		NEQ
%token <number> NUMBER;
%token <string> VARIABLE;

%type <node>	varList varDec dec decList funDec params paramList param
				compoundStmt stmtList stmt localDec writeStmt expr
				simpleExpr additiveExpr term factor args argList call var
				assignmentStmt exprStmt iterationStmt returnStmt readStmt
				selectionStmt

%type <datatype> typeSpec 
%type <op> addop multop relop

%%
/* program -> declaration-list */
program	: decList {
			globalTreePointer = $1;
		}
		;

/* declaration-list -> declaration { declaration } */
decList	: dec {
			$$ = $1;
		}
		| dec decList {
			ASTNode *last = ASTfollowNode($1);
			/* append the other decList to the end of the last node
			   in this node's next chain */
			last->next = $2;

			$$ = $1;
		}
		;

/* declaration -> var-declaration | fun-declaration */
dec	: varDec {
		$$ = $1;
	}
	| funDec {
		$$ = $1;
	}
	;

/* var-declaration -> type-specifier var-list ; */
varDec	: typeSpec varList ';' {
			$$ = $2;

			/*	propogate dt across all vars in varList	*/
			for (ASTNode *i = $$; i != NULL; i = i->next) {
				struct SymbTab *sym = Search(i->name, level, 0);
				sym->Type = $1;
				i->dt = $1;
			}
		}
		;

/* var-list -> ID | ID [ NUM ] | ID , var-list | ID [ NUM ] , var-list */
varList	: VARIABLE {
			if (Search($1, level, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($1);

				exit(1);
			}

			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($1, -1, 0, level, 1, offset, NULL, 0);

			/* increment offset by the size	*/
			offset = offset + 1;
			Display();
		}
		| VARIABLE '[' NUMBER ']' {
			if (Search($1, level, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($1);

				exit(1);
			}

			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($1, -1, 0, level, $3, offset, NULL, 1);

			/* default is -1, indicating the
			   variable is NOT an array */
			$$->size = $3;

			/* increment offset by the size	*/
			offset = offset + $3;
			Display();
		}
		| VARIABLE ',' varList {
			if (Search($1, level, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($1);

				exit(1);
			}

			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $3;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($1, -1, 0, level, 1, offset, NULL, 0);

			/* increment offset by the size	*/
			offset = offset + 1;
			Display();
		}
		| VARIABLE '[' NUMBER ']' ',' varList {
			if (Search($1, level, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($1);

				exit(1);
			}

			$$ = ASTcreateNode(VARDEC);
			$$->name = $1;
			$$->next = $6;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($1, -1, 0, level, $3, offset, NULL, 1);

			/* default is -1, indicating the
			   variable is NOT an array */
			$$->size = $3;

			/* increment offset by the size	*/
			offset = offset + $3;
			Display();
		}
		;

/* type-specifier -> int | void | boolean */
typeSpec	: INT {
				$$ = INTTYPE;
			}
			| VOID {
				$$ = VOIDTYPE;
			}
			| BOOLEAN {
				$$ = BOOLEANTYPE;
			}
			;

/* fun-declaration -> type-specifier ID ( params ) compound-stmt */
funDec	:	typeSpec VARIABLE '(' {
				if (Search($2, level, 0) != NULL) {
					yyerror("ERROR: duplicate function: ");
					yyerror($2);

					exit(1);
				}

				/*	insert into symbol table so we know this function
					exists while we're defining it (for recursion)	*/
				/*	name, type, isafunc, level, mysize, offset, fparams	*/
				Insert($2, $1, 1, level, 0, 0, NULL, 0);

				goffset = offset;
				offset = 0;
			}
			params ')' compoundStmt {
				$$ = ASTcreateNode(FUNDEC);
				$$->name = $2;
				$$->dt = $1;
				$$->s1 = $5;
				$$->s2 = $7;

				/*	retrieve the symbol table for this function and
					add in the formal parameters	*/
				struct SymbTab *s = Search($2, level, 0);
				s->fparms = $5;
				$$->sym = s;

				offset = goffset;
				Display();
		}
		;

/* params -> void | param-list */
params	: VOID {
			$$ = NULL;
		}
		| paramList {
			$$ = $1;
		}
		;

/* param-list -> param { , param } */
paramList	: param {
				$$ = $1;
			}
			| param ',' paramList {
				ASTNode *last = ASTfollowNode($1);
				/* append the other decList to the end of the last node
				   in this node's next chain */
				last->next = $3;

				$$ = $1;
			}
			;

/* param -> type-specifier ID [ [] ] */
param	: typeSpec VARIABLE '[' ']' {
			if (Search($2, level + 1, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($2);

				exit(1);
			}

			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($2, $1, 0, level + 1, 1, offset, NULL, 1);

			$$->size = 0;
			offset = offset + 1;
			Display();
		}
		| typeSpec VARIABLE {
			if (Search($2, level + 1, 0) != NULL) {
				yyerror("ERROR: duplicate variable: ");
				yyerror($2);

				exit(1);
			}

			$$ = ASTcreateNode(PARAM);
			$$->dt = $1;
			$$->name = $2;

			/*	name, type, isafunc, level, mysize, offset, fparams, isarray	*/
			$$->sym = Insert($2, $1, 0, level + 1, 1, offset, NULL, 0);

			offset = offset + 1;
			Display();
		}
		;

/* compound-stmt -> begin local-declarations statement-list end */
compoundStmt	: MYBEGIN {
					++level;
				}
				localDec stmtList END {
					$$ = ASTcreateNode(BLOCK);
					$$->s1 = $3;
					$$->s2 = $4;

					/*	reset our offset back to what it was	*/
					offset -= Delete(level);
					--level;
				}
				;

/* local-declarations -> { var-declarations } */
localDec	: /* empty */ {
				$$ = NULL;
			}
			| varDec localDec  {
				if ($1 == NULL) {
					$$ = $2;
				}
				else {
					ASTNode *last = ASTfollowNode($1);
					/* append the other decList to the end of the last node
					   in this node's next chain */
					last->next = $2;

					$$ = $1;
				}
			}
			;

/* statement-list -> { statement } */
stmtList	: /* empty */ {
				$$ = NULL;
			}
			| stmt stmtList {
				if ($1 == NULL) {
					$$ = $2;
				}
				else {
					ASTNode *last = ASTfollowNode($1);
					/* append the other decList to the end of the last node
					   in this node's next chain */
					last->next = $2;

					$$ = $1;
				}
			}
			;

/* statement -> expression-stmt | compount-stmt | selection-stmt
				| iteration-stmt | assignment-stmt | return-stmt
				| read-stmt | write-stmt */
stmt	: exprStmt {
			$$ = $1;
		}
		| compoundStmt {
			$$ = $1;
		}
		| selectionStmt {
			$$ = $1;
		}
		| iterationStmt {
			$$ = $1;
		}
		| assignmentStmt {
			$$ = $1;
		}
		| returnStmt {
			$$ = $1;
		}
		| readStmt {
			$$ = $1;
		}
		| writeStmt {
			$$ = $1;
		}
		;

/* expression-stmt -> expression ; | ; */
exprStmt	: expr ';' {
				$$ = $1;
			}
			| ';' {
				$$ = NULL;
			}
			;

/* selection-stmt -> if expression then statement [ else statement ]+ */
selectionStmt	: IF expr THEN stmt {
					$$ = ASTcreateNode(MYIF);
					$$->s1 = $2;

					ASTNode *elseNode = ASTcreateNode(MYELSE);
					/*	the stmt in the IF	*/
					elseNode->s1 = $4;
					/*	the stmt in the ELSE	*/
					elseNode->s2 = NULL;

					$$->s2 = elseNode;
				}
				| IF expr THEN stmt ELSE stmt {
					$$ = ASTcreateNode(MYIF);
					$$->s1 = $2;

					ASTNode *elseNode = ASTcreateNode(MYELSE);
					/*	the stmt in the IF	*/
					elseNode->s1 = $4;
					/*	the stmt in the ELSE	*/
					elseNode->s2 = $6;

					$$->s2 = elseNode;
				}
				;

/* iteration-stmt -> while expressino do statement */
iterationStmt	: WHILE expr DO stmt {
					$$ = ASTcreateNode(MYWHILE);
					$$->s1 = $2;
					$$->s2 = $4;
				}
				;

/* return-stmt -> return [ expressinon ]+ */
returnStmt	: MYRETURN ';' {
				$$ = ASTcreateNode(RETURN);
			}
			| MYRETURN expr ';' {
				$$ = ASTcreateNode(RETURN);
				$$->s1 = $2;
			}
			;

/* read-stmt -> read variable; */
readStmt	: READ var ';' {
				$$ = ASTcreateNode(MYREAD);
				$$->s1 = $2;
			}
			;

/* write-stmt -> write expr; */
writeStmt	: WRITE expr ';' {
				$$ = ASTcreateNode(MYWRITE);
				$$->s1 = $2;
			}
			;

/* assignment-stmt -> var = simple-expression; */
assignmentStmt	: var '=' simpleExpr ';' {
					if (!equalTypes($1, $3, level)) {
						yyerror("ERROR: assignment statement has unequal "
								"types: \n");
						yyerror($1->name);

						exit(1);
					}

					$$ = ASTcreateNode(ASSIGN);
					$$->s1 = $1;
					$$->s2 = $3;

				}
				;

/* expression -> simple-expression; */
expr	: simpleExpr {
			$$ = $1;
		}
		;

/* var -> ID [ [ expression ] ]+ */
/* NOTE: we aren't dealing with multi dimensional arrays */
var	: VARIABLE {
		/*	check if this var is in the symbol table	*/
		if (Search($1, level, 1) == NULL) {
			yyerror("ERROR: undefined variable: ");
			yyerror($1);

			exit(1);
		}

		$$ = ASTcreateNode(ID);
		$$->name = $1;
	}
	| VARIABLE '[' expr ']' {
		/*	check if this var is in the symbol table	*/
		struct SymbTab *s = Search($1, level, 1);
		if (s == NULL) {
			yyerror("ERROR: undefined variable: ");
			yyerror($1);

			exit(1);
		}

		/*	check if the var is actually an array	*/
		if (!s->isArray) {
			yyerror("ERROR: [] is undefined on non-array types: \n");
			yyerror($1);

			exit(1);
		}

		$$ = ASTcreateNode(ID);
		$$->name = $1;
		/*	an VARIABLE node's s1 points to its expression	*/
		$$->s1 = $3;

	}
	;

/* simple-expression -> additive-expression [ relop additive-expression ]+
   */
simpleExpr	: additiveExpr {
				$$ = $1;
			}
			| simpleExpr relop additiveExpr {
				$$ = ASTcreateNode(EXPR);
				$$->s1 = $1;
				$$->op = $2;
				$$->s2 = $3;

			}
			;

/* relop -> <= | < | > | >= | == | != */
relop	: LE {
			$$ = MYLE;
		}
		| '<' {
			$$ = GT;
		}
		| '>' {
			$$ = LT;
		}
		| GE {
			$$ = MYGE;
		}
		| EQ {
			$$ = MYEQ;
		}
		| NEQ {
			$$ = MYNEQ;
		}
		;

/* additive-expression -> term { addop term } */
additiveExpr	: term {
					$$ = $1;
				}
				| additiveExpr addop term {
					/* all of our multi-expr stuff is EXPR */
					$$ = ASTcreateNode(EXPR);
					$$->s1 = $1;
					$$->op = $2;
					$$->s2 = $3;

					/*	if s1's type is equal to s2's type, then we are ok.
						this includes if s1's type is 'INT' and s2 is a
						NUMBER node.	*/
					if (!equalTypes($1, $3, level)) {
						yyerror("ERROR: additiveExpr with unequal types!\n");
						exit(1);
					}

				}
				;

/* addop -> + | - */
addop	: '+' {
			$$ = PLUS;
		}
		| '-' {
			$$ = MINUS;
		}
		;

/* term -> factor { multop factor } */
term	: factor {
			$$ = $1;
		}
		| term multop term {
			/* all of our multi-expr stuff is EXPR */
			$$ = ASTcreateNode(EXPR);
			$$->s1 = $1;
			$$->op = $2;
			$$->s2 = $3;
		}
		;

/* multop -> factor { multop factor } */
multop	: '*' {
			$$ = MULTIPLY;
		}
		| '/' {
			$$ = DIVIDE;
		}
		| AND {
			$$ = MYAND;
		}
		| OR {
			$$ = MYOR;
		}
		;

/* factor -> ( expression ) | NUM | var | call | TRUE | FALSE | NOT factor
   */
factor	: '(' expr ')' {
			$$ = $2;
		}
		| NUMBER {
			$$ = ASTcreateNode(MYNUM);
			$$->value = $1;
		}
		| var {
			$$ = $1;
		}
		| call {
			$$ = $1;
		}
		| TRUE {
			$$ = ASTcreateNode(BOOL);
			$$->value = 1;
		}
		| FALSE {
			$$ = ASTcreateNode(BOOL);
			$$->value = 0;
		}
		| NOT factor {
			$$ = ASTcreateNode(MYNOT);
			$$->s1 = $2;
		}
		;

/* call -> ID ( args ) */
call	: VARIABLE '(' args ')' {
			$$ = ASTcreateNode(CALL);
			$$->name = $1;
			$$->s1 = $3;

			/*	grab the symbol table for this variable	*/
			struct SymbTab *s = Search($1, level, 1);
			/*	if our var doesn't exist	*/
			if (s == NULL) {
				yyerror("ERROR: attempt to call undefined function: ");
				yyerror($1);

				exit(1);
			}
			/*	if our var isn't a function	*/
			else if (!s->IsAFunc) {
				yyerror("ERROR: calling a variable that is not a function: ");
				yyerror($1);

				exit(1);
			}

			/*	check that our arguments match our formal parameters	*/
			/*	iterate the arguments & parameters	*/
			ASTNode *fparm = s->fparms;
			ASTNode *arg = $3;
			while (fparm != NULL && arg != NULL) {
				/*	pull our symbol table data from this current arg	*/
				struct SymbTab *s = Search(arg->name, level, 1);
				/*	if this arg was never defined	*/
				if (s == NULL) {
					yyerror("ERROR: use of undefined argument: \n");
					yyerror($1);

					exit(1);
				}

				/*	if our current arg/param have differing data types...	*/
				if (fparm->dt != s->Type) {
					yyerror("ERROR: mismatched data types for function "
							"call: ");
					yyerror($1);

					exit(1);
				}

				fparm = fparm->next;
				arg = arg->next;
			}

			/*	if the number of arguments and fparams are not matched..	*/
			if (!(fparm == NULL && arg == NULL)) {
				yyerror("ERROR: mismatched number of arguments for function"
						" call: ");
				yyerror($1);

				exit(1);
			}

		}
		;

/* args -> arg-list | empty */
args	: /* empty */ {
			$$ = NULL;
		}
		| argList {
			$$ = $1;
		}
		;

/* argList -> expression { , expression } */
argList	: expr {
			$$ = $1;
		}
		| expr ',' argList {
			ASTNode *last = ASTfollowNode($1);
			/* append the other decList to the end of the last node
			   in this node's next chain */
			last->next = $3;

			$$ = $1;
		}
		;
%%

int main(int argc, char** argv)
{
	if (yyparse()) {
		fprintf(stderr, "yyparse() failed!\n");
		exit(1);
	}
	printf("yyparse() was successful!\n");

	if (globalTreePointer == 0) {
		fprintf(stderr, "ERROR: globalTreePointer points to null!\n");
		exit(1);
	}

	// print out
	ASTprint(globalTreePointer, 0);

	exit(0);
}
