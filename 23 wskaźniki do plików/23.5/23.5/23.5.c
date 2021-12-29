#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *fp;
	char sauce[50];
	printf("Podaj nazwe pliku: ");
	scanf("%49s", sauce);
	fp = fopen(sauce, "w");
	if (fp == NULL)
	{
		printf("Error");
		return 1;
	}
	
	int i;
	for (i = 0; i <= 100; i++)
	{
		fprintf(fp, "%d\n", i);
	}
	
	printf("File saved");
	
	fclose(fp);
	return 0;
}
