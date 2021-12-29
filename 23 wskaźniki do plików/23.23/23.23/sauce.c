#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int read_file(const char *filename)
{
	static FILE *fp;
	FILE *inside;
	char tab[50];
	int ch, counter = 0;
	static int all_counter = 0;

	fp = fopen(filename, "r");
	if ((fp == NULL) && (all_counter == 0))
	{
		printf("Error");
		exit(1);
	}
	
	if ((fp == NULL) && (all_counter != 0))
	{
		return 1;
	}


	if (all_counter == 0)
	{

	}


	return 0;
}

int main()
{
	char sauce[31];
	printf("Podaj zrodlo pliku: ");
	scanf("%30s", sauce);
	read_file(sauce);




	return 0;
}