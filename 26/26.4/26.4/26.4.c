#include<stdio.h>
#include<stdlib.h>

int create_array2(float **ptr, int N)
{
	if ((!ptr) || (N <= 0))
		return 2;
	*ptr = (float*)malloc(N * sizeof(float));
	if (!*ptr)
		return 1;

	return 0;
}

int main()
{
	int size;
	float *tab = 0, **tab2;
	tab2 = &tab;
	
	printf("Podaj ile chcesz: ");
	scanf("%d", &size);

	create_array2(tab2, size);

	if (!tab)
	{
		printf("Error");
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		*(tab + i) = (float)(((float)(rand() % 2001) / 100) - 10);
	}

	for (int i = 0; i < size; i++)
	{
		printf("%f ", *(tab + i));
	}

	free(tab);



	return 0;
}