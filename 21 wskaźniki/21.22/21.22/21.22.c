#include<stdio.h>
#include<stdlib.h>

int dd_test(const int *ptr, int width, int height)
{
	int row_sum = 0, temp = 0;
	if ((ptr == NULL) || (width <= 0) || (height <= 0) || (width != height))
		return -1;

	for (int i = 0; i < height; i++)
	{
		row_sum = 0;
		for (int j = 0; j < width; j++)
		{
			if (i == j)
				temp = abs(*((ptr + (i*width)) + j));
			else
			{
				row_sum = row_sum + abs(*((ptr + (i * width)) + j));
			}
		}
		if (row_sum >= temp)
			return 0;
	}



	return 1;
}

int main()
{
	int tab[5][5], *ptab = tab[0];

	printf("Podaj macierz 5x5: ");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			scanf("%d", *(tab + i) + j);
		}
	}

	if (dd_test(ptab, 5, 5) == 1)
		printf("TAK");
	else
		printf("NIE");


	return 0;
}