#include<stdio.h>
#include<stdlib.h>
#include"comparators.h"

void display(int* tab, int N);

int main()
{
	int *lel;
	if (!(lel = (int*)malloc(sizeof(int) * 5)))
	{
		printf("Failed to allocate memory");
		return 2;
	}

	int choice, size, *tab, input;
	printf("Podaj ile chcesz liczb: ");
	scanf("%d", &size);
	if (size < 1)
	{
		printf("Incorrect input");
		free(lel);
		return 1;
	}

	if (!(tab = malloc(sizeof(int) * size)))
	{
		printf("Failed to allocate memory");
		free(lel);
		return 2;
	}

	printf("Podaj liczby: ");
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &input);
		*(tab + i) = input;
	}

	printf("Podaj operacje: ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 0:
		if (!sort_int(tab, size, comp_int))
			display(tab, size);
		else
		{
			printf("Error");
			free(lel);
			free(tab);
			return 2;
		}
		
		break;
	case 1:
		if (!sort_int(tab, size, comp_int_abs))
			display(tab, size);
		else
		{
			printf("Error");
			free(lel);
			free(tab);
			return 2;
		}
		break;
	case 2:
		if (!sort_int(tab, size, comp_int_length))
			display(tab, size);
		else
		{
			printf("Error");
			free(lel);
			free(tab);
			return 2;
		}
		break;
	case 3:
		if (!sort_int(tab, size, comp_int_digits_sum))
			display(tab, size);
		else
		{
			printf("Error");
			free(lel);
			free(tab);
			return 2;
		}
		break;
	default:
		printf("Incorrect input");
		free(lel);
		free(tab);
		return 1;
	}

	free(lel);
	free(tab);

	return 0;
}

void display(int* tab, int N)
{
	if (tab && N > 0)
		for (int i = 0; i < N; i++)
			printf("%d ", *(tab + i));
}