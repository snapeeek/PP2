#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main()
{
	FILE *fp;
	int suma = 0, helper = 0;
	char cyfry[50], sauce[50];
	int ch;
	printf("Podaj zrodlo: ");
	scanf("%49s", sauce);

	fp = fopen(sauce, "r");
	if (fp == NULL)
	{
		printf("Error");
		return 1;
	}

	while (1) 
	{
		ch = fgetc(fp);
		
		if ((isspace(ch) == 0) && (ch != EOF))
		{
			cyfry[helper] = ch;
			helper++;
		}
		else
		{
			cyfry[helper] = 0;
			suma = suma + atoi(cyfry);
			helper = 0;
		}

		if (ch == EOF)
			break;
	}

	fclose(fp);
	printf("%d", suma);


	return 0;
}