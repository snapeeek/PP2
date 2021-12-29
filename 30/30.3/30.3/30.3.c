#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

void show(const void* ptr, size_t count);
void display_hex(int n);
void inverse_bits(void* ptr, size_t offset, size_t count);

int main()
{
	char input[100];
	printf("Podaj teksta ziomus: ");
	fgets(input, 100, stdin);
	fflush(stdin);

	int i = strlen(input);
	if (*(input + i - 1) != '\0')
		*(input + i - 1) = '\0';

	show(input, i);
	inverse_bits(input, 0, i);
	show(input, strlen(input));

	return 0;
}

void show(const void* ptr, size_t count) 
{
	if (ptr && count > 0)
	{
		const uint8_t *iptr;
		iptr = ptr;
		for (int i = 0; i < (int)count; i++)
		{
			display_hex(*(iptr + i));
		}
		printf("\n");
	}
}

void display_hex(int n)
{
	if (n >= 0)
	{
		int tab[3];
		*(tab + 1) = n % 16;
		n = n / 16;
		*(tab) = n % 16;
		*(tab + 2) = '\0';

		if (*(tab) <= 9)
			printf("%d", *tab);
		else
			switch (*tab)
			{
			case 10:
				printf("a"); break;
			case 11:
				printf("b"); break;
			case 12:
				printf("c"); break;
			case 13:
				printf("d"); break;
			case 14:
				printf("e"); break;
			case 15:
				printf("f"); break;
			}

		if (*(tab + 1) <= 9)
			printf("%d", *(tab + 1));
		else
			switch (*(tab + 1))
			{
			case 10:
				printf("a"); break;
			case 11:
				printf("b"); break;
			case 12:
				printf("c"); break;
			case 13:
				printf("d"); break;
			case 14:
				printf("e"); break;
			case 15:
				printf("f"); break;
			}
		printf(" ");
	}
}

void inverse_bits(void* ptr, size_t offset, size_t count)
{
	if (ptr && count > 0)
	{
		uint8_t *iptr;
		iptr = ptr;
		for (int i = (int)offset; i < (int)count + (int)offset; i++)
		{
			*(iptr + i) = ~*(iptr + i);			
		}
	}
}