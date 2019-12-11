#include <stdio.h>
#define SIZE 10
int getSeries(int a[]);
int b_search(int a[], int num);


int main()
{
    int a[SIZE] = {0};
    printf("Enter a string of values, ending with 0: \n");
    getSeries(a);

    int num = 0, found = 0;
    printf("Enter the value to search for: \n");
    scanf("%d", &num);
    found = b_search(a, num);
    if (found)
        printf("\"%d\" was found in the series.\n", num);
    else
        printf("\"%d\" was not found in the series.\n", num);

    return 0;
}

int getSeries(int a[])
{
    int n = 0;
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &n);
        puts("before assignment");
        if (!n)
            break;
        a[i] = n; 
        puts("after assignment");
    }
    return n;
}

int b_search(int a[], int num)
{
    int mid = SIZE / 2, i = 0;
    while(1) {
        if (a[i] == num) {
            puts("1");
            return 1;
        }
        if (num < a[mid]) {
            puts("2");
            if (i == mid)
                break;
            i++;
        }
        else if (num > a[mid]) {
            puts("3");

            if (i == mid)
                break;
            i--;
        }
    }
    puts("end of while");
    return 0;
}


















