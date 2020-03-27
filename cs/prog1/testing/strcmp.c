#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int test1()
{
	char x[50];
	for (int i = 0; i < 5; ++i) {
		x[i] = 'a';
	}
	x[5] = '\0';

	char *x2 = "aaaaa";

	return (strcmp(x, x2));
}


int test2()
{
	FILE *fp = fopen("tmp.txt", "r");
	if (fp == NULL) {
		return -100;
	}

	char word[10];
	fgets(word, 10, fp);
	word[strcspn(word, "\n")] = '\0';

	for (int i = 0; i < 10; ++i) {
		printf("%c", word[i]);
	}
	printf("\n");

	char *word2 = "hel";


	fclose(fp);

	return (strcmp(word, word2));
}


int main()
{
	printf("%d\n", test1());
	printf("%d\n", test2());
}
