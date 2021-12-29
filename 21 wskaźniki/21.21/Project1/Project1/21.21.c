#include<stdio.h>
#include<stdlib.h>

int column_statistics(const int *ptr, int width, int height, int column_id,
	int* max, int* min, float *avg)
{
	float suma = 0;
	if ((ptr == NULL) || (max == NULL) || (min == NULL) || (avg == NULL) || (column_id >= width) || (width <= 0) || (height <= 0) || (column_id < 0))
		return 0;

	for (int i = 0; i < height; i++)
	{
		if (i == 0)
		{
			*min = *max = *((ptr + (i*width)) + column_id);
			suma = suma + *((ptr + (i*width)) + column_id);
		}
		else
		{
			if (*((ptr + (i*width)) + column_id) > *max)
				*max = *((ptr + (i*width)) + column_id);

			if (*((ptr + (i*width)) + column_id) < *min)
				*min = *((ptr + (i*width)) + column_id);

			suma = suma + *((ptr + (i*width)) + column_id);
		}

	}

	*avg = suma / height;

	return 1;
}
int row_statistics(const int *ptr, int width, int height, int row_id, int* max,
	int* min, float *avg)
{
	float suma = 0;
	if ((ptr == NULL) || (max == NULL) || (min == NULL) || (avg == NULL) || (row_id >= height) || (width <= 0) || (height <= 0) || (row_id < 0))
		return 0;

	for (int i = 0; i < width; i++)
	{
		if (i == 0)
		{
			*min = *max = *((ptr + (row_id*width)) + i);
			suma = suma + *((ptr + (row_id*width)) + i);
		}
		else
		{
			if (*((ptr + (row_id*width)) + i) > *max)
				*max = *((ptr + (row_id*width)) + i);

			if (*((ptr + (row_id*width)) + i) < *min)
				*min = *((ptr + (row_id*width)) + i);

			suma = suma + *((ptr + (row_id*width)) + i);
		}

	}

	*avg = suma / width;

	return 1;
}

int main()
{
	int tab[5][5], min, max, *ptab = tab[0], *pmin, *pmax;
	float avg, *pavg;
	pmin = &min;
	pmax = &max;
	pavg = &avg;

	printf("Podaj macierz 5x5: ");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			scanf("%d", *(tab + i) + j);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		column_statistics(ptab, 5, 5, i, pmax, pmin, pavg);
		printf("%d %d %.2f\n", *pmin, *pmax, *pavg);
	}

	
	for (int i = 0; i < 5; i++)
	{
		row_statistics(ptab, 5, 5, i, pmax, pmin, pavg);
		printf("%d %d %.2f\n", *pmin, *pmax, *pavg);
	}

	return 0;
}