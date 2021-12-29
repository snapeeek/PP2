#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

int count_bits(const void* ptr, size_t offset, size_t count);
int check(uint8_t n);

int main()
{
	char sauce[101];
	printf("Podaj zrodlo: ");
	scanf("%100s", sauce);

	FILE *fp;
	if (!(fp = fopen(sauce, "rb")))
	{
		printf("Unable to open the file");
		return 1;
	}

	char tab[1000];
	int ch, i = 0;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		*(tab + i) = ch;
		ch = fgetc(fp);
		i++;
	}
	*(tab + i) = '\0';

	int a;
	a = count_bits(tab, 0, i);
	printf("%d", a);

	fclose(fp);
	return 0;
}

int count_bits(const void* ptr, size_t offset, size_t count)
{
	if (!ptr)
		return -1;

	const uint8_t *iptr;
	iptr = ptr;

	int suma = 0, a;
	for (int i = offset; i < (int)count + (int)offset; i++)
	{
		a = check(*(iptr + i));
		suma = suma + a;
	}

	return suma;
}

int check(uint8_t n)
{
	int counter = 0;
	while (n > 0)
	{
		if (n % 2 == 1)
		{
			counter++;
		}
		n = n / 2;
	}
	
	return counter;
}