#include<stdio.h>
#include<stdlib.h>

int main()
{

	char nazwa_pliku[20];
	char i;
	printf("Podaj zrodlo: ");
	scanf("%19s", nazwa_pliku);

	FILE *fp;
	fp = fopen(nazwa_pliku, "r");

	if (fp == NULL)
	{
		printf("Error");
		return 1;
	}

	
	for (;;)
	{
		i = fgetc(fp);
		if (i == EOF) break;
		putchar(i);
	}

	fclose(fp);



	return 0;
}