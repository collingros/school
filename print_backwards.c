#include <stdio.h>
int check_digit(int a, int b, int c, int d, int e,
		int f, int g, int h, int i, int j,
		int k);
void reverse(int n);

int main()
{
	int a, b, c, d, e, f, g, h, i, j, k, cd;
	printf("Enter the UPC code(all integers, no spaces): \n");
	scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d",
	       &a, &b, &c, &d, &e, &f, &g, &h, &i,
	       &j, &k);

	cd = check_digit(a, b, c, d, e, f, g, h, i, j, k);
	printf("The check digit of the entered UPC code is: %d\n", cd);

	int n;
	printf("Enter a number to be printed backwards: \n");
	scanf("%d", &n);
	reverse(n);

	return 0;
}

int check_digit(int a, int b, int c, int d, int e,
		int f, int g, int h, int i, int j,
		int k)
	/* Returns the check digit of UPC code, given UPC integers */
{
	int cd, sum1, sum2, product, total;

	sum1 = a + c + e + g + i + k;
	sum2 = b + d + f + h + j;
	product = (sum1 * 3) + sum2;
	total = product - 1;
	cd = 9 - (total % 10);

	return cd;
}

void reverse(int n)
{
	if (n == 0)
		return;
	else{
		printf("%d", n % 10);
		reverse(n / 10);
	}
}
