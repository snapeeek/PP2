#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int file_size_from_path(const char *path)
{
	if (path == NULL)
		return -1;
	FILE *f = fopen(path, "r");
	int dlugosc = 0;
	if (f == NULL)
	{
		printf("error");
		exit(1);
	}
	
	while (fgetc(f) != EOF)
	{
		dlugosc++;
	}
	fclose(f);
	return dlugosc;
}

int file_size_from_file(FILE *f)
{	
	int dlugosc = 0;
	if ((f) == NULL) {
		printf("error");
		exit(1);
	}
	
	while (fgetc(f) != EOF)
	{
		dlugosc++;		
	}
	return dlugosc;
}

int main()
{
	char tab[30], *p;	
	printf("Podaj zrodlo pliku: ");
	scanf("%29s", tab);
	p = tab;
	FILE *f;
	f = fopen(tab, "r");

	if (file_size_from_path(p) == file_size_from_file(f))
		printf("%d", file_size_from_path(p));
	
	fclose(f);
	return 0;
}