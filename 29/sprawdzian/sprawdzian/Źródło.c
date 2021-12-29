#include<stdio.h>
#include<string.h>

void show(const void* ptr, size_t count)
{
	static int counter = 0;
	char help[3] = "xx";
	while (counter < count)
	{
		
	}
}

void inverse_bits(void* ptr, size_t offset, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		*(ptr + offset + i) = ~*(ptr + offset + i);
	}
}

int main()
{
	char tab[100];
	printf("Podaj cokolwiek xD: ");
	fgets(tab, 100, stdin);

	show(tab, strlen(tab));

	return 0;
}