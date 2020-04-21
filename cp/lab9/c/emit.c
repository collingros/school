/*	collin gros
	04/21/2020	*/


#include <string.h>
#include <stdio.h>

#include "emit.h"


static int GLABEL = 0;	/*	global label counter	*/


char *genlabel()
{
	char buf[MAX_LABEL_SIZE];
	sprintf(buf, "_L%d", GLABEL++);


	char *s = strdup(buf);
	return s;
}

