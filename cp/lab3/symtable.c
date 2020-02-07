/*!
	collin gros
	02/07/2020
	lab 3

	code is from: https://forgetcode.com/C/101-Symbol-table

	indent, comment, and understand the code. create a .h file w/description

	i created the .h file, and indented/commented a lot of the code
*/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#include "symtable.h"


void main()
{
	int option;
	char label[10];

	/* our menu */
	do {
		printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
		printf("\n\t1.INSERT\n\t2.DISPLAY\n"
			   "\t3.DELETE\n\t4.SEARCH\n\t5.MODIFY\n\t6.END\n");
		printf("\n\tEnter your choice: ");
		scanf("%d",&option);

		switch(option) {
			case 1:
				Insert();
				break;
			case 2:
				Display();
				break;
			case 3:
				Delete();
				break;
			case 4:
				printf("\n\tEnter the label to be searched : ");
				scanf("%s",label);

				/* search for the label they specified */
				int isPresent = Search(label);
				printf("\n\tSearch Result:");
				if(isPresent) {
					printf("\n\tThe label is present in "
						   "the symbol table\n");
				}
				else {
					printf("\n\tThe label is not present "
						   "in the symbol table\n");
				}

				break;
			case 5:
				Modify();
				break;
			case 6:
				exit(0);
		}
	} while(1);
}


void Insert()
{
	int n;
	char l[10];

	printf("\n\tEnter the label : ");
	scanf("%s",l);

	/* can't insert a label if it already exists! */
	n=Search(l);
	if(n==1) {
		printf("\n\tThe label exists already in the symbol "
			   "table\n\tDuplicate can.t be inserted");
	}
	else {
		struct SymbTab *p;
		p=malloc(sizeof(struct SymbTab));
		strcpy(p->label,l);

		/* set our values in the symbol table */
		printf("\n\tEnter the symbol : ");
		scanf("%s",p->symbol);
		printf("\n\tEnter the address : ");
		scanf("%d",&p->addr);

		/* if there were no other nodes before... */
		p->next=NULL;
		if(size==0) {
			first=p;
			last=p;
		}
		/* insert it into existing list */
		else {
			last->next=p;
			last=p;
		}

		size++;
	}
	printf("\n\tLabel inserted\n");
}


void Display()
{
	int i;
	struct SymbTab *p;

	p=first;
	printf("\n\tLABEL\t\tSYMBOL\t\tADDRESS\n");

	/* increment the entire list and print all information */
	for(i=0;i<size;i++) {
		printf("\t%s\t\t%s\t\t%d\n",p->label,p->symbol,p->addr);
		p=p->next;
	}
}


int Search(char lab[])
{
	int i,flag=0;
	struct SymbTab *p;

	/* iterate the entire table and search for our label */
	p=first;
	for(i=0;i<size;i++) {
		if(strcmp(p->label,lab)==0) {
			flag=1;
		}

		p=p->next;
	}
	return flag;
}


void Modify()
{
	char l[10],nl[10];
	int add,choice,i,s;
	struct SymbTab *p;

	p=first;
	printf("\n\tWhat do you want to modify?\n");
	printf("\n\t1.Only the label\n\t2.Only the address\n"
		   "\t3.Both the label and address\n");
	printf("\tEnter your choice : ");

	scanf("%d",&choice);
	switch(choice) {
		case 1:
			printf("\n\tEnter the old label : ");
			scanf("%s",l);

			/* if our label doesn't exist */
			s=Search(l);
			if(s==0) {
				printf("\n\tLabel not found\n");
			}
			else {
				printf("\n\tEnter the new label : ");
				scanf("%s",nl);
				/* search our symbol table for the label and change its
				   data */
				for(i=0;i<size;i++) {
					if(strcmp(p->label,l)==0) {
						strcpy(p->label,nl);
					}

					p=p->next;
				}

				printf("\n\tAfter Modification:\n");
				Display();
			}
			break;
		case 2:
			printf("\n\tEnter the label where the "
				   "address is to be modified : ");
			scanf("%s",l);

			/* if our label doesn't exist */
			s=Search(l);
			if(s==0) {
				printf("\n\tLabel not found\n");
			}
			else {
				printf("\n\tEnter the new address : ");
				scanf("%d",&add);
				/* search our symbol table for the label and change its
				   data */
				for(i=0;i<size;i++) {
					if(strcmp(p->label,l)==0) {
						p->addr=add;
					}

					p=p->next;
				}

				printf("\n\tAfter Modification:\n");
				Display();
			}
			break;
		case 3:
			printf("\n\tEnter the old label : ");
			scanf("%s",l);

			/* if our label doesn't exist */
			s=Search(l);
			if(s==0) {
				printf("\n\tLabel not found\n");
			}
			else {
				printf("\n\tEnter the new label : ");
				scanf("%s",nl);
				printf("\n\tEnter the new address : ");
				scanf("%d",&add);

				/* search our symbol table for the label and change its
				   data */
				for(i=0;i<size;i++) {
					if(strcmp(p->label,l)==0) {
						strcpy(p->label,nl);
						p->addr=add;
					}

					p=p->next;
				}

				printf("\n\tAfter Modification:\n");
				Display();
			}
			break;
	}
}


void Delete()
{
	int a;
	char l[10];
	struct SymbTab *p,*q;

	p=first;
	printf("\n\tEnter the label to be deleted : ");
	scanf("%s",l);

	/* if our label doesn't exist */
	a=Search(l);
	if(a==0) {
		printf("\n\tLabel not found\n");
	}
	else {
		/* if we found our label in the first node */
		if(strcmp(first->label,l)==0) {
			/* 'delete' our node, and modify where first points to */
			first=first->next;
		}

		/* if we found our label in the last node */
		else if(strcmp(last->label,l)==0) {
			q=p->next;
			/* 'delete' node, and modify where last points to */
			while(strcmp(q->label,l)!=0) {
				p=p->next;
				q=q->next;
			}

			p->next=NULL;
			last=p;
		}
		else {
			q=p->next;
			/* search for our label */
			while(strcmp(q->label,l)!=0) {
				p=p->next;
				q=q->next;
			}

			/* 'delete' our node */
			p->next=q->next;
		}

		size--;
		printf("\n\tAfter Deletion:\n");
		Display();
	}
}

