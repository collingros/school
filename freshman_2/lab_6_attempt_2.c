/*
Collin Gros
Group: Frank, Mihir
Lab 6
3/8/2018
 */
#include <stdio.h>
int getSeries(int a[]);
int b_search(int a[], int start, int size, int val);

int main()
{
    int a[10] = {0};
    printf("Enter a string of values, ending with 0: \n");
    int size = getSeries(a); /* size is how many integers
                                the user entered in the array */

    int found = 0, val = 0; /* found is true/false */
    printf("Enter the value to search for: \n");
    scanf("%d", &val);
    int mid = size / 2; /* get first midpoint */
    found = b_search(a, mid, size, val); /* found is 1 if user value
                                            is found */
    if (found)
        printf("The number \"%d\" was found in the series.\n",
                val);
    else
        printf("That number \"%d\" was not found in the series.\n",
                val);

    return 0;
}

int getSeries(int a[]) /* gets the array of values user enters */
{
    int n = 0;
    for (int i = 0; i < 10; i++) {
        scanf("%d", &n);
        if (!n) /* if user enters 0, then stop getting integers */
            return i; /* returns the size */
        a[i] = n; 
    }
}

int b_search(int a[], int mid, int size, int val) /* searches values, 0 for not found 1 for found
                                                     using binary method*/
{
    if (val == a[mid]) { /* if value is found  */
      return 1;
    }
    else if (val > a[mid]) { /* change midpoint for the right half */
      return b_search(a, mid+(size-mid)/2, size - mid, val);
    }
    else if (val < a[mid]) { /* change midpoint for the left half */
      return b_search(a, mid-(size-mid)/2, size - mid, val);
    }
    return 0;
}
