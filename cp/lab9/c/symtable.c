/*  Symbol Table --linked list
    Used for Compilers class

    Modified Spring 2015 to allow for name to pointed to by symtable, instead of copied, since the name is copied
    into the heap

    Modified to have levels.  A level 0 means global variable, other levels means in range of the function.  We
    start out our offsets at 0 (from stack pointer) for level 1,,,when we enter a functional declaration.
    We increment offset each time we insert a new variable.  A variable is considered to be valid if it is found in
    the symbol table at our level or lesser level.  If at 0, then it is global.  

    We return a pointer to the symbol table when a variable matches our creteria.

    We add a routine to remove variables at our level and above.
*/

    
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symtable.h"


struct SymbTab *first = NULL;
static int GTEMP = 0;


char *CreateTemp()
{
	char buf[MAX_TEMP_SIZE];
	sprintf(buf, "_t%d", GTEMP++);


	char *s = strdup(buf);
	return s;
}


/* Simple Insert into the symbol table with the size, type level that the name is being inserted into */
struct SymbTab * Insert(char *name, enum DATATYPE Type, int isafunc, int  level, int mysize, int offset , ASTNode * fparms, int isArray)

{
  struct SymbTab * n;
    n=Search(name,level, 0);
    if(n!=NULL)
      {
      printf("\n\tThe name %s exists at level %d already in the symbol table\n\tDuplicate can.t be inserted",name, level);
      return (NULL);
      }
    else
    {
      struct SymbTab *p;
      p=malloc(sizeof(struct SymbTab));
      p->name=name;
      p->offset=offset;  /* assign the offset */
      p->level=level;  /* assign the level */
      p->mysize=mysize;  /* assign the size */
      p->Type=Type;  /* assign the Type */
      p->IsAFunc=isafunc;  /* assign the Function  */
      p->fparms=fparms;  /* assign the Function  */
		p->isArray = isArray;
      p->next=NULL;


   /* Check on how many elements we have in the symbol table */
      if(first==NULL)
      {
        first=p;
      }
      else
      {
        p->next=first;
        first=p;
      }

      return (p);
 
    }
}

/* print out a single symbol table entry -- for debugging */
void PrintSym(struct SymbTab *s)
{
         printf("\t%s\t\t%d\t\t%d\n",s->name,s->offset, s->level);

}


/*  General display to see what is our symbol table */

void Display()
{
   int i;
   struct SymbTab *p;
   p=first;
   printf("\n\tLABEL\t\tOffset \t LEVEL\n");
      while (p!=NULL)
      {
         PrintSym(p);
         p=p->next;
      }
}

/*  Search for a symbol name at level or below.  We have to do multiple passes into the symbol table because we have to find
   the name closest to us 


  If recur is non-zero, then we look through all of the levels, otherwise, only our level 
   We return a pointer to a SymbolTab structure so that we can use other functions/methods to get the attributes */

 


struct SymbTab * Search(char name[], int level, int recur)
{
   int i,flag=0;
   struct SymbTab *p;

  /* for each level, try to find our symbol */
   while (level >= 0)
    {
       p=first;
       while (p!=NULL)
        {
         if((strcmp(p->name,name)==0) && (p->level == level))
           return p;
         p=p->next;
        }
       if (recur == 0) return (NULL);   /* we did not find it at our level */
       level--; /* check the next level up */
    }


   return  NULL;  /* did not find it, return 0 */
}

/* Remove all enteries that have the indicated level
   We need to take care about updating first pointer into the linked list when we are deleting edge elements */


int Delete(int level)
{
    struct SymbTab *p,*f=NULL;  /* we follow with pointer f */
    int SIZE=0;
    p=first;

    
    
  /* cruise through the list */

    while (p != NULL)
      {
        /* do we match? */
        if (p->level>= level )
        { /* if it is the first in the list we have to update first, we know this by f being NULL */
           SIZE+=p->mysize;
           if ( f==NULL) first=p->next;
           else /* not the first element */
              {f->next=p->next;
              }
            p=p->next;
           
        }
        else
         {
               /* update follow pointer, move the p pointer */
                f=p;
                p=p->next;
          }

      }

    return(SIZE);
}


int equalTypes(ASTNode *n1, ASTNode *n2, int level)
{
	enum NODETYPE n1type = n1->Type;
	enum NODETYPE n2type = n2->Type;

	enum DATATYPE n1dt = -1, n2dt = -1;

	/*	check if either n1 or n2 are ID nodes. if they are,
		we need to pull them from the symbol table	*/
	if (n1type == ID) {
		struct SymbTab *s = Search(n1->name, level, 0);
		if (s == NULL) {
			return -1;
		}

		n1dt = s->Type;
	}
	if (n2type == ID) {
		struct SymbTab *s = Search(n2->name, level, 0);
		if (s == NULL) {
			return -1;
		}

		n2dt = s->Type;

	}

	/*	check if the node is a MYNUM type; if it is, its dt is an
		INTTYPE	*/
	if (n1type == MYNUM) {
		n1dt = INTTYPE;
	}
	if (n2type == MYNUM) {
		n2dt = INTTYPE;
	}

	/*	check if the node is a function	*/
	if (n1type == FUNDEC) {
	}
	if (n2type == FUNDEC) {
	}

	/*	if we were unable to set the dt for one of them	*/
	if (n1dt == -1 || n2dt == -1) {
		/*	unknown datatype (not implemented for this yet	*/
		return -1;
	}


	/*	if their datatypes are equal	*/
	if (n1dt == n2dt) {
		return 1;
	}

	/*	their datatypes were different	*/
	return 0;
}



