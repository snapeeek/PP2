#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void display(const int* ptr, int N);
int* copy(const int* ptr, int N);

int main()
{
	srand(rand());
	int input;
	int *tab, *help;

	printf("Podaj ilosc danych: ");
	scanf("%d", &input);

	if (!(tab = malloc(input * sizeof(int))))
	{
		printf("Error");
		return 1;
	}

	for (int i = 0; i < input; i++)
	{
		*(tab + i) = (rand() % 21) - 10;
	}

	display(tab, input);
	help = copy(tab, input);
	if (help == NULL)
	{
		printf("Error");
		free(tab);
		return 1;
	}
	display(help, input);

	free(help);
	free(tab);
	return 0;
}

void display(const int* ptr, int N)
{
	if (ptr && N >= 1)
	{
		for (int i = 0; i < N; i++)
			printf("%d ", *(ptr + i));
		printf("\n");
	}
}

int* copy(const int* ptr, int N)
{
	if (!ptr || N < 1)
		return NULL;

	int *help;
	if (!(help = malloc(N * sizeof(int))))
	{
		return NULL;
	}

	for (int i = 0; i < N; i++)
	{
		*(help + i) = *(ptr + i);
	}

	return help;
}